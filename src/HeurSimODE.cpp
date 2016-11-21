//#define SCIP_DEBUG
//#define SCIP_DBG
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2012 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License.             */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#include
/**@file   HeurMaxCtrl.cpp
 * @brief  Maximum Control Heuristic
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "HeurSimODE.h"

using namespace sdscip;

/** destructor of primal heuristic to free user data (called when SCIP is exiting) */
SCIP_DECL_HEURFREE(HeurSimODE::scip_free)
{
   return SCIP_OKAY;
}


/** initialization method of primal heuristic (called after problem was transformed) */
SCIP_DECL_HEURINIT(HeurSimODE::scip_init)
{
   return SCIP_OKAY;
}


/** deinitialization method of primal heuristic (called before transformed problem is freed) */
SCIP_DECL_HEUREXIT(HeurSimODE::scip_exit)
{
   return SCIP_OKAY;
}


/** solving process initialization method of primal heuristic (called when branch and bound process is about to begin)
 *
 *  This method is called when the presolving was finished and the branch and bound process is about to begin.
 *  The primal heuristic may use this call to initialize its branch and bound specific data.
 *
 */
SCIP_DECL_HEURINITSOL(HeurSimODE::scip_initsol)
{
   return SCIP_OKAY;
}


/** solving process deinitialization method of primal heuristic (called before branch and bound process data is freed)
 *
 *  This method is called before the branch and bound process is freed.
 *  The primal heuristic should use this call to clean up its branch and bound data.
 */
SCIP_DECL_HEUREXITSOL(HeurSimODE::scip_exitsol)
{

   return SCIP_OKAY;
}


/** Open file and write header if writesols parameter is true */
SCIP_RETCODE HeurSimODE::prepareOutFile(std::vector<std::string>  stateVarNames, std::string reductionModeString)
{
   /* Prepare output file */
   std::ostringstream outFileName;
   SCIP_Bool writeFile;
   SCIP_CALL( SCIPgetBoolParam(scip_ ,"heuristics/simODE/writesols", &writeFile) );
   if (writeFile)
   {
      char* paramstr;
      SCIPgetStringParam(scip_ , "heuristics/simODE/outFilePrefix",&paramstr);
      outFileName << "_" << reductionModeString;
      outFileName << paramstr << "_0.dat";
      outFile_.open(outFileName.str());
      outFile_ << "#" << std::setw(3) << "t" << "\t";
      for (int i = 0; i < nStates_; ++i)
         outFile_ <<  stateVarNames[i] << "\t";
      outFile_ << std::endl;
   }
   return SCIP_OKAY;
}


/** Close the outfile */
SCIP_RETCODE HeurSimODE::finalizeOutFile(std::string message)
{
   if (outFile_.is_open())
   {
      outFile_ << message;
      outFile_.close();

      SCIPdbg( std::ostringstream outFileName);
      SCIPdbg( char* paramstr );
      SCIPdbg( SCIPgetStringParam(scip_ , "heuristics/simODE/outFilePrefix",&paramstr));
      SCIPdbg( outFileName << paramstr << "_0.dat" );
      SCIPdbg( SCIPdbgMsg("CLOSING outFile %s\n", outFileName.str().c_str()) );
   }

   return SCIP_OKAY;
}


