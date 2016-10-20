//#define SCIP_DBG
//#define SCIP_DEBUG
//#define SD_PROPOBRA_WRITE_PREPROP


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/**@file   PropOBRA.cpp
 * @brief  Propagating bounds of control problems by solving auxiliary OBRAs, implementing Scott, Barton 2012
 * @author Ingmar Vierhaus
 */
/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include "PropOBRA.h"

using namespace ctrl;

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
	return std::pair<B,A>(p.second, p.first);
}

/*
 * Helper function use for display of run statistics
 */
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
	std::multimap<B,A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
			flip_pair<A,B>);
	return dst;
}

#define HASHTABLESIZE_FACTOR 5

/** Displays the header for the progress bar */
SCIP_RETCODE PropOBRA::printTimeProgressHeader(int tStart, int tFinal, int steps, int nChars)
{
   int length = std::max(snprintf(nullptr, 0, "%d", tStart), snprintf(nullptr, 0, "%d", tFinal)) + 1;
   SCIPinfoMessage(scip_, NULL, "CondhdlrCtrlDifferential: Beginning iteration over time steps\n");
   SCIPinfoMessage(scip_, NULL,  "%-*s", length, std::to_string(tStart).c_str());

   for (int i = 0; i < nChars - 2*length; ++i)
   {
      SCIPinfoMessage(scip_, NULL,  "-");
   }
   SCIPinfoMessage(scip_, NULL,  "%*s\n", length, std::to_string(tFinal).c_str());
   progressTime_ = 0;
   progressStep_ =  (SCIP_Real) nChars / (SCIP_Real) steps;
   return SCIP_OKAY;
}

/** displays the progress of propOBRA to the user as a horizontal progress bar */
SCIP_RETCODE PropOBRA::printProgress()
{
   int newTime = (int) std::floor((long double) currentTime_ * progressStep_);
   for (int i = progressTime_; i < newTime; ++i) {
      if( i == 0)
         printf("|");
      else
         printf("-");
      fflush(stdout);
   }

   progressTime_ = newTime;

   return SCIP_OKAY;
}

/** Reads the params for the subscip if given in via parameter propagating/obra/subscipSetFile */
SCIP_RETCODE readSubscipParams(SCIP* scip, SCIP* subscip)
{
   /* Read subscip parameters (overwrites timelimit, if given in subscip set-file */
   char* setfile;
   SCIPgetStringParam(scip,"propagating/obra/subscipSetFile",&setfile);
   //SCIPdebugMessage("reading parameters from %s\n",setfile);
   //SCIP_CALL( SCIPreadParams(subscip, setfile) );

   if( SCIPfileExists(setfile) )
   {
      SCIPdebugMessage("reading subscip parameter file <%s>\n", setfile);
      SCIP_CALL( SCIPreadParams(subscip, setfile) );
   }
   else
      SCIPdebugMessage("subscip parameter file <%s> not found - using default parameters\n", setfile);

}


/** initialization method of propagator */
SCIP_DECL_PROPINIT(PropOBRA::scip_init)
{
   return SCIP_OKAY;
}

/** execution method of propagator */
SCIP_DECL_PROPEXEC(PropOBRA::scip_exec)
{
   SCIP_CALL( applyOBRA(scip, result) );
   return SCIP_OKAY;
}


SCIP_RETCODE PropOBRA::prepareConstTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap)
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;
   SCIP_Bool addCuts;
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/addCuts",&addCuts) );

   /* Configure pattern */
   constTimePattern_.clearVars();
   constTimePattern_.setScip(scip);
   constTimePattern_.setSubscip(subscip);
   constTimePattern_.setCurrentTime(currentTime_);
   SCIP_CALL( constTimePattern_.setAddCuts(addCuts) );

   /* Iterate over variables that will create the space of the linear cut */
   for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
   {
      SCIP_VAR* var(structure_->getDiffConsVar());
      if( var != NULL)
      {
         /* Add the scip and subscip variables corresponding the the differential variable */
         assert( SCIPhashmapGetImage(varmap,var) != NULL);
         constTimePattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap,var));
         SCIPdebugMessage("added variable  %s\n",SCIPvarGetName(var));
      }
      else
      {
         SCIPdebugMessage("Constraint %s has no forward variable\n",SCIPconsGetName(pairIt->first));
      }
   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::prepareMultiTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_VAR* lastVar, SCIP_HASHMAP* varmap)
{

   VarVec subscipVars;
   int multiTimecutLookback;
   SCIP_CALL( SCIPgetIntParam(scip,"propagating/obra/multiTimeCutLookback",&multiTimecutLookback) );

   if( lastVar == NULL)
   {
      SCIPdebugMessage("Constraint has no forward variable\n");
      return SCIP_OKAY;
   }

   /* Configure pattern */
   multiTimePattern_.clearVars();
   multiTimePattern_.setScip(scip);
   multiTimePattern_.setSubscip(subscip);
   multiTimePattern_.setCurrentTime(currentTime_);

   std::vector<SCIP_VAR*> lastVars(structure_->getDiffConsLastVars(multiTimecutLookback));

   /* Add the scip and subscip variables corresponding the the differential variable */
   SCIPdbgMsg("adding variable %s\n",SCIPvarGetName(lastVar));
   multiTimePattern_.addVar(lastVar, (SCIP_VAR*) SCIPhashmapGetImage(varmap,lastVar));
   boost::cmatch matches;

   if( !boost::regex_match(SCIPvarGetName(lastVar), matches, structure_->getVarRegex() ))
      assert(false);

   std::string varName(matches[1].first,matches[1].second);
   std::string varTimeString(matches[5].first,matches[5].second);
   std::string varControlString(matches[2].first,matches[2].second);
   std::string varLevelString(matches[3].first,matches[3].second);
   std::string varTypeString(matches[4].first,matches[4].second);

   /* Iterate over previous variables of the same state and add to pattern */
   for( int i=1; i <= multiTimecutLookback - 1; ++i)
   {
      SCIP_VAR* var;
      std::ostringstream oss;
      oss << "t_" << varName << "(" << currentTime_ - i << ")";
      SCIPdbgMsg("i= %i:finding variable at time %i\n",i, currentTime_ - i);
      SCIPdbgMsg("finding var %s\n",oss.str().c_str());
      var = SCIPfindVar(scip,oss.str().c_str());
      SCIPdbgMsg("found var %s\n",SCIPvarGetName(var));
      /* Make sure varaible exists in subscip */
      SCIP_VAR* subscipVar;
      subscipVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,var);
      if( subscipVar != NULL)
    	  multiTimePattern_.addVar(var, subscipVar);
   }

   return SCIP_OKAY;
}


