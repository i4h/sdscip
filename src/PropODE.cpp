//#define SCIP_DBG
#define SCIP_DEBUG
//#define SD_PROPODE_WRITE_PREPROP


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/**@file   Propode.cpp
 * @brief  Propagating bounds of control problems by solving auxiliary ODEs, implementing Scott, Barton 2012
 * @author Ingmar Vierhaus
 */
/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include "PropODE.h"

using namespace ctrl;


/** initialization method of propagator */
SCIP_DECL_PROPINIT(PropODE::scip_init)
{
   ctrl::SDproblemStructureInterface* structure(SDgetStructure(scip));

   /* Disable propODE if derivatives ar not continuous */
   if( !structure->isXdotContinuous() )
   {
      SCIPwarningMessage(scip, "Derivatives are not absolutely continuous, disabling propODE\n");
      SCIP_CALL( SCIPsetIntParam(scip, "propagating/propODE/maxprerounds", 0) );
      SCIP_CALL( SCIPsetIntParam(scip, "propagating/propODE/freq", -1) );
   }

   /* Get parameters from scip */
   SCIP_CALL( SCIPgetBoolParam(scip_ ,"propagating/propODE/writeBounds", &writeFile_) );
   SCIP_CALL( SCIPgetStringParam(scip_ , "propagating/propODE/outFilePrefix",&outfilePrefix_) );
   SCIP_CALL( SCIPgetIntParam(scip_ , "propagating/propODE/intermediateSteps",&intermediateSteps_) );
   SCIP_CALL( SCIPgetBoolParam(scip_ ,"propagating/propODE/addErrorTerms", &addErrorTerms_) );


   /* Get parameters from problem structure */
   nStates_ = structure->getNStates();
   nControls_ = structure->getNControls();
   nAlgebraic_= structure->getNAlgebraic();
   nParams_ = 0;
   dt_ = structure->getTstep();
   t0_ = structure->getTinit();
   tf_ = structure->getTfinal();

   /* Derived parameters */
   dtIntermediate_ = dt_ / intermediateSteps_;

   return SCIP_OKAY;
}

