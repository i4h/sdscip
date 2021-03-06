/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 2012-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*    Copyright (C) 2016      Helmut-Schmidt University Hamburg              */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Lesser General Public License        */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.*/
/*                                                                           */
/*                                                                           */
/* Based on SCIP - Solving Constraint Integer Programs                       */
/* Copyright (C) 2002-2016 Zuse Institute Berlin                             */
/* SCIP is distributed under the terms of the SCIP Academic Licence,         */
/* see file COPYING in the SCIP distribution.                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   HeurSimODE.cpp
 * @brief  Heuristic simulating sdo problems while fixing control variables
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

SCIP_RETCODE HeurSimODE::propagateInitial(SCIP* scip)
{
   sdscip::SDproblemStructureInterface* structure(SDgetStructure(scip) );

   /* Iterate explicit differential cons at 0 */

   for( structure->startAlgebraicConsIteration(0); structure->algebraicConsLeft(0); structure->incrementAlgebraicCons())
   {
      SCIP_CONS* cons(structure->getAlgebraicCons());
      SCIP_RESULT result;
      SCIP_CONS* transcons;

      if (cons == nullptr)
         continue;

      SCIP_CALL( SCIPgetTransformedCons(scip, cons, &transcons) );
      if( transcons == NULL || SCIPconsIsDeleted(transcons) == TRUE )
      {
         continue;
      }

      SCIPpropCons(scip, transcons, SCIP_PROPTIMING_ALWAYS, &result);
   }

   for( structure->startDiffConsIteration(0); structure->diffConsLeft(0); structure->incrementDiffCons())
   {
      SCIP_CONS * cons(structure->getDiffConsCons());
      if( cons != nullptr )
      {
         SCIP_RESULT result;
         SCIP_CONS* transcons;
         SCIPgetTransformedCons(scip, cons, &transcons);
         SCIPpropCons(scip, transcons, SCIP_PROPTIMING_ALWAYS, &result);
      }
   }
   return SCIP_OKAY;
}


/** execution method of primal heuristic MaxCtrl */
SCIP_DECL_HEUREXEC(HeurSimODE::scip_exec)
{
   *result = SCIP_DIDNOTFIND;

   /* No probdata, no heurSimODE (maybe called by subscip) */
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

   if (propagateInitial_ == TRUE && SCIPgetStage(scip) == SCIP_STAGE_PRESOLVING)
      SCIP_CALL(propagateInitial(scip) );

   /** Create integrator **/
   char* discretization;
   SCIPgetStringParam(scip, "reading/sdoreader/discretization", &discretization);

   /* Remember if previous loop found sim */
   SCIP_Bool isSim = false;

   for( ReduceODEintegrator::REDUCTION_MODE mode : ReduceODEintegrator::getReductionModeVector())
   {
      SCIPdebugMessage("Simulating in %s mode\n",ReduceODEintegrator::getReductionModeString(mode).c_str());

      if( isSim)
      {
         SCIPverbMessage(scip_, SCIP_VERBLEVEL_FULL, NULL, "Not running HeurSimODE because problem was already marked as simulation in previous run\n");
         break;
      }

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
         SCIPdbgMsg("Setting state var values\n");
         for (structure->startStateVarIteration(); structure->stateVarsLeft() && doingFine ;structure->incrementStateVar())
         {
            SCIP_VAR* var = structure->getCurrentStateVarOrig();
            int varId = structure->getCurrentStateVarId();
            SCIP_Real val = integrator.getState(varId);
            SCIPdbgMsg(" %s [%f,%f] = %f \n",SCIPvarGetName(var), SCIPvarGetLbLocal(var), SCIPvarGetUbLocal(var), val);
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
#ifdef SCIP_DEBUG
         SCIPtrySol(scip_, sol_, TRUE,  TRUE, TRUE, TRUE, TRUE, &stored);
#else
         SCIPtrySol(scip_, sol_, FALSE,  TRUE, TRUE, TRUE, TRUE, &stored);
#endif
         finalizeOutFile(std::string("#") + std::to_string(SCIPclockGetTime(clock)) + std::string(" s"));
         /* Only good reason for infeasible solutions in presolving is existence of path constraints */
         if( !stored && SCIPgetStage(scip)== SCIP_STAGE_PRESOLVING && SCIPgetBestSol(scip_) != NULL  )
         {
            SCIPwarningMessage(scip, "HeurSimODE computed complete but infeasible solution in %s mode\n", integrator.getReductionModeString().c_str());
            SCIPdebug( FILE* file );
            SCIPdebug( file = fopen("simode_debug.sol", "w") ) ;
            SCIPdebug( SCIPtrySol(scip_, sol_, TRUE,  TRUE, TRUE, TRUE, TRUE, &stored) );

            SCIPdebug( SCIPprintSol(scip_, sol_, file, TRUE));
            SCIPdebugMessage("Solution written to simode_debug.sol");
         }

         /* Save the solution if in presolving if savesols parameter is true */
         if (stored && savesols_ && SCIPgetStage(scip) == SCIP_STAGE_PRESOLVING )
         {
            std::ostringstream solFileName;
            solFileName << "HeurSimODE_" << ReduceODEintegrator::getReductionModeString(mode) << ".sol";
            FILE* file = fopen(solFileName.str().c_str(), "w");
            SCIP_CALL( SCIPprintSol(scip_, sol_, file, TRUE) );
            SCIPdbgMsg("Wrote solution to file %s\n", solFileName.str().c_str());
         }

         SCIPfreeSol(scip_, &sol_);

         if (stored)
            *result = SCIP_FOUNDSOL;

         SCIPstopClock(scip_, clock);

         SCIPdebugMessage("Exit %s HeurSimODE %s, %f seconds for sim, %f total, obj: %f\n",
            ReduceODEintegrator::getReductionModeString(mode).c_str(),
            (stored ? "(solution found)" : (infeasible ? "(infeasible)" : (infiniteBound ? "(infinite)" : (violatedBounds ? "(violatedBounds)" : "")))),
            solTime, SCIPclockGetTime(clock), obj);

         /* If we are in presolving and still in sim mode, inform user that problem is simulation */
         if( SCIPgetStage(scip) == SCIP_STAGE_PRESOLVING && integrator.getSolveMode() == ReduceODEintegrator::SOLVE_MODE_SIM)
         {
            isSim = true;
            SCIPinfoMessage(scip, NULL, "HeurSimODE: Detected pure simulation problem. All variables were fixed in presolving.\n");
         }
      }
      else
      {
         SCIPfreeSol(scip_, &sol_);
         SCIPdbgMsg("Exit %s HeurSimODE %s, %f seconds for sim, %f total, \n",
            ReduceODEintegrator::getReductionModeString(mode).c_str(),
            (infeasible ? "(infeasible)" : (infiniteBound ? "(infinite)" : (violatedBounds ? "(violatedBounds)" : ""))),
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