/** Method executing bound propagation using a subscip for differential and algebraic constraints at one given time
 *
 *  input:
 *  - scip                 : SCIP main data structure of the original problem
 *  - subscip              : SCIP main data structure for the subscip, with created empty problem and settings
 *  - currentTime          : Bounds of variables at the given currentTime will (hopfeully) be tightened
 *  - historicCons         : The number of historical constraints to be considered in bound tightening
 *  - varmap               : A preallocated sufficiently large varmap to be used for the subscip (contents will be lost)
 *  - consmap              : A preallocated sufficently large consmap to be used for the subscip (contents will be lost)
 *  - nPropagatedVars      : Pointer to an integer, which is incrementend by one for each propagated variable, or NULL
 *  - nchgbds              : Pointer to an integer, which is incrementend by one for each changed bound or NULL
 *
 *  In Addition to the call parameters, this method depends on the availability of a valid problem structure
 *
 *  The method sequentially completes two tasks:
 *  1) Bound propagation to algebraic variables at t = currentTime -1 using the algebraic constraints at t = currentTime -1
 *     and additionally historicCons earlier constraints
 *  2) Bound propagation to differential variables at t = currentTime using the algebraic constraints at t = currentTime
 *     and additionally historicCons earlier constraints
 *
 *  These tasks are divided into 6 smaller steps, see comments in code and SCIPdebugMessages
 *
 *  If historicCons is set to 0 this method amounts to (inefficient) conventional bound propagation for variables at a given time
 *
 */