/** execution method of propagator */
SCIP_DECL_PROPEXEC(PropODE::scip_exec)
{
   //SCIPdbgMsg("entered PropODE::scip_exec --------------------------------- \n");
   int nchgbds(0);

   assert(scip != NULL);
   assert(prop != NULL);

   if (!scipIsSet_)
   {
      scip_ = scip;
      scipIsSet_ = true;
   }


   *result = SCIP_DIDNOTRUN;

   if (SCIPinProbing(scip))
   {
      //SCIPdbgMsg("leaving PropODE, was called probing mode\n");
      return SCIP_OKAY;
   }

   /* Check that we know what to do with the last branching */
   /* allocate memory for all branching decisions */

   SCIP_VAR** branchvars;
   unsigned int startTime;
   SCIP_Real* branchbounds;
   SCIP_BOUNDTYPE* boundtypes;
   SCIP_NODE* node(SCIPgetCurrentNode(scip));
   int nbranchvars;
   int size(1);

   /* Only running once on each node */
   if (lastNodeNumber_ != 0 && SCIPnodeGetNumber(node) == lastNodeNumber_)
   {
      SCIPdbgMsg("not running again on node %lld\n", SCIPnodeGetNumber(node));
      return SCIP_OKAY;
   }
   else
      lastNodeNumber_ = SCIPnodeGetNumber(node);

   SCIP_CALL( SCIPallocBufferArray(scip, &branchvars, size) );
   SCIP_CALL( SCIPallocBufferArray(scip, &branchbounds, size) );
   SCIP_CALL( SCIPallocBufferArray(scip, &boundtypes, size) );
   SCIPnodeGetParentBranchings(node, branchvars, branchbounds, boundtypes, &nbranchvars, size );
   if (nbranchvars >= 2)
   {
      SCIPdbgMsg("reallocating branchvars buffer to fit %i branchvars\n",nbranchvars);
      size = nbranchvars;
      SCIPfreeBufferArray(scip, &branchvars);
      SCIP_CALL( SCIPallocBufferArray(scip, &branchvars, size) );
      SCIPnodeGetParentBranchings(node, branchvars, branchbounds, boundtypes, &nbranchvars, size );
   }

   for (int i = 0; i < nbranchvars; ++i) {
      SCIP_VAR *branchVar(branchvars[i]);
      SCIPdbgMsg("considering %i th branchvar %s\n",i, SCIPvarGetName(branchVar));
      ctrl::SDproblemStructureInterface* structure(SDgetStructure(scip));
      //SCIPdebugMessage("found last branchvar %s in [%f,%f]\n",SCIPvarGetName(lastBranchVar), SCIPvarGetLbLocal(lastBranchVar), SCIPvarGetUbLocal(lastBranchVar));
      if( structure->isControlVar(branchVar) )
      {
         /* If the branch was on a control variable, we start propagating at the first time of appearance */
         assert(structure->getControlVarBeginTime(branchVar) >= 0);
         startTime = (unsigned int) structure->getControlVarBeginTime(branchVar);
         SCIPdbgMsg("Executing PropODE in depth %i, node %lld\n",SCIPgetDepth(scip),SCIPnodeGetNumber(node));
         execCount_++;
         SCIPdebugMessage("applying PropODE for problem <%s> after branching on %s at depth %d, starting at t=%i, execCount = %i\n",
            "[..]", SCIPvarGetName(branchVar), SCIPgetDepth(scip), startTime, execCount_);
         SCIP_CALL( applyPropODE(scip, &nchgbds, result, startTime) );
         //assert(false);

      }
      else if( structure->isStateVar(branchVar))
      {
         startTime = (unsigned int) structure->getStateVarTime(branchVar);
         execCount_++;
         SCIPdebugMessage("applying PropODE for problem <%s> after branching on %s at depth %d, starting at t=%i, execCount = %i\n",
            "[..]", SCIPvarGetName(branchVar), SCIPgetDepth(scip), startTime, execCount_);
         SCIP_CALL( applyPropODE(scip, &nchgbds, result, startTime) );
         //assert(false);

      }
      else
      {
         SCIPdbgMsg("branch was not on state or control, doing nothing\n");
      }
      if (startTime == structure->getLastTime())
      {
         SCIPdbgMsg("branch was at last time, doing nothing\n");
      }
   }
   SCIPfreeBufferArray(scip, &branchvars);
   SCIPfreeBufferArray(scip, &branchbounds);
   SCIPfreeBufferArray(scip, &boundtypes);







   return SCIP_OKAY;
}

   SCIP_DECL_PROPPRESOL(PropODE::scip_presol)
{
   SDensureValidStructure(scip);
   ctrl::SDproblemStructureInterface* structure(SDgetStructure(scip) );


   assert(scip != NULL);
   assert(prop != NULL);

   *result = SCIP_DIDNOTRUN;

   if (!scipIsSet_)
   {
      scip_ = scip;
      scipIsSet_ = true;
   }

      /** This should soon be set via SDproblemStructure */
#ifdef CURRENT_MODEL_PREDATORPREY
      nStates_ = 2;
      nControls_ = 1;
      dt_ = 0.01;
      t0_ = 0;
      tf_ = 7;
      intermediateSteps_ = 1;
      dtIntermediate_ = 0.01;

#else
   #ifdef CURRENT_MODEL_MINIWORLD
         nStates_ = 3;
         nControls_ = 1;
         nParams_ = 0;
         dt_ = 0.5;
         /*intermediateSteps_ = 50;
         dtIntermediate_ = 0.01;*/
         intermediateSteps_ = 1;
         dtIntermediate_ = dt_ / intermediateSteps_;

         t0_ = 0;
         tf_ = 10;
   #else
      #ifdef CURRENT_MODEL_DNRU
            /* @todo: update */
            nStates_ = 8;
            nControls_ = 1;
            nParams_ = 0;
            dt_ = 1;
            intermediateSteps_ = 1;
            dtIntermediate_ = 1;
            t0_ = 0;
            tf_ = 200;
      #else
            //assert(false);
      #endif
   #endif
#endif

   /* Global enclosures
   addGlobalEnclosure(0, SCIP_BOUNDTYPE_LOWER, 0.0);
   addGlobalEnclosure(1, SCIP_BOUNDTYPE_LOWER, 0.0);
   addGlobalEnclosure(2, SCIP_BOUNDTYPE_LOWER, 0.0);

   addGlobalEnclosure(0, SCIP_BOUNDTYPE_UPPER, 20.0);
   addGlobalEnclosure(1, SCIP_BOUNDTYPE_UPPER, 20.0);
   addGlobalEnclosure(1, SCIP_BOUNDTYPE_UPPER, 20.0);*/

   /* Make sure that the derivative expression xDot_ is valid */
   //SCIP_CALL( updateXdot() );

   SCIP_CALL( applyPropODE(scip, nchgbds, result, 0) );

   if (*result == SCIP_REDUCEDDOM)
      *result = SCIP_SUCCESS;

   SCIPdbgMsg("returning from presolving of PropODE with result %i\n", *result);
   //assert(false);

   return SCIP_OKAY;
 }