/** execution method of primal heuristic MaxCtrl */
SCIP_DECL_HEUREXEC(HeurSimODE::scip_exec)
{
   /* No probdata, no heurSimODE (maybe called by subscip) */
   *result = SCIP_DIDNOTFIND;

   if( SCIPgetProbData(scip) == NULL)
      return SCIP_OKAY;

   /* Start the clock */
   SCIP_CLOCK* clock;
   SCIPcreateClock(scip,&clock);
   SCIPclockSetTime(clock,0);
   SCIPstartClock(scip, clock);

   I4H::Statistics stats;

   /* Get structure */
   SDensureValidStructure(scip);
   sdscip::SDproblemStructureInterface* structure(SDgetStructure(scip) );
   nControls_ = structure->getNControls();
   nStates_ = structure->getNStates();
   nAlgebraic_ = structure->getNAlgebraic();
   SCIPdbgMsg("set nAlgebraic_ to %i\n", nAlgebraic_);

   /** Create integrator **/
   char* discretization;
   SCIPgetStringParam(scip, "reading/vopreader/discretization", &discretization);

   //for(ReduceODEintegrator::REDUCTION_MODE mode = ReduceODEintegrator::REDUCTION_MODE_LOWER; mode <= ReduceODEintegrator::REDUCTION_MODE_MIDPOINT; mode = mode + 1) {
   //ReduceODEintegrator::REDUCTION_MODE mode = ReduceODEintegrator::REDUCTION_MODE::REDUCTION_MODE_LOWER;
   //for(ReduceODEintegrator::REDUCTION_MODE mode = ReduceODEintegrator::REDUCTION_MODE::REDUCTION_MODE_LOWER; mode <= ReduceODEintegrator::REDUCTION_MODE::REDUCTION_MODE_MIDPOINT; mode = mode + 1)
   for( ReduceODEintegrator::REDUCTION_MODE mode : ReduceODEintegrator::getReductionModeVector())
   {
      /* Declare internal flags */
      SCIP_Bool infeasible(false); /* Know internally if we found infeasibility */
      SCIP_Bool violatedBounds(false);
      SCIP_Bool infiniteBound(false); /* Know internally if a bound went to infinity */

	   /* Start clock */
	   SCIPclockSetTime(clock,0);
	   SCIPstartClock(scip, clock);

	   /* Create solution */
	   SCIPcreateOrigSol(scip_, &sol_, heur);

	   /* Initialize integrator */
      ReduceODEintegrator integrator(scip_, discretization , structure->getTstep(), 1, nStates_, nAlgebraic_, nControls_);
      SCIPdbgMsg("setting xDots\n");
      integrator.setXdots(structure->getXdotAlgebraic());
      integrator.setAlgebraicExpressions(structure->getAlgebraicExpressions());
      integrator.setReductionMode(mode);
      SCIPdbg(integrator.rateEvaluator()->printXdotAlgebraic() );

	   /* Prepare out file */
	   SCIP_CALL( prepareOutFile(structure->getStateVarNames(), integrator.getReductionModeString()));

      /* Start timeIteration in structure to initialize integrator */
      int currentTime = structure->startTimeIteration();
      integrator.setInitial(structure->getTinit(), structure->getStateBounds());
      SCIPdbgMsg("initialized integrator: \n %s \n %s\n",integrator.toString().c_str(), integrator.statesToString().c_str());

      /* Set initial values in solution */
      for (structure->startStateVarIteration(); structure->stateVarsLeft() ;structure->incrementStateVar())
      {
         SCIP_VAR* var = structure->getCurrentStateVarOrig();
         int varId = structure->getCurrentStateVarId();
         SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, integrator.getState(varId)) );
      }

      /* Set the control bounds at t = 0 */
      integrator.setControls(structure->getControlBounds());
      SCIPdbgMsg("integrator states: %s\n",integrator.statesToString().c_str());
      SCIPdbgMsg("integrator controls: %s\n",integrator.controlsToString().c_str());

      integrator.computeAlgebraic(structure->getXdotParams(currentTime));

      SCIPdbgMsg("-- after computing algebraic \n");
      SCIPdbgMsg("integrator states: %s\n",integrator.statesToString().c_str());
      SCIPdbgMsg("integrator controls: %s\n",integrator.controlsToString().c_str());

      /* Start integration loop */
      int tStep(0);
      SCIP_Bool doingFine = TRUE;

      SCIPdbgMsg("Set initial values in integrator:\n");
      SCIPdbgMsg("%s\n",integrator.statesToString().c_str());

      for (currentTime = structure->incrementTime(); structure->timesLeft() && doingFine ; currentTime = structure->incrementTime())
      {
         SCIPdbgMsg("----Integrating to currentTime %i -----\n",currentTime);
         /* Set control intervals from variables */
         /* TODO _SD: cycleControls missing? */
         integrator.setEndControls(structure->getControlBounds());
         SCIPdbgMsg("set integrator controls to %s\n",integrator.controlsToString().c_str());
         BoundMap currentStateBounds = structure->getStateBoundsMap();

         /* Step integrator with state bounds and parameters */
         integrator.step( structure->getXdotParams(currentTime - 1), structure->getXdotParams(currentTime) );
         tStep++;

         SCIPdbgMsg("-- after integrator step: step = %i, t = %f, currentTime = %i -- \n",tStep,integrator.getT(),currentTime);
         SCIPdbgMsg("integrator states: %s\n",integrator.statesToString().c_str());
         SCIPdbgMsg("integrator controls: %s\n",integrator.controlsToString().c_str());

         /* Write v and w to current outFile */
         integrator.writeStates(outFile_);

         /* Set state values in solution */
         for (structure->startStateVarIteration(); structure->stateVarsLeft() && doingFine ;structure->incrementStateVar())
         {
            SCIP_VAR* var = structure->getCurrentStateVarOrig();
            //SCIPdbgMsg("var is %s [%f,%f]\n",SCIPvarGetName(var), SCIPvarGetLbLocal(var), SCIPvarGetUbLocal(var));
            int varId = structure->getCurrentStateVarId();
            SCIP_Real val = integrator.getState(varId);
            if( SCIPisFeasLT(scip_, val, SCIPvarGetLbLocal(var)) || SCIPisFeasGT(scip_, val, SCIPvarGetUbLocal(var)) )
            {
               doingFine = false;
               violatedBounds = true;
               SCIPdbgMsg("solution value for state var %s of %f violates existing bounds [%f, %f], exiting\n", SCIPvarGetName(var), val, SCIPvarGetLbLocal(var), SCIPvarGetUbLocal(var));
               break;
            }
            SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, val) );

            /* If we are in sim mode, fix variable */
            if( integrator.getSolveMode() == ReduceODEintegrator::SOLVE_MODE_SIM)
            {
               SCIP_Bool fixed = FALSE;
               SCIP_Bool fixinfeasible = FALSE;
               SCIPfixVar(scip_, var, val, &fixinfeasible, &fixed);
               if (fixinfeasible)
               {
                  doingFine = false;
                  violatedBounds = true;
               }
               if (!fixed)
               {
                  SCIPdbgMsg("var %s was already fixed\n", SCIPvarGetName(var));
               }
            }
         }

         /* Set control values in solution */
         int varId = nStates_;
         SCIPdbgMsg("setting control variable values at t = %i:\n", currentTime - 1);
         for (structure->startControlVarAtTIteration(currentTime - 1); structure->controlVarsAtTLeft(currentTime - 1) && doingFine ;structure->incrementControlVarAtT())
         {
            SCIP_VAR* var(structure->getControlVarAtTOrig());

            SCIP_Real val = integrator.getControl(varId);
            SCIPdbgMsg("%s to %f\n", SCIPvarGetName(var), val);
            if( SCIPisFeasLT(scip_, val, SCIPvarGetLbLocal(var)) || SCIPisFeasGT(scip_, val, SCIPvarGetUbLocal(var)) )
            {
               doingFine = false;
               violatedBounds = true;
               break;
            }
            SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, val) );
            ++varId; /* TODO _SD: Get varid from SDVar once we get the SD var for the iteration */
         }

         /* Set algebraic values in solution */
         varId = nStates_ + nControls_;
         SCIPdbgMsg("setting algebraic variable values:\n");
         for (structure->startAlgebraicConsIteration(currentTime - 1); structure->algebraicConsLeft(currentTime - 1) && doingFine ;structure->incrementAlgebraicCons())
         {
            SCIP_VAR* var(structure->getAlgebraicVarOrig ());

            SCIP_Real val = integrator.getAlgebraic(varId);
            SCIPdbgMsg("%s: %f\n", SCIPvarGetName(var), val);
            if( SCIPisFeasLT(scip_, val, SCIPvarGetLbLocal(var)) || SCIPisFeasGT(scip_, val, SCIPvarGetUbLocal(var)) )
            {
               doingFine = false;
               violatedBounds = true;
               break;
            }
            SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, val) );

            /* If we are in sim mode, fix variable */
            if( integrator.getSolveMode() == ReduceODEintegrator::SOLVE_MODE_SIM)
            {
               SCIP_Bool fixed = FALSE;
               SCIP_Bool fixinfeasible = FALSE;
               SCIPfixVar(scip_, var, val, &fixinfeasible, &fixed);
               if (fixinfeasible)
               {
                  doingFine = false;
                  violatedBounds = true;
               }
               assert(fixed);
            }
            ++varId; /* TODO _SD: Get varid from SDVar once we get the SD var for the iteration */
         }
      }

      /* Do one more step to set values of superfluous control and algebraic vars at t = T */
      if( doingFine) {

         SCIPdebugMessage("----Last step: Integrating to currentTime %i -----\n",currentTime);
         integrator.computeAlgebraic(structure->getXdotParams(currentTime - 1));

         /* Set control values in solution */
         int varId = nStates_;
         SCIPdbgMsg("setting control variable values:\n");
         for (structure->startControlVarAtTIteration(currentTime -1) ; structure->controlVarsAtTLeft(currentTime -1)  ;structure->incrementControlVarAtT())
         {
            SCIP_VAR* var(structure->getControlVarAtTOrig());

            SCIP_Real val = integrator.getControl(varId);
            SCIPdbgMsg("%s: %f\n", SCIPvarGetName(var), val);
            SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, val) );
            ++varId; /* TODO _SD: Get varid from SDVar once we get the SD var for the iteration */
         }

         /* Set algebraic values in solution */
         varId = nStates_ + nControls_;
         SCIPdbgMsg("setting algebraic variable values:\n");
         for (structure->startAlgebraicConsIteration(currentTime -1 ); structure->algebraicConsLeft(currentTime - 1) ;structure->incrementAlgebraicCons())
         {
            SCIP_VAR* var(structure->getAlgebraicVarOrig());

            SCIP_Real val = integrator.getAlgebraic(varId);
            SCIPdbgMsg("%s: %f\n", SCIPvarGetName(var), val);
            SCIP_CALL( SCIPsetSolVal(scip_, sol_, var, val) );
            ++varId; /* TODO _SD: Get varid from SDVar once we get the SD var for the iteration */
         }
      }

      SCIP_Bool stored  = FALSE;
      SCIP_Real solTime = SCIPclockGetTime(clock);

      if (doingFine)
      {
         SCIP_Real obj = SCIPsolGetOrigObj(sol_);
         SCIPtrySolFree(scip_, &sol_, FALSE, TRUE, TRUE, TRUE, TRUE, &stored);
         //SCIPdebugMessage("Solution%s stored!\n", (stored ? "" : " NOT"));
         finalizeOutFile(std::string("#") + std::to_string(SCIPclockGetTime(clock)) + std::string(" s"));
         assert(stored  || (SCIPgetBestSol(scip_) != NULL));
         if (stored)
            *result = SCIP_FOUNDSOL;

         SCIPstopClock(scip_, clock);

         SCIPdebugMessage("Exit HeurSimODE %s, %f seconds for sim, %f total, obj: %f\n",
            (stored ? "(solution found)" : (infeasible ? "(infeasible)" : (infiniteBound ? "(infinite)" : (violatedBounds ? "(violatedBounds)" : "")))),
            solTime, SCIPclockGetTime(clock), obj);

         /* If we are in presolving and still in sim mode, inform user that problem is simulation */
         if( SCIPgetStage(scip) == SCIP_STAGE_PRESOLVING && integrator.getSolveMode() == ReduceODEintegrator::SOLVE_MODE_SIM)
         {
            SCIPinfoMessage(scip, NULL, "HeurSimODE: Detected pure simulation problem. All variables were fixed in presolving.\n");
         }
      }
      else
      {
         SCIPfreeSol(scip_, &sol_);
         SCIPdbgMsg("Exit HeurSimODE %s, %f seconds for sim, %f total, \n",
            (stored ? "(solution found)" : (infeasible ? "(infeasible)" : (infiniteBound ? "(infinite)" : (violatedBounds ? "(violatedBounds)" : "")))),
            solTime, SCIPclockGetTime(clock));
      }

   } /* End loop over reduction modes */

   SCIPfreeClock(scip_, &clock);


   return SCIP_OKAY;
}


/** clone method which will be used to copy a objective plugin */
SCIP_DECL_HEURCLONE(scip::ObjCloneable* HeurSimODE::clone)
{
   return new HeurSimODE(scip);
}