SCIP_RETCODE PropOBRA::propBoundsAtTwithSubscip(SCIP* scip, SCIP* subscip, int historicCons, SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, int* nPropagatedVars, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge)
{

   /* Get parameters on what to propagate */
   SCIP_Bool propagateAlgebraic;
   SCIP_Bool propagateStates;
   SCIP_Bool propagateControls;
   SCIP_Bool addMultiTimeCuts;
   int multiTimecutLookback;
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/propagateAlgebraic",&propagateAlgebraic) );
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/propagateStates",&propagateStates) );
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/propagateControls",&propagateControls) );
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/addMultiTimeCuts",&addMultiTimeCuts) );
   SCIP_CALL( SCIPgetIntParam(scip,"propagating/obra/multiTimeCutLookback",&multiTimecutLookback) );

   SCIPdbgMsg("Entering propBoundsAtTWithSubscip, currentTime_ is %i\n",currentTime_);

   /*
    * 1: Free Subscip and emtpy hashmaps
    */
   SCIP_CALL(SCIPcreateProb(subscip, "algebraicPropagationSubScip", NULL, NULL,         NULL, NULL, NULL, NULL, NULL));
   SCIP_CALL( SCIPaddParamsSD(subscip));

   std::map<SCIP_VAR*, SCIP_Real>* solMap = new std::map<SCIP_VAR*, SCIP_Real>;

   /* We want to use structure exploiting heuristic in the subproblem, so we need to initialize an SD problem */
   SCIP_CALL( SDinit(subscip));

   SCIPhashmapRemoveAll(varmap);
   SCIPhashmapRemoveAll(consmap);

   /*
    * 2: Add historic and current algebraic constraints to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - 1 - historicCons);
      if( firstAddTime < 0)
         firstAddTime = 0;
      SCIPdebugMessage(" Step 2: Adding algebraic constraints and variables for t=%i,...,%i\n",firstAddTime,currentTime_ - 1);

      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         SCIPdbgMsg(" Adding algebraic constraints at t=%i\n",addTime);
         for( structure_->startAlgebraicConsIteration(addTime); structure_->algebraicConsLeft(addTime);structure_->incrementAlgebraicCons())
         {

            SCIPdbgMsg("entered algebraicCons iteration\n");
            SCIP_CONS* cons(structure_->getAlgebraicCons());
            //TODO _SD: Problem structure should not return deleted constraints, but does in (for example reading DNRU_sos2_costinvest.osilc)
            if( !SCIPconsIsDeleted(cons) )
            {
               SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cons));
               SCIP_CALL( SDaddConsWithVars(cons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
            }
            else
            {
               SCIPdbgMsg("not adding deleted cons %s\n", SCIPconsGetName(cons));
            }
         }
         SCIPcppDbgMsg(" Added Constraints and Variables" << std::endl);
      }
   }

   /*
    * 3: Add historic differential constraints to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - historicCons);
      if( firstAddTime < 0 )
         firstAddTime = 0;
      SCIPdebugMessage(" Step 3: Adding historic differential constraints to subscip at t=%i,...,%i\n",firstAddTime, currentTime_ - 1);
      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         for( structure_->startDiffConsIteration(addTime); structure_->diffConsLeft(addTime); structure_->incrementDiffCons())
         {
            SCIP_CONS* cons(structure_->getDiffConsCons());
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cons));
            SCIP_CALL( SDaddConsWithVars(cons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
         }
      }
      SCIPcppDbgMsg(" Added Constraints and Variables" << std::endl);
   }

   /*
    * 4: Add historic cuts to state variables to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - historicCons);
      if( firstAddTime < 0 )
         firstAddTime = 0;
      SCIPdebugMessage(" Step 4: Adding state cut constraints to subscip at t=%i,...,%i\n",firstAddTime, currentTime_ - 1);
      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         SCIPdbgMsg(" Adding cut constraints at t=%i\n",addTime);
         for( structure_->startCutIteration(addTime); structure_->cutsLeft(addTime); structure_->incrementCut())
         {
            SCIP_CONS* cut(structure_->getCut());
            assert(!SCIPconsIsDeleted(cut));
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cut));
            /* Add this constraint and its variables */
            SCIP_CALL( SDaddConsWithVars(cut,scip,subscip, varmap, consmap, true, true, solMap, FALSE) );
         }
      }
   }

   /*
    * 5: Propagate algebraic constraints
    */
   if( propagateAlgebraic && (currentTime_ -1 >= 0) )
   {
      SCIPdebugMessage(" Step 5: Propagating bounds to forward algebraic variables at t=%i\n",currentTime_ - 1);
      SCIP_VAR* subscipLastVar = NULL;

      for( structure_->startLevelIteration(currentTime_ - 1); structure_->levelsLeft(currentTime_ - 1); structure_->incrementLevel())
      {
         int consCounter(0);
         for( structure_->startLevelConsIteration(); structure_->levelConsLeft() && !(*boundsDiverge); structure_->incrementLevelCons())
         {
            if( structure_->currentLevelConsHasVar() ) /* Only if constraint has forward variable */
            {
               SCIP_CONS* currentCons(structure_->getCurrentLevelConsCons());
               SCIP_VAR* forwardVar(structure_->getCurrentLevelConsOrigVar());
               assert(currentCons != NULL);
               //TODO _SD: Problem structure should not return deleted constraints, but does in (for example reading DNRU_sos2_costinvest.osilc)
               if( !SCIPconsIsDeleted(currentCons) )
               {

                  SCIPdbg(SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s [%1.16e,%1.16e]\n    ",
                     SCIPconsGetName(currentCons), SCIPvarGetName(forwardVar),
                     SCIPvarGetLbLocal(forwardVar),SCIPvarGetUbLocal(forwardVar)));

                  SCIPdbg( SCIP_CALL_ABORT( SCIPprintCons(scip, currentCons, NULL) ) );
                  SCIPdbg( SCIPinfoMessage(scip, NULL, ";\n") );

                  //unsigned int varIndex(SCIPvarGetIndex(forwardVar));
                  SCIPdbgMsg("Considering Variable %s\n",SCIPvarGetName(forwardVar));
                  SCIPdbgMsg("bound difference is %1.16f\n",SCIPvarGetUbLocal(forwardVar)-SCIPvarGetLbLocal(forwardVar));

                  SCIP_Bool localBoundsDiverge(false);

                  /* Set Objective of last variable back to zero */
                  if( subscipLastVar != NULL )
                     SCIPchgVarObj(subscip, subscipLastVar, 0);

                  /* Set Objective of current variable to 1 */
                  SCIPcppDbgMsg("Setting Objective" << std::endl);
                  SCIP_VAR* subscipForwardVar;
                  subscipForwardVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,forwardVar);

                  SCIPcppDbgMsg("Got current var from hashmap, original " << SCIPvarGetName(forwardVar) << std::endl);
                  SCIPcppDbgMsg("image is " << SCIPvarGetName(subscipForwardVar) << std::endl);
                  SCIPchgVarObj(subscip, subscipForwardVar, 1);

                  SCIPcppDbgMsg("Set Objective" << std::endl);
                  subscipLastVar = subscipForwardVar;

                  SCIP_CALL( propBoundWithSubscip(scip,forwardVar,subscip,subscipForwardVar,nchgbds,totalBoundReduction,&localBoundsDiverge, solMap) );
                  if( nPropagatedVars != NULL )
                     ++(*nPropagatedVars);

                  if( localBoundsDiverge ) {
                     SCIPdebugMessage("propagation arrives at divergence\n");
                     *boundsDiverge = true;
                  }

                  /* Set Objective of current variable back to 0*/
                  SCIPchgVarObj(subscip, subscipForwardVar, 0);
                  ++consCounter;
               }
               else
               {
                  SCIPdbgMsg("not adding deleted cons %s\n", SCIPconsGetName(currentCons));
               }

            } /* Close only constraints with forward variable */
         } /* Close loop over constraints of level */
      } /* Close loop over levels */
   }

   //TODO _SD: This worked well before, removed for sol copy testing, better way?
   //SCIP_CALL(SCIPfreeTransform(subscip) );

   /*
    * 6: Add differential constraints at current time to subscip
    */
   SCIPdebugMessage(" Step 6: Adding differential constraints at t=%i\n",currentTime_);
   if( !(*boundsDiverge) ) {
      ConsVarVec::iterator pairIt;
      for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
      {
         SCIP_CONS * cons(structure_->getDiffConsCons());
         //TODO _SD: Problem structure should not return deleted constraints, but does in (for example reading DNRU_sos2_costinvest.osilc)
         if( !SCIPconsIsDeleted(cons) )
         {
            assert(!SCIPconsIsDeleted(cons));
            SCIPdebug( SCIP_CALL_ABORT( SCIPprintCons(scip, cons, NULL) ) );
            SCIPdebug( SCIPinfoMessage(scip, NULL, ";\n") );
            SCIP_CONS * currentCons(structure_->getDiffConsCons());
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(currentCons));
            /* Add this constraint and its variables */
            SCIP_CALL( SDaddConsWithVars(currentCons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
         }
         else
         {
            SCIPdbgMsg("not adding deleted cons %s\n", SCIPconsGetName(cons));
         }
      }
   }

   /*
    * 7_2: propagation of states 'vertically', 'horizontally' and 'diagonally'
    */
   if(  currentTime_ >= 1 && propagateStates && !(*boundsDiverge) )
   {
      SCIPdebugMessage("#### Step 7_2: Propagating bounds to differential variables at t=%i\n",currentTime_);
      ConsVarVec::iterator pairIt;

      SCIP_CALL( prepareConstTimeStatePattern(scip, subscip, varmap));
      SCIP_CALL( constTimePattern_.setSolMap(solMap));
      SCIP_CALL( constTimePattern_.buildHyperCube() );

      SCIP_CALL( constTimePattern_.propagate(currentTime_));
      SCIPdebugMessage("#### Done with Step 7_2\n");
   } //Close Step 7


   /*
    * 7_3: Propagation of states from different times
    */
   if( currentTime_ >= 1 && addMultiTimeCuts && !(*boundsDiverge) ) {
      SCIPdbgMsg("multitimelookback = %i\n",multiTimecutLookback);
      SCIPdebugMessage("#### Step 7_3: Propagating bounds to differential variables at t=%i...%i\n",currentTime_ - multiTimecutLookback + 1,currentTime_);
      ConsVarVec::iterator pairIt;

      for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
      {
         int multiTimecutLookback;
         SCIP_CALL( SCIPgetIntParam(scip,"propagating/obra/multiTimeCutLookback",&multiTimecutLookback) );
         SCIP_VAR* var(structure_->getDiffConsVar());
         SCIP_CONS* cons(structure_->getDiffConsCons());
         SCIPdebugMessage("  Creating multitime cuts on Variable %s --> %s\n",SCIPvarGetName(var),SCIPconsGetName(cons));

         SCIP_CALL( prepareMultiTimeStatePattern(scip, subscip, var, varmap));
         multiTimePattern_.toString();
         SCIP_CALL( multiTimePattern_.setSolMap(solMap));
         SCIP_CALL(multiTimePattern_.buildHyperCube() );
         SCIP_CALL(multiTimePattern_.propagate(currentTime_));
         SCIP_CALL(multiTimePattern_.resetObjVals());

      }
      SCIPdebugMessage("#### Done with Step 7_3\n");
   } /* Close Step 7 */


   if( propagateControls )
   {
	   SCIPdebugMessage(" Step 7_4: Propagating bounds to control variables at t=%i\n",currentTime_);
	   for( structure_->startControlVarIteration(currentTime_ - 1); structure_->controlVarsLeft(currentTime_ - 1);structure_->incrementControlVar() )
	   {
		   SCIP_VAR* controlVar(structure_->getControlVar());
		   SCIP_Bool localBoundsDiverge(false);

		   assert(controlVar != NULL);
		   assert(!SCIPvarIsDeleted(controlVar));

		   SCIPdbgMsg("propagating for control variable %s\n",SCIPvarGetName(controlVar));
		   SCIPdebugMessage("propagating for control variable %s\n",SCIPvarGetName(controlVar));

		   /* Set objective of the control variable to 1 */
		   SCIP_VAR* subscipControlVar;
		   subscipControlVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,controlVar);
		   SCIPchgVarObj(subscip, subscipControlVar, 1);

		   /* Call propBoundWithSubscip on this variable */
		   SCIP_CALL( propBoundWithSubscip(scip,controlVar,subscip,subscipControlVar,nchgbds, totalBoundReduction, &localBoundsDiverge, solMap));
		   if( nPropagatedVars != NULL )
			   ++(*nPropagatedVars);

		   /* Set objective of the control variable back to 0*/
		   SCIPchgVarObj(subscip, subscipControlVar, 0);

	   } //Close Iteration over control variables at given time
   }

   SCIP_CALL( SCIPfreeTransform(subscip) );

   if( (*boundsDiverge) )
   {
      SCIPdebugMessage("Bounds diverge at  t=%i\n",currentTime_);
   }

   delete solMap;

   return SCIP_OKAY;
}