SCIP_RETCODE PropODE::prepareOutFile(std::vector<std::string>  stateVarNames)
{
   /* Prepare output file */
   std::ostringstream outFileName;
   if (writeFile_)
   {
      outFileName << outfilePrefix_ << "_" << execCount_ << ".dat";
      outFile_.open(outFileName.str());
      SCIPdebugMessage("WRITNG u,v to %s\n", outFileName.str().c_str());
      outFile_ << "#" << std::setw(3) << "t" << "\t";
      for (int i = 0; i < nStates_; ++i)
         outFile_ << std::setw(8) << "v[" << i << "]" << "\t"
         << std::setw(8) << "w[" << i << "]" << "\t";
      outFile_ << std::endl;
      for (int i = 0; i < nStates_; ++i)
         outFile_ <<  stateVarNames[i] << "_l" << "\t"
         << stateVarNames[i] << "_u" << "\t";
      outFile_ << std::endl;
   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropODE::finalizeOutFile(std::string message)
{
   if (outFile_.is_open())
   {
      outFile_ << message;
      outFile_.close();
   }

   return SCIP_OKAY;
}

 /** This method executes the propagation routine by solving the systems interval-ode for v,w which
 * constitute lower and upper bounds to the states respectively
 * It uses the IntervalODEintegrator class, which in turn uses the SBrateEvaluator class to handle
 * derivative computations as well as the application of the bound tightening function \Omega_i^{U/L}.
 * A priori bounds for states and control bounds are read from the variables of the MINLP
 * and handed over to the integrator when calling the step function.
 * Depending on the chosen discretization, the rates may be evaluated at several points within the
 * interval of the current time step [t - \Delta t, t]. Therefore the given state and control bounds are
 * required to hold for the complete interval.
 */
SCIP_RETCODE PropODE::applyPropODE(SCIP* scip, int *nchgbds, SCIP_RESULT *result, unsigned int startTime)
{
   int outCount(0);

   /* Start the clock */
   SCIP_CLOCK* clock;
   SCIPcreateClock(scip,&clock);
   SCIPclockSetTime(clock,0);
   SCIPstartClock(scip, clock);

   /* Declare internal flags */
   SCIP_Bool infeasible(false); /* Know internally if we found infeasiblity */
   SCIP_Bool infiniteBound(false); /* Know internally if a bound went to infinity */
   SCIP_Bool strictBoundViolated(false); /* Know internally if a strict bound was violated */
   I4H::Statistics stats;
   int oldnchgbds = *nchgbds; /* private counter for changed bounds */
   int potentialBndChgs(0);


   /* Get structure */
   SDensureValidStructure(scip);
   ctrl::SDproblemStructureInterface* structure(SDgetStructure(scip) );

   /* Prepare out file */
   SCIP_CALL( prepareOutFile(structure->getStateVarNames()) );

   /* Write initial transproblem to file */
#ifdef SD_PROPODE_WRITE_PREPROP
   {
      char *paramstr2;
      std::ostringstream oss;
      SCIPgetStringParam(scip,"constraints/ctrlDifferential/outDir",&paramstr2);
      oss << paramstr2 << "propode_preprop_" << execCount_ << ".cip";
      SCIPdebugMessage("WRITING transformed preprop problem to file %s at execCount %i\n",oss.str().c_str(),execCount_);
      SCIPwriteTransProblem(scip_, oss.str().c_str(), std::string("cip").c_str(), false);
   }
#endif

   /** Create integrator **/
   char* discretization;
   SCIPgetStringParam(scip, "reading/vopreader/discretization", &discretization);
   //const char* discretization = "euler";
   IntervalODEintegrator integrator(scip_, discretization , dt_, intermediateSteps_, nStates_, nAlgebraic_, nControls_);
   integrator.rateEvaluator()->setXdot(structure->getXdotAlgebraic());
   integrator.rateEvaluator()->setAlgebraicExpressions(structure->getAlgebraicExpressions());
   integrator.setControlMode(IntervalODEintegrator::CONTROL_MODE_STARTMIDEND);

   /* Start timeIteration in structure to initialize integrator */
   int currentTime = structure->startTimeIteration(startTime);
   //TODO _SD: implement double structure::getProblemTime(int structureTime)
   integrator.setInitial(structure->getTinit() + startTime * structure->getTstep(), structure->getStateBounds());
   SCIPdbgMsg("initialized integrator: x = %s, z = %s\n", integrator.statesToString().c_str(), integrator.controlsToString().c_str());

   /* Set the control bounds at t = 0 */
   integrator.setControls(structure->getControlBounds());

   /* TODO: Removing this should not change anything */
   /* Save the state bounds at t = 0 to use as enclosure */
   SDproblemStructureInterface::BoundMap oldStateBounds = structure->getStateBoundsMap();

   /** Start integration loop */
   SCIP_Real t(startTime);
   int tStep(0);
   if (execCount_ >= outCount) { SCIPdbgMsg("dt_ = %f\n",dt_); }
   SCIP_Bool doingFine = true;
   for( currentTime = structure->incrementTime(); structure->timesLeft() && doingFine; currentTime = structure->incrementTime())
   {
      SCIPdbgMsg("Preparing for integration to currentTime %i\n",currentTime);

      /* Set control intervals from variables */
      //integrator.setControls(structure->getMaxControlBounds(oldControlBounds));
      integrator.setEndControls(structure->getControlBounds());
      SCIPdbgMsg("set integrator controls to %s\n",integrator.controlsToString().c_str());

      /* Get already known state bounds from variables */
      SBrateEvaluator::BoundMap currentStateBounds = structure->getStateBoundsMap();

      /* Step integrator with state bounds and parameters */
      integrator.step(oldStateBounds, currentStateBounds, structure->getXdotParams(currentTime - 1) );
      t = integrator.getT();
      tStep++;
      SCIPdbgMsg("after integrator step: step = %i, t = %f, currentTime = %i\n",tStep,t,currentTime);
      SCIPdbgMsg("integrator states: \n %s",intervalVecToString(integrator.getStates()).c_str());

      /* Write v and w to current outFile */
      integrator.writeStates(outFile_);

      SCIP_Bool applyTightenings(true);
      if (execCount_ >= outCount) {  SCIPdbgMsg("evaluating bounds\n"); }

      /* Check if we still produce at least one useful bound */
      if( integrator.isDiverging())
      {
         SCIPdebugMessage("PropODE calculated infinite bound, giving up\n");
         infiniteBound = true;
         doingFine = false;
      }

      /* Check if we violate strict bounds */
      if( !integrator.checkBounds(structure->getStrictBounds()))
      {
         SCIPdebugMessage("PropODE no longer conforms with strict bounds, giving up\n");
         strictBoundViolated = true;
         doingFine = false;
      }

      /* Foreach state and boundtype: check for infeasibility, check for and apply bound tightenings */
      int varCounter(0);
      for (structure->startStateVarIteration(); structure->stateVarsLeft() && doingFine ;structure->incrementStateVar())
      {
         SCIP_VAR* var = structure->getCurrentStateVar();
         if (true || SCIPvarGetStatus(var) == SCIP_VARSTATUS_LOOSE || SCIPvarGetStatus(var) == SCIP_VARSTATUS_COLUMN )
         {
            for (int bndType = SCIP_BOUNDTYPE_LOWER; bndType <=  SCIP_BOUNDTYPE_UPPER && doingFine; bndType++)
            {
               ++potentialBndChgs;
               SCIP_Real newBound = integrator.getState(varCounter, (SCIP_BOUNDTYPE) bndType);

               /* Check if a bound is infinity */
               if( false && (SCIPisInfinity(scip,-1.0* newBound) || SCIPisInfinity(scip, newBound)))
               {
                  SCIPdebugMessage("PropODE calculated infinite bound, giving up\n");
                  infiniteBound = true;
                  doingFine = false;
               }
               else
               {
                  if (addErrorTerms_)
                     newBound = newBound + (bndType == SCIP_BOUNDTYPE_LOWER ? -1.0*dtIntermediate_: dtIntermediate_);

                  if (    (bndType == SCIP_BOUNDTYPE_LOWER && SCIPisLE(scip, newBound, -1.0 * boundApplyCutoff_))
                             || (bndType == SCIP_BOUNDTYPE_UPPER && SCIPisGE(scip_, newBound, boundApplyCutoff_))      )
                  {
                     //SCIPdbgMsg("bound is outside of boundApplyCutoff\n");
                  }
                  else if /* If bound is improvement or proves infeasiblity */
                   (    (bndType == SCIP_BOUNDTYPE_LOWER && SCIPisGT(scip_, newBound, SCIPvarGetLbLocal(var)))
                       || (bndType == SCIP_BOUNDTYPE_UPPER && SCIPisLT(scip_, newBound, SCIPvarGetUbLocal(var)))
                  )
                  {
                     /* If the bound proves infeasiblity */
                     if (    (bndType == SCIP_BOUNDTYPE_LOWER && SCIPisGT(scip, newBound, SCIPvarGetUbLocal(var)))
                        || (bndType == SCIP_BOUNDTYPE_UPPER && SCIPisLT(scip, newBound, SCIPvarGetLbLocal(var))) )
                     {
                        SCIPdebugMessage("PropODE detected infeasiblity\n");
#ifdef SD_PROPODE_WRITE_INFEAS
                        char *paramstr2;
                        std::ostringstream oss;
                        SCIPgetStringParam(scip,"constraints/ctrlDifferential/outDir",&paramstr2);
                        oss << paramstr2 << "propode_infeas_" << infeasCount_ << ".cip";
                        SCIPdebugMessage("WRITING transformed problem to file %s at t=%i\n",oss.str().c_str(),currentTime);
                        SCIPwriteTransProblem(scip, oss.str().c_str(), std::string("cip").c_str(), false);
#endif
                        ++infeasCount_;
                        infeasible = true;
                        *result = SCIP_CUTOFF;
                        SCIPdebugMessage("leaving time loop at t = %i/%i because of detected infeasiblity\n", currentTime,structure->getLastTime());
                        doingFine = false;
                     }
                     else if( applyTightenings ) /* new bound is tightening, apply */
                     {

#if defined(SCIP_DBG) || defined(SCIP_DEBUG)
                        SCIP_Real oldBound = bndType == SCIP_BOUNDTYPE_LOWER ? SCIPvarGetLbLocal(var) : SCIPvarGetUbLocal(var);
                        SCIP_Real boundDiff = bndType == SCIP_BOUNDTYPE_LOWER ? newBound - SCIPvarGetLbLocal(var) : SCIPvarGetUbLocal(var) - newBound;
                        SCIP_Real relImprovement(boundDiff / (SCIPvarGetUbLocal(var) - SCIPvarGetLbLocal(var)) * 100);
                        SCIPdbgMsg("    Setting local %s bound of %s to %e\n",bndType == SCIP_BOUNDTYPE_LOWER ? "lower" : "upper", SCIPvarGetName(var), newBound);
                        SCIPdbgMsg("    Improved %s bound of %s by %f percent\n",bndType == SCIP_BOUNDTYPE_LOWER ? "lower" : "upper", SCIPvarGetName(var), relImprovement);
                        stats.addVal(relImprovement);
#endif

                        /* Perform boundchange */
                        if (bndType == SCIP_BOUNDTYPE_LOWER)
                           SCIP_CALL( SCIPchgVarLb(scip_, var, newBound) );
                        else if (bndType == SCIP_BOUNDTYPE_UPPER)
                           SCIP_CALL( SCIPchgVarUb(scip_, var, newBound) );
                        ++(*nchgbds);
                     } /* close: bound is tightening */
                  }
                  else
                  {
                     if (execCount_ >= outCount) {  SCIPdbgMsg("    %s Bound of %s is no improvement\n",bndType == SCIP_BOUNDTYPE_LOWER ? "Lower" : "Upper",SCIPvarGetName(var)); }
                  }
               } /* newbound is not infinite */
            } /* Loop over upper / lower bound */
         } /* VARTYPE is interesting */
         else
         {
            SCIPdbgMsg("not applying bounds because vartype is not interesting\n");
         }
         ++varCounter;
      } /* Loop over state vars */

      /* Remember this steps bounds for the next round */
      oldStateBounds = structure->getStateBoundsMap();
   }
   /* Summarize this run */
   SCIPdbgMsg("applied %i / %i possible bndchgs, leaving after step to t = %i after %.3f s\n",*nchgbds - oldnchgbds, potentialBndChgs, currentTime - 1, SCIPclockGetTime(clock));

   SCIPstopClock(scip_, clock);
   finalizeOutFile(std::string("#") + std::to_string(SCIPclockGetTime(clock)) + std::string(" s"));
   if (execCount_ >= outCount) {  SCIPdbgMsg("closed file\n"); }

   {
      SCIPdebugMessage("Exit applyPropODE%s after t=%i, %i/%i changes, [min,avg,max][%%] = [%.3f,%.3f,%.3f], %.3f s, %s\n",
         (infeasible ? " (infeasible)" : (infiniteBound ? " (infinite)" : (strictBoundViolated ? " (strictBoundViolated)" : ""))),
         currentTime - 1, stats.nVals(), potentialBndChgs, stats.min(), stats.mean(), stats.max(), SCIPclockGetTime(clock),
         (*result == SCIP_CUTOFF ? "CUTOFF" : (*nchgbds == 0 ? "DIDNOTFIND" : "REDUCEDDOM"))
      );
   }

   SCIPfreeClock(scip_, &clock);

   /* Write bounds to .bnd file */
   SCIP_Bool writeBounds = false;
   if (writeBounds)
   {
      std::ostringstream boundFileName;
      boundFileName << "data/transprob_" << std::to_string(execCount_) << ".bnd";
      SCIPdebugMessage("WRITING bounds to %s\n", boundFileName.str().c_str());
      SCIP_CALL( SCIPwriteTransProblem(scip_, boundFileName.str().c_str(), "bnd", FALSE) );
   }
   /* Write bounds to .cip file */
   SCIP_Bool writeAfterProp = false;
   if (writeAfterProp)
   {
      std::ostringstream boundFileName;
      boundFileName << "data/propode_postprop" << std::to_string(execCount_) << ".cip";
      SCIPdebugMessage("WRITING transprob to %s\n", boundFileName.str().c_str());
      SCIP_CALL( SCIPwriteTransProblem(scip_, boundFileName.str().c_str(), "cip", FALSE) );
   }

   if (*result == SCIP_CUTOFF)
   {
      SCIPdbgMsg("applyPropODE: returning  with result cutoff\n");
   }
   else if (*nchgbds == 0)
   {
      SCIPdbgMsg("applyPropODE: returning  with result didnotfind\n");
      *result = SCIP_DIDNOTFIND;
   }
   else
   {
      SCIPdbgMsg("applyPropODE: returning with result reduceddom\n");
      *result = SCIP_REDUCEDDOM;
   }

   return SCIP_OKAY;
}

/* Adds a global enclosure to the propagator data, discards a worse bound if it exists
 * @todo _SD: this should eventually move to the problem data, together with the instance variables */
SCIP_RETCODE PropODE::addGlobalEnclosure(int nState, SCIP_BOUNDTYPE boundType, SCIP_Real val)
{
   switch (boundType)
   {
   case SCIP_BOUNDTYPE_LOWER:
      if (globalEnclosureLbs_.find(nState) == globalEnclosureLbs_.end()) /* No previous global bound exists */
         globalEnclosureLbs_.insert(std::pair<int, SCIP_Real>(nState,val));
      else
         globalEnclosureLbs_[nState] = std::min(val, globalEnclosureLbs_[nState]);
      break;
   case SCIP_BOUNDTYPE_UPPER:
      if (globalEnclosureUbs_.find(nState) == globalEnclosureUbs_.end()) /* No previous global bound exists */
         globalEnclosureUbs_.insert(std::pair<int, SCIP_Real>(nState,val));
      else
         globalEnclosureUbs_[nState] = std::max(val,globalEnclosureUbs_[nState]);
      break;
   default:
      return SCIP_ERROR;
   }
   return SCIP_OKAY;
}