/** propagation of Bounds of a variable by global solution of a subscip
 *
 *  input:
 *  - scip                 : SCIP main data structure of the original problem
 *  - origVar              : Pointer to the Variable in the original problem
 *  - subscip              : SCIP main data structure for the subscip
 *  - subscipObjectiveVar  : Pointer to the Variable in the sub problem
 *
 *  This method solves the subscip in maximization and minimization sense.
 *  If the subscip is solved to optimality, the lower (upper) bound of the original
 *  problem is set to the solution of the subscipObjectiveVar in the minimization (maximization) problem.
 *  The resulting bounds are also set in the subscip for subscipObjectiveVar
 *
 *  Except for setting the optimization sense, the subscip is not altered before solutions which means that the
 *  objectives of all values have to be set appropriately,
 *  i.e. var->obj = 1 if( var = subscipObjectiveVar ), else 0
 *
 */

SCIP_RETCODE PropOBRA::propBoundWithSubscip( SCIP* scip, SCIP_VAR* origVar, SCIP* subscip, SCIP_VAR* subscipObjectiveVar, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge, std::map<SCIP_VAR*, SCIP_Real>* solMap )
{
   assert( scip != NULL );
   assert( subscip != NULL );
   assert( origVar != NULL );
   assert( subscipObjectiveVar != NULL );
   assert( boundsDiverge != NULL );

   SCIP_Bool changedBounds[] = {false, false};
   SCIP_Real newBounds[2];
   SCIP_Real oldBounds[2];
   changedBounds[0] = false;
   changedBounds[1] = false;

   int historicCons( 0 );
   int i;

   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/historicCons", &historicCons ) );
   std::string origVarFullName( SCIPvarGetName( origVar ) );

   *boundsDiverge = false;

   /* Create clock and start measuring time in propagator */
   SCIP_CLOCK* propClock;
   SCIP_CALL( SCIPclockCreate( & propClock , SCIP_CLOCKTYPE_DEFAULT ) );
   SCIPclockSetTime( propClock, 0 );
   SCIPclockStart( propClock, scip->set );

   /*
    * Solving subscips for lower (i=0) and upper (i=1) bound in loop
    */

   /* Prepare everything we can do outside the loop */
   oldBounds[0] = SCIPvarGetLbLocal( origVar );
   oldBounds[1] = SCIPvarGetUbLocal( origVar );

   for( i = 0; i <= 1 && !( *boundsDiverge ); i++ )
   {
      SCIP_CALL( SCIPfreeTransform( subscip ) );

      /* Preparations of the run, depending on maximization or minimization */
      //TODO if what
      if( i == 0 )
         SCIP_CALL( SCIPsetObjsense( subscip, SCIP_OBJSENSE_MINIMIZE ) );
      else
         SCIP_CALL( SCIPsetObjsense( subscip, SCIP_OBJSENSE_MAXIMIZE ) );

      /* Solve the subscip */
      SCIPdbgMsg( "ready to solve subscip\n" );
      SCIPdbgMsg( "before solving: objlim is %g\n", SCIPgetObjlimit( subscip ) );

      SCIP_Bool writeSubscips;
      SCIPgetBoolParam( scip, "propagating/obra/writeSubscips", &writeSubscips );
      char* paramstr, *paramstr2;
      SCIPgetStringParam( scip, "propagating/obra/outFile", &paramstr );
      SCIPgetStringParam( scip, "propagating/obra/outDir", &paramstr2 );

      if( writeSubscips )
      {
         std::ostringstream oss;
         oss << paramstr2 << paramstr << "_" << historicCons << "_" << currentTime_ << "_algebraic_subscip_" << SCIPvarGetName( origVar ) << "_" << i << ".cip";
         SCIPdebugMessage( "WRITING transformed subscip to file %s\n", oss.str().c_str() );
         SCIPdebug( SCIP_CALL( SCIPwriteOrigProblem( subscip, oss.str().c_str(), "cip", FALSE ) ) );
      }

      SCIPdbgMsg( "(t=%i) solving SCIP for %s bound and Variable %s (%s)\n", currentTime_, ( i == 0 ? "lower" : "upper" ), SCIPvarGetName( origVar ), SCIPvarGetName( subscipObjectiveVar ) );

      if( signal_)
      {
         std::ostringstream oss;
         oss << "algebraicSubscipStrangeStall_" << SCIPvarGetName( subscipObjectiveVar );

         if( i == 0 )
            oss << "_lower.cip";
         else
            oss << "_upper.cip";

         SCIPdebug( SCIP_CALL( SCIPwriteOrigProblem( subscip, oss.str().c_str(), "cip", FALSE ) ) );
      }

      SCIP_CALL( SCIPtransformProb( subscip ) );
      SCIPdbgMsg( "ready to solve SCIP for %s bound of variable %s\n", ( i == 0 ? "lower" : "upper" ) , SCIPvarGetName(origVar));

      SCIP_SOL* subscipSol;
      SCIP_CALL(SCIPcreateSol(subscip,&subscipSol,NULL));
      for( auto iter = solMap->begin(); iter != solMap->end(); ++iter)
         SCIPsetSolVal(subscip, subscipSol, iter->first, iter->second);

      SCIP_Bool success;
      SCIPtrySolFree(subscip, &subscipSol, FALSE, TRUE, TRUE, TRUE, TRUE, &success);
      if( !success)
         SCIPwarningMessage(scip, "Solution was not accepted in subscip\n");

      SDsetIsReformulated( subscip, false );
      SCIP_CALL( SCIPsolve( subscip ) );

      /* Evaluate (hopefully) solved subscip */
      if( SCIPgetStatus( subscip ) == SCIP_STATUS_UNBOUNDED )
      {
         *boundsDiverge = true;
         SCIPdebugMessage( "Set boundsDiverge to true because subproblem was unbounded\n" );
      }
      else if( SCIPgetStatus( subscip ) == SCIP_STATUS_INFEASIBLE )
      {
         *boundsDiverge = true;
         SCIPdebugMessage( "Set boundsDiverge to true because subproblem was infeasible\n" );
         assert(false);
      }
      else if( SCIPgetStatus( subscip ) == SCIP_STATUS_OPTIMAL
               || SCIPgetStatus( subscip ) == SCIP_STATUS_TIMELIMIT
               || SCIPgetStatus( subscip ) == SCIP_STATUS_GAPLIMIT
               || SCIPgetStatus( subscip ) == SCIP_STATUS_NODELIMIT
               || SCIPgetStatus( subscip ) == SCIP_STATUS_TOTALNODELIMIT
               || SCIPgetStatus( subscip ) == SCIP_STATUS_STALLNODELIMIT
               || SCIPgetStatus( subscip ) == SCIP_STATUS_MEMLIMIT
             )
      {
         if( SCIPgetStatus( subscip ) == SCIP_STATUS_OPTIMAL )
         {

            SCIP_SOL* subSol = SCIPgetBestSol( subscip );
            SCIPdbgMsg( "optimal solution value is %e\n", SCIPgetSolVal( subscip, subSol, subscipObjectiveVar ) );

            //Set new lower bound if global solution was found and bound is tighter
            newBounds[i] = SCIPgetSolVal( subscip, subSol, subscipObjectiveVar );
            SCIP_Bool feasible;
            SCIP_CALL( SCIPcheckSolOrig( subscip, subSol, &feasible, FALSE, FALSE ) );

            if( !feasible )
            {
               if( i == 0 )
               {
                  SCIPdbgMsg( "sol is not feasible, lowering bound slightly\n" );
                  newBounds[i] -= 1e-6;
               }
               else if( i == 1 )
               {
                  SCIPdbgMsg( "sol is not feasible, increasing bound slightly\n" );
                  newBounds[i] += 1e-6;
               }
            }

         }
         else
         {
            newBounds[i] = SCIPgetDualbound( subscip );
            SCIPdebugMessage( "did not solve algebraic to optimality for %s, using dual bound as new %s bound\n", SCIPvarGetName( origVar ), ( i == 0 ? "lower" : "upper" ) );
         }

         SCIPcppDbgMsg( "Solution value is " << std::setprecision( 16 ) << std::setw( 18 ) << newBounds[i]
                        << ", Current " << ( i == 0 ? "lower" : "upper" ) << "bound is " << ( i == 0 ? SCIPvarGetLbLocal( origVar ) : SCIPvarGetUbLocal( origVar ) )
                        << ", Diff is " << newBounds[i] - oldBounds[i] << std::endl );

         if( (
                  ( i == 0 && oldBounds[0] < newBounds[0] ) || //Found lower bound is better
                  ( i == 1 && oldBounds[1] > newBounds[1] )  //.. or found upper bound is better
               ) && !SCIPisEQ( scip, newBounds[i], oldBounds[i] ) )
         {
            *totalBoundReduction += ( i == 0 ? newBounds[0] - oldBounds[0] : oldBounds[1] - newBounds[1] );
            SCIPcppDbgMsg( "changing " << ( i == 0 ? "lower" : "upper" ) << " bound in scip" << std::endl );

            if( i == 0 )
            {
               SCIP_CALL( SCIPchgVarLb( scip, origVar, newBounds[i] ) );
            }
            else if( i == 1 )
            {
               SCIP_CALL( SCIPchgVarUb( scip, origVar, newBounds[i] ) );
            }

            if( nchgbds != NULL )
               ++ ( *nchgbds );

            changedBounds[i] = TRUE;
         }
      }
      else
      {
         SCIPdebugMessage( "subscip has unexpected status\n" );
         assert( false );
      }

      SCIP_CALL( SCIPfreeTransform( subscip ) );

      /* Update bound in subscip if it we computed a tighter bound */
      SCIPcppDbgMsg( "Changing bound in subscip" << std::endl );

      if( changedBounds[i] )
      {
         if( i == 0 )
         {
            SCIP_CALL( SCIPchgVarLb( subscip, subscipObjectiveVar, newBounds[i] ) );
         }
         else
         {
            SCIP_CALL( SCIPchgVarUb( subscip, subscipObjectiveVar, newBounds[i] ) );
         }
      }
   }


   /*
    * Fix variable if possible
    */
   SCIP_Real bounddiff( 0 );

   if( changedBounds[0] && changedBounds[1] )
   {
      SCIPdbgMsg( "both bounds have changed\n" );
      bounddiff = newBounds[1] - newBounds[0];
   }
   else if( changedBounds[0] )
   {
      SCIPdbgMsg( "only lower bound has changed\n" );
      bounddiff = oldBounds[1] - newBounds[0];
   }
   else if( changedBounds[1] )
   {
      SCIPdbgMsg( "only upper bound has changed\n" );
      bounddiff = newBounds[1] - oldBounds[0];
   }

   SCIPdbgMsg( "bounddifference is %1.16e\n", bounddiff );

   if( ( changedBounds[0] && changedBounds[1] && newBounds[1] - newBounds[0] < 1e-8 ) //Both bounds were changed to the same value
         || ( changedBounds[0] && oldBounds[1] - newBounds[0] < 1e-8 ) //Lower bound was changed to value of unchanged upper bound
         || ( changedBounds[1] && newBounds[1] - oldBounds[0] < 1e-8 ) //Upper bound was changed to value of unchanged lower bound
     )
   {
      SCIPdbgMsg( "fixing variables, since bounds are identical: lb = %e, ub = %e\n", newBounds[0], newBounds[1] );
      SCIP_Bool fixed;
      SCIP_Bool infeasible;

      if( changedBounds[0] && changedBounds[1] )
         SCIPfixVar( scip, origVar, 0.5 * ( newBounds[0] + newBounds[1] ), &infeasible, &fixed );
      else if( changedBounds[0] )
         SCIPfixVar( scip, origVar, 0.5 * ( newBounds[0] + oldBounds[1] ), &infeasible, &fixed );
      else if( changedBounds[1] )
         SCIPfixVar( scip, origVar, 0.5 * ( oldBounds[0] + newBounds[1] ), &infeasible, &fixed );

      assert( !infeasible );
      assert( fixed );
      SCIPdebugMessage( "  variable %-30s fixed to %1.5e                   in %1.3f s\n", origVarFullName.c_str(), 0.5 * ( newBounds[1] + newBounds[1] ), SCIPclockGetTime( propClock ) );
   }
   else
   {
      /* Add remaining domain to statstics */
      stats_.remainingBounds +=  SCIPvarGetUbLocal( origVar ) - SCIPvarGetLbLocal( origVar );
      SCIPdbgMsg( "remainingbounds after propagating to %s is %f\n", SCIPvarGetName( origVar ), stats_.remainingBounds );

      if( changedBounds[0] || changedBounds[1] )
      {
         SCIPdebugMessage( "  variable %-30s tightened to [%1.5e,%1.5e] in %1.3f s (lb:%i,ub:%i)\n", origVarFullName.c_str(), SCIPvarGetLbLocal( origVar ), SCIPvarGetUbLocal( origVar ) , SCIPclockGetTime( propClock ) , newBounds[0] ? 1 : 0, newBounds[1] ? 1 : 0 );

         if( ( changedBounds[0] && SCIPisInfinity( scip, SCIPvarGetUbLocal( origVar ) ) ) || ( changedBounds[1] && SCIPisInfinity( scip, -1 * SCIPvarGetLbLocal( origVar ) ) ) )
         {
            *boundsDiverge = true;
            SCIPdebugMessage( "Set boundsDiverge to true because bound was set to infinity\n" );
         }
         else if( ( changedBounds[0] && SCIPvarGetUbLocal( origVar ) > 1e10 ) || ( changedBounds[1] && SCIPvarGetLbLocal( origVar ) < -1e10 ) )
         {
            *boundsDiverge = true;
            SCIPdebugMessage( "Set boundsDiverge to true because bound was set to high/low value\n" );
         }
      }
      else
      {
         SCIPdebugMessage( "  variable %-30s not tightened       in %1.3f s\n", origVarFullName.c_str(),  SCIPclockGetTime( propClock ) );

         if( SCIPisInfinity( scip, SCIPvarGetUbLocal( origVar ) ) || SCIPisInfinity( scip, -1 * SCIPvarGetLbLocal( origVar ) ) )
         {
            *boundsDiverge = true;
            SCIPdebugMessage( "Set boundsDiverge to true because bounds remained untouched\n" );
         }
      }

      /* 'Valid' Unbounded variables should not stop propagation  */
      if(false && *boundsDiverge )
      {
         ctrl::SDproblemStructureInterface* structure(SDgetStructure(scip));
         boost::cmatch matches;
         if( boost::regex_match(origVarFullName.c_str(), matches, structure->getVarRegex() ))
         {
            std::string varName(matches[1].first,matches[1].second);
            SCIPdbgMsg("varname is %s\n",varName.c_str());
            std::string varTimeString(matches[5].first,matches[5].second);
            std::string varControlString(matches[2].first,matches[2].second);
            std::string varLevelString(matches[3].first,matches[3].second);
            std::string varTypeString(matches[4].first,matches[4].second);
            if( varName.compare("elasticityofdemand") == 0)
            {
               SCIPdbgMsg("elasticityOfDemand diverges as expected, not bailing out\n");
               *boundsDiverge = false;
            }
         }
         else
         {
            SCIPdbgMsg("did not match\n");
            assert(false);
         }
      }
   }

   SCIPclockFree( &propClock );

   return SCIP_OKAY;
}


SCIP_DECL_PROPPRESOL( PropOBRA::scip_presol )
{
   SCIPdebugMessage( "entered Presolving of Constraintless Conshdlr CtrlDifferential \n" );

   SDensureValidStructure(scip );

   SCIPdebugMessage( "Running Propagation of CtrlDifferential routine as part of presolving\n" );

   SCIP_CALL( applyOBRA(scip, result) );

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::printSummary(SCIP* scip, int nSubscips, SCIP_Real aggSolvingTime, SCIP_Bool addCuts, SCIP_Bool addMultiTimeCuts, int breakTime, int historicCons, SCIP_CLOCK* propClock)
{
   std::multimap<int, std::string> dst;
   std::map<int, std::string>::iterator iter;

   SCIPinfoMessage( scip, NULL, "-------------------------------------------------------------------------\n" );
   SCIPinfoMessage(scip,NULL,"| CtrlDifferential General Statistics in depth %5i                    |\n",SCIPgetDepth(scip));
   SCIPinfoMessage(scip,NULL,"| HistoricCons parameter:          %-4i                                 |\n",historicCons);
   SCIPinfoMessage( scip, NULL, "| Total time elapsed:             %1.5e s                         |\n", SCIPclockGetTime( propClock ) );
   SCIPinfoMessage( scip, NULL, "| Last propagated Time:           %-4i                                  |\n", ( breakTime < 0 ? currentTime_ : breakTime - 1 ) );
   SCIPinfoMessage(scip,NULL,"| Number of solved Subscips:       %-5i                                |\n",nSubscips);
   SCIPinfoMessage(scip,NULL,"| Total Solving Time:              %1.5e s                        |\n",aggSolvingTime);
   SCIPinfoMessage(scip,NULL,"| Avrg Time per Subscip:           %1.5e s                        |\n",aggSolvingTime / nSubscips);
   SCIPinfoMessage(scip,NULL,"| Time solving subscips [%]:       %-3.2f                                |\n",aggSolvingTime / SCIPclockGetTime(propClock) * 100.0);
   SCIPinfoMessage(scip,NULL,"-------------------------------------------------------------------------\n");
   SCIPinfoMessage(scip,NULL,"| Constant Time Statistics - Direct Bounds                              |\n");
   SCIPinfoMessage(scip,NULL,"| Number of considered bounds:     %-4i                                 |\n",constTimePattern_.stats_.nDirectBounds);
   SCIPinfoMessage(scip,NULL,"| Number of changed bounds:        %-4i                                 |\n",constTimePattern_.stats_.nUpdatedBounds);
   SCIPinfoMessage(scip,NULL,"| Updated Bounds [percent]:        %-3.2f                               |\n",(double) constTimePattern_.stats_.nDirectBounds / (double) constTimePattern_.stats_.nUpdatedBounds * 100);
   SCIPinfoMessage(scip,NULL,"| Optimal Bounds [percent]:        %-3.2f                               |\n",(double) constTimePattern_.stats_.nDirectBounds / (double) constTimePattern_.stats_.nDirectOptimal * 100);
   SCIPinfoMessage(scip,NULL,"| Aggregated Remaining Bounds:     %1.5e                          |\n",constTimePattern_.stats_.aggRemainingBounds);
   SCIPinfoMessage(scip,NULL,"| Average Remaining Bounds:        %1.5e                          |\n",constTimePattern_.stats_.aggRemainingBounds / constTimePattern_.stats_.nDirectBounds / 2);
   SCIPinfoMessage(scip,NULL,"| Aggregated Bound Reduction:      %1.5e                          |\n",constTimePattern_.stats_.aggBoundReduction);
   SCIPinfoMessage(scip,NULL,"| Bound Reduction per Variable:    %1.5e                          |\n",constTimePattern_.stats_.aggBoundReduction / constTimePattern_.stats_.nDirectBounds / 2);
   SCIPinfoMessage(scip,NULL,"| Aggregated Bounds Solving Time:  %1.5e s                        |\n",constTimePattern_.stats_.aggDirectSolutionTime);
   SCIPinfoMessage(scip,NULL,"| Bounds Solving Time per subscip: %1.5e s                        |\n",constTimePattern_.stats_.aggDirectSolutionTime / constTimePattern_.stats_.nDirectBounds);
   if( addCuts == TRUE)
   {
      SCIPinfoMessage(scip,NULL,"-------------------------------------------------------------------------\n");
      SCIPinfoMessage(scip,NULL,"| Constant Time Statistics - Cuts                                       |\n");
      SCIPinfoMessage(scip,NULL,"| Number of considered cuts:       %-4i                                 |\n",constTimePattern_.stats_.nCuts);
      SCIPinfoMessage(scip,NULL,"| Useful Cuts [percent] :          %-3.2f                               |\n",(double) constTimePattern_.stats_.nCutsUseful / (double) constTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip,NULL,"| Optimal Cuts  [percent] :        %-3.2f                               |\n",(double) constTimePattern_.stats_.nCutsOptimal / (double) constTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip,NULL,"| Aggregated Cuts Solving Time:    %1.5e s                        |\n",constTimePattern_.stats_.aggCutsSolutionTime);
      SCIPinfoMessage(scip,NULL,"| Cuts Solving Time per subscip:   %1.5e s                        |\n",constTimePattern_.stats_.aggCutsSolutionTime / constTimePattern_.stats_.nCuts);
      dst = flip_map(constTimePattern_.stats_.usefulCutDistribution);
      for( iter = dst.begin(); iter != dst.end(); ++iter) {
         SCIPinfoMessage(scip,NULL,"|   Percentage of type %8s*:   %-3.1f                                |\n",iter->second.c_str(),(double) iter->first / (double) constTimePattern_.stats_.nCutsUseful * 100.0);
      }
   }
   if( addMultiTimeCuts == TRUE)
   {
      SCIPinfoMessage(scip,NULL,"-------------------------------------------------------------------------\n");
      SCIPinfoMessage(scip,NULL,"| Multi Time Statistics - Cuts                                          |\n");
      SCIPinfoMessage(scip,NULL,"| Number of considered cuts:       %-4i                                 |\n",multiTimePattern_.stats_.nCuts);
      SCIPinfoMessage(scip,NULL,"| Useful Cuts [percent] :          %-3.2f                               |\n",(double) multiTimePattern_.stats_.nCutsUseful / (double) multiTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip,NULL,"| Optimal Cuts  [percent] :        %-3.2f                               |\n",(double) multiTimePattern_.stats_.nCutsOptimal / (double) multiTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip,NULL,"| Aggregated Cuts Solving Time:    %1.5e s                        |\n",multiTimePattern_.stats_.aggCutsSolutionTime);
      SCIPinfoMessage(scip,NULL,"| Cuts Solving Time per subscip:   %1.5e s                        |\n",multiTimePattern_.stats_.aggCutsSolutionTime / multiTimePattern_.stats_.nCuts);
      dst = flip_map(multiTimePattern_.stats_.usefulCutDistribution);
      for( iter = dst.begin(); iter != dst.end(); ++iter) {
         SCIPinfoMessage(scip,NULL,"|   Percentage of type %8s*:   %-3.1f                                |\n",iter->second.c_str(),(double) iter->first / (double) multiTimePattern_.stats_.nCutsUseful * 100.0);
      }
      SCIPinfoMessage( scip, NULL, "-------------------------------------------------------------------------\n" );
      SCIPinfoMessage(scip,NULL,"*: Unless variables are always orderd correctly this is not yet meaningful\n");
   }
   SCIPinfoMessage( scip, NULL, "-------------------------------------------------------------------------\n" );

}

SCIP_RETCODE PropOBRA::applyOBRA(SCIP* scip, SCIP_RESULT* result)
{
   /* Make sure parameters are the way we want them */
   {
      SCIP_Bool val;
      SCIP_CALL(SCIPgetBoolParam(scip, "constraints/nonlinear/reformulate", &val));
      //assert(val == FALSE);
      SCIP_CALL(SCIPgetBoolParam(scip, "presolving/donotmultaggr", &val));
      assert(val == TRUE);
   }

   /* We don't run in probing to avoid shitfAndPropagate heuristic propagating this expensive propagator */
   if( SCIPinProbing( scip ) )
      return SCIP_OKAY;

   SCIP_CLOCK* propClock;

   /* Start timing */
   SCIP_CALL( SCIPclockCreate(& propClock , SCIP_CLOCKTYPE_DEFAULT) );
   SCIPclockSetTime(propClock,0);
   SCIPclockStart(propClock,scip->set);

   /* Get parameters on how to run */
   int historicCons;
   int breakTime;
   int writeFreq;
   SCIP_Bool addCuts;
   SCIP_Bool addMultiTimeCuts;
   int cutFreq;
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/historicCons", &historicCons ) );
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/breakTime", &breakTime ) );
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/writeFreq", &writeFreq ) );
   SCIP_CALL( SCIPgetBoolParam( scip, "propagating/obra/addCuts", &addCuts ) );
   SCIP_CALL( SCIPgetBoolParam( scip, "propagating/obra/addMultiTimeCuts", &addMultiTimeCuts ) );
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/cutFreq", &cutFreq ) );

   /* Configure the constTime and multiTime PropagationPatterns */
   int cutConf3d;
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/cutConf3d", &cutConf3d ) );
   constTimePattern_.setCutConf3d( cutConf3d );
   constTimePattern_.setUseUnitCuts(false);

   SCIP_Bool useUnitCuts;
   SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/useUnitCuts",&useUnitCuts));
   multiTimePattern_.setUseUnitCuts(useUnitCuts);

   /* TODO _SD: Pending implementation of event handlers to invalidate Structure on consdelete, reform */
   structure_ = SDgetStructure(scip);

   SCIP_Real totalBoundReduction( 0 );
   int nPropagatedVars( 0 );
   int nchgbds( 0 );

   printTimeProgressHeader(structure_->getTinit(), structure_->getTfinal(), structure_->getLastTime(), 80);

   SCIPinfoMessage(scip_, NULL, "\n");

   for( currentTime_ = structure_->startTimeIteration(); structure_->timesLeft(); currentTime_ = structure_->incrementTime())
   {
      if( breakTime == -1 || currentTime_ < breakTime)
      {
         SCIPdebugMessage("t = %i\n",currentTime_);

         if(false && currentTime_ % 50 == 0) {
            SCIPinfoMessage(scip,NULL,"Propagating Bounds t = %i\n",currentTime_);
         }
         if( writeFreq != -1 && currentTime_ % writeFreq == 0)
         {
            char* paramstr,*paramstr2;
            std::ostringstream oss;
            SCIPgetStringParam(scip,"propagating/obra/outFile",&paramstr);
            SCIPgetStringParam(scip,"propagating/obra/outDir",&paramstr2);

            oss << paramstr2 << paramstr << "_" << historicCons << "_" << currentTime_ << ".cip";
            SCIPdebugMessage("WRITING transformed problem to file %s at t=%i\n",oss.str().c_str(),currentTime_);
            SCIPwriteTransProblem(scip, oss.str().c_str(), "cip", false);

         }
         /*
          * Create, allocate and configure Subscip
          */
         SCIP* subscip;
         SCIP_CALL( SCIPcreate(&subscip) );

         SCIP_CALL(SCIPincludeDefaultPlugins(subscip));
         SCIPaddIntParam(subscip,
            "misc/SDproblemStructureVersion",
            "Which version of the problemStructure Class should be loaded",
            NULL, FALSE, 0, 0, INT_MAX, NULL, NULL);

         /* Enable reoptimization if enabled */
         SCIP_Bool reoptimize;
         SCIP_CALL( SCIPgetBoolParam(scip, "propagating/obra/reoptimize", &reoptimize));
         if( reoptimize == TRUE )
         {
            SCIP_CALL( SCIPsetBoolParam(subscip, "reoptimization/enable", TRUE));
         }

         SCIP_Bool reopt;
         SCIP_CALL( SCIPgetBoolParam(subscip, "reoptimization/enable", &reopt));
         if( reopt == TRUE)
         {
            SCIPdebugMessage("reoptimization: ENABLED\n");
         }
         else
         {
            SCIPdebugMessage("reoptimization: DISABLED\n");
         }

         //SCIP_CALL( SCIPincludeObjHeur(subscip, new ctrl::HeurMaxCtrl(subscip), TRUE) );

         /* Standard feasibility tolerance allows sense reversed solutions of problem
          * without free variables to differ by more then SCIPepsilon */
         /* SCIP_CALL( SCIPsetSetFeastol(subscip->set,SCIPsetEpsilon(scip->set)) ); */

         /* Set timelimit and nodelimit of subscip from scip obra  parameters*/
         SCIP_Real subscipTimeLimit;
         SCIP_CALL( SCIPgetRealParam(scip,"propagating/obra/subscipTimeLimit",&subscipTimeLimit) );
         SCIP_CALL( SCIPsetRealParam(subscip,"limits/time",subscipTimeLimit) );
         /* Set nodelimit of subscip given through parameters of this constraint handler */
         SCIP_Longint subscipNodeLimit;
         SCIP_CALL( SCIPgetLongintParam(scip,"propagating/obra/subscipNodeLimit",&subscipNodeLimit) );
         SCIP_CALL( SCIPsetLongintParam(subscip,"limits/nodes",subscipNodeLimit) );

         /* Read params for subscip */
         readSubscipParams(scip, subscip);

         /* Create and allocate consmap and varmap */
         SCIP_HASHMAP* consmap;
         SCIP_CALL( SCIPhashmapCreate(&consmap, SCIPblkmem(subscip), SCIPgetNConss(scip)) );
         SCIP_HASHMAP* varmap;
         SCIP_CALL( SCIPhashmapCreate(&varmap, SCIPblkmem(subscip), SCIPcalcHashtableSize(SCIPgetNVars(scip))) );

         /* mute subscips */
         SCIP_Bool muteSubscip;
         SCIP_CALL( SCIPgetBoolParam(scip,"propagating/obra/muteSubscip",&muteSubscip) );
         if(muteSubscip == true)
         {
            SCIP_CALL( SCIPsetIntParam(subscip, "display/verblevel", 0) );
         }

         SCIP_Bool boundsDiverge(false);
         SCIPdbgMsg("calling propBoundsAtTwithSubscip, currentTime = %i\n",currentTime_);
         SCIP_CALL( propBoundsAtTwithSubscip(scip,subscip,historicCons,varmap,consmap, &nPropagatedVars, &nchgbds, &totalBoundReduction, &boundsDiverge));

         /* Clean up allocated maps, empty subscip */
         SCIPcppDbgMsg("Freeing hashmaps" << std::endl);
         SCIPhashmapFree(&varmap);
         SCIPhashmapFree(&consmap);
         /* Free subscip */
         SCIPcppDbgMsg("Freeing subscip" << std::endl);
         SCIP_CALL( SCIPfree(&subscip) );

         if( boundsDiverge)
         {
            SCIPdebugMessage("breaking for boundsDiverge at t = %i\n",currentTime_);
            break;
         }

      } /*Close stop iteration at given time*/
      else if( currentTime_ == breakTime)
      {
         SCIPdebugMessage("breaking for breakTime\n");
      }
      printProgress();
   } /*/Close iteration over times */

   SCIPclockStop( propClock, scip->set );

   int nSubscips = constTimePattern_.stats_.nSubscips + constTimePattern_.stats_.nSubscips;
   SCIP_Real aggSolvingTime    = constTimePattern_.stats_.aggSolutionTime    + multiTimePattern_.stats_.aggSolutionTime;

   /* Display the summary of this obra run */
   printSummary(scip, nSubscips, aggSolvingTime, addCuts, addMultiTimeCuts, breakTime, historicCons, propClock);

   SCIP_CALL( writeAfterProp(scip, breakTime, historicCons) );

   SCIPclockFree( &propClock );

   *result = SCIP_DIDNOTFIND;
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::writeAfterProp(SCIP* scip, int breakTime, int historicCons)
{
   SCIP_Bool writeAfterProp;
   if( SCIPgetBoolParam( scip, "propagating/obra/writeAfterProp", &writeAfterProp ) && writeAfterProp )
   {
      char* outfilestr, *outdirstr;
      std::ostringstream oss,bndoss;
      SCIPgetStringParam( scip, "propagating/obra/outFile", &outfilestr );
      SCIPgetStringParam( scip, "propagating/obra/outDir", &outdirstr );
      oss << outdirstr << outfilestr << "_" << historicCons << "_" << ( breakTime < 0 ? currentTime_ : breakTime - 1 ) << ".cip";

      SCIPdebugMessage( "WRITING transformed problem to file %s at t=%i\n", oss.str().c_str(), currentTime_ );
      SCIPwriteTransProblem(scip, oss.str().c_str(),"cip", false);
      bndoss << outdirstr << outfilestr << "_" << historicCons << "_" << currentTime_ << ".bnd";
      SCIPdebugMessage("WRITING bounds to file %s at t=%i\n",bndoss.str().c_str(),currentTime_);
      SCIPwriteTransProblem(scip, bndoss.str().c_str(), "bnd", false);

      SCIPdebugMessage( "done writing\n" );
   }

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::ensureCurrentStructure( SCIP* scip )
{

   SCIPdbgMsg( "ensuring current Structure by refreshing it blindly" );
   //TODO _SD: make sure structure refresh is necessary by using scip event handlers for constraint changes
//   SDrefreshStructure(scip);
   return SCIP_OKAY;
}








