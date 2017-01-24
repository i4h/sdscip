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

/**@file   PropOBRA.cpp
 * @brief  Propagating bounds of control problems by solving auxiliary OBRAs
 * @author Ingmar Vierhaus
 *
 * @todo: SD-Plugins in subscips:
 *        - Add problem structure plugin
 *        - Write problem structure when creating subscips
 *        - Add and enable HeurMaxCtrl and PropODE plugins to subscip
 */

#include "PropOBRA.h"

#define HASHTABLESIZE_FACTOR 5

using namespace sdscip;

/** Helper function used for display of run statistics */
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
	return std::pair<B,A>(p.second, p.first);
}

/** Helper function used for display of run statistics */
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
	std::multimap<B,A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
			flip_pair<A,B>);
	return dst;
}

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

/** writes the current progress to a file */
SCIP_RETCODE PropOBRA::writeProgress(SCIP_Real solvingTime)
{
   std::vector<SCIP_Interval> stateBounds = structure_->getStateBounds();

   if (!progressOfs_.is_open()) {
      progressOfs_.open(progressFile_, std::ofstream::out);
   }

   progressOfs_ << structure_->getCurrentTime() << "\t";
   progressOfs_ << solvingTime << "\t";
   for(unsigned int i = 0; i < structure_->getNStates(); ++i) {
      progressOfs_ << stateBounds[i].inf << "\t" << stateBounds[i].sup << "\t";
   }
   progressOfs_ << "\n";
   progressOfs_.flush();

   return SCIP_OKAY;
}

/** close the current progress file */
SCIP_RETCODE PropOBRA::closeProgressFile(SCIP_Real solvingTime)
{
   if (progressOfs_.is_open())
      progressOfs_.close();

   return SCIP_OKAY;
}

/** displays the progress of propOBRA to the user as a horizontal progress bar */
SCIP_RETCODE PropOBRA::printProgress()
{
   SCIP_Real tStart = structure_->getTinit();
   SCIP_Real tEnd = structure_->getTfinal();
   SCIP_Real tSpan = tEnd - tStart;
   int nSteps = structure_->getLastTime();
   int width = 80;
   int w = 3;
   int precision = 0;
   if (tEnd <= 99) {
      precision = 1;
      w = 4;
   }
   int numWidth = w + (precision == 0 ? 0 : precision + 1);

   /*                     ]  OBRA: [    T = ... / ...  */
   int barWidth = width - 1  - 7      - 2 * numWidth - 6;

   SCIP_Real percent = (SCIP_Real) currentTime_ / (SCIP_Real) nSteps;
   int activeSegments = barWidth * percent;

   std::cout << "OBRA: [";
   for (int i = 0; i < barWidth; ++i) {
      if (i < activeSegments)
         std::cout << ("-");
      else if (i == activeSegments)
         std::cout << (">");
      else
         std::cout << (" ");
   }
   std::cout << "] T = " << std::fixed << std::setw(w) << std::setprecision(precision) <<  (tStart + percent * tSpan) << " / " << tEnd << "\r";
   fflush(stdout);

   return SCIP_OKAY;
}


SCIP_RETCODE PropOBRA::printSummary( int nSubscips, SCIP_Real aggSolvingTime, SCIP_Bool addCuts, SCIP_Bool addMultiTimeCuts, int breakTime, SCIP_CLOCK* propClock)
{
   std::multimap<int, std::string> dst;
   std::map<int, std::string>::iterator iter;

   SCIPinfoMessage( scip_, NULL, "-------------------------------------------------------------------------\n" );
   SCIPinfoMessage(scip_,NULL,"| CtrlDifferential General Statistics in depth %5i                    |\n",SCIPgetDepth(scip_));
   SCIPinfoMessage(scip_,NULL,"| HistoricCons parameter:          %-4i                                 |\n",lookback_);
   SCIPinfoMessage( scip_, NULL, "| Total time elapsed:             %1.5e s                         |\n", SCIPclockGetTime( propClock ) );
   SCIPinfoMessage( scip_, NULL, "| Last propagated Time:           %-4i                                  |\n", ( breakTime < 0 ? currentTime_ : breakTime - 1 ) );
   SCIPinfoMessage(scip_,NULL,"| Number of solved Subscips:       %-5i                                |\n",nSubscips);
   SCIPinfoMessage(scip_,NULL,"| Total Solving Time:              %1.5e s                        |\n",aggSolvingTime);
   SCIPinfoMessage(scip_,NULL,"| Avrg Time per Subscip:           %1.5e s                        |\n",aggSolvingTime / nSubscips);
   SCIPinfoMessage(scip_,NULL,"| Time solving subscips [%]:       %-3.2f                                |\n",aggSolvingTime / SCIPclockGetTime(propClock) * 100.0);
   SCIPinfoMessage(scip_,NULL,"-------------------------------------------------------------------------\n");
   SCIPinfoMessage(scip_,NULL,"| Constant Time Statistics - Direct Bounds                              |\n");
   SCIPinfoMessage(scip_,NULL,"| Number of considered bounds:     %-4i                                 |\n",constTimePattern_.stats_.nDirectBounds);
   SCIPinfoMessage(scip_,NULL,"| Number of changed bounds:        %-4i                                 |\n",constTimePattern_.stats_.nUpdatedBounds);
   SCIPinfoMessage(scip_,NULL,"| Updated Bounds [percent]:        %-3.2f                               |\n",(double) constTimePattern_.stats_.nDirectBounds / (double) constTimePattern_.stats_.nUpdatedBounds * 100);
   SCIPinfoMessage(scip_,NULL,"| Optimal Bounds [percent]:        %-3.2f                               |\n",(double) constTimePattern_.stats_.nDirectBounds / (double) constTimePattern_.stats_.nDirectOptimal * 100);
   SCIPinfoMessage(scip_,NULL,"| Aggregated Remaining Bounds:     %1.5e                          |\n",constTimePattern_.stats_.aggRemainingBounds);
   SCIPinfoMessage(scip_,NULL,"| Average Remaining Bounds:        %1.5e                          |\n",constTimePattern_.stats_.aggRemainingBounds / constTimePattern_.stats_.nDirectBounds / 2);
   SCIPinfoMessage(scip_,NULL,"| Aggregated Bound Reduction:      %1.5e                          |\n",constTimePattern_.stats_.aggBoundReduction);
   SCIPinfoMessage(scip_,NULL,"| Bound Reduction per Variable:    %1.5e                          |\n",constTimePattern_.stats_.aggBoundReduction / constTimePattern_.stats_.nDirectBounds / 2);
   SCIPinfoMessage(scip_,NULL,"| Aggregated Bounds Solving Time:  %1.5e s                        |\n",constTimePattern_.stats_.aggDirectSolutionTime);
   SCIPinfoMessage(scip_,NULL,"| Bounds Solving Time per subscip: %1.5e s                        |\n",constTimePattern_.stats_.aggDirectSolutionTime / constTimePattern_.stats_.nDirectBounds);
   if( addCuts == TRUE)
   {
      SCIPinfoMessage(scip_,NULL,"-------------------------------------------------------------------------\n");
      SCIPinfoMessage(scip_,NULL,"| Constant Time Statistics - Cuts                                       |\n");
      SCIPinfoMessage(scip_,NULL,"| Number of considered cuts:       %-4i                                 |\n",constTimePattern_.stats_.nCuts);
      SCIPinfoMessage(scip_,NULL,"| Useful Cuts [percent] :          %-3.2f                               |\n",(double) constTimePattern_.stats_.nCutsUseful / (double) constTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip_,NULL,"| Optimal Cuts  [percent] :        %-3.2f                               |\n",(double) constTimePattern_.stats_.nCutsOptimal / (double) constTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip_,NULL,"| Aggregated Cuts Solving Time:    %1.5e s                        |\n",constTimePattern_.stats_.aggCutsSolutionTime);
      SCIPinfoMessage(scip_,NULL,"| Cuts Solving Time per subscip:   %1.5e s                        |\n",constTimePattern_.stats_.aggCutsSolutionTime / constTimePattern_.stats_.nCuts);
      dst = flip_map(constTimePattern_.stats_.usefulCutDistribution);
      for( iter = dst.begin(); iter != dst.end(); ++iter) {
         SCIPinfoMessage(scip_,NULL,"|   Percentage of type %8s*:   %-3.1f                                |\n",iter->second.c_str(),(double) iter->first / (double) constTimePattern_.stats_.nCutsUseful * 100.0);
      }
   }
   if( addMultiTimeCuts == TRUE)
   {
      SCIPinfoMessage(scip_,NULL,"-------------------------------------------------------------------------\n");
      SCIPinfoMessage(scip_,NULL,"| Multi Time Statistics - Cuts                                          |\n");
      SCIPinfoMessage(scip_,NULL,"| Number of considered cuts:       %-4i                                 |\n",multiTimePattern_.stats_.nCuts);
      SCIPinfoMessage(scip_,NULL,"| Useful Cuts [percent] :          %-3.2f                               |\n",(double) multiTimePattern_.stats_.nCutsUseful / (double) multiTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip_,NULL,"| Optimal Cuts  [percent] :        %-3.2f                               |\n",(double) multiTimePattern_.stats_.nCutsOptimal / (double) multiTimePattern_.stats_.nCuts * 100.0);
      SCIPinfoMessage(scip_,NULL,"| Aggregated Cuts Solving Time:    %1.5e s                        |\n",multiTimePattern_.stats_.aggCutsSolutionTime);
      SCIPinfoMessage(scip_,NULL,"| Cuts Solving Time per subscip:   %1.5e s                        |\n",multiTimePattern_.stats_.aggCutsSolutionTime / multiTimePattern_.stats_.nCuts);
      dst = flip_map(multiTimePattern_.stats_.usefulCutDistribution);
      for( iter = dst.begin(); iter != dst.end(); ++iter) {
         SCIPinfoMessage(scip_,NULL,"|   Percentage of type %8s*:   %-3.1f                                |\n",iter->second.c_str(),(double) iter->first / (double) multiTimePattern_.stats_.nCutsUseful * 100.0);
      }
      SCIPinfoMessage( scip_, NULL, "-------------------------------------------------------------------------\n" );
      SCIPinfoMessage(scip_,NULL,"*: Unless variables are always orderd correctly this is not yet meaningful\n");
   }
   SCIPinfoMessage( scip_, NULL, "-------------------------------------------------------------------------\n" );

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::writeAfterProp( int breakTime)
{
   SCIP_Bool writeAfterPropParam;
   if( SCIPgetBoolParam( scip_, "propagating/obra/writeAfterProp", &writeAfterPropParam ) && writeAfterPropParam )
   {
      char* outfilestr, *outdirstr;
      std::ostringstream oss,bndoss;
      SCIPgetStringParam( scip_, "propagating/obra/outFile", &outfilestr );
      SCIPgetStringParam( scip_, "propagating/obra/outDir", &outdirstr );
      oss << outdirstr << outfilestr << "_" << lookback_ << "_" << ( breakTime < 0 ? currentTime_ : breakTime - 1 ) << ".cip";

      SCIPdebugMessage( "WRITING transformed problem to file %s at t=%i\n", oss.str().c_str(), currentTime_ );
      SCIPwriteTransProblem(scip_, oss.str().c_str(),"cip", false);
      bndoss << outdirstr << outfilestr << "_" << lookback_ << "_" << currentTime_ << ".bnd";
      SCIPdebugMessage("WRITING bounds to file %s at t=%i\n",bndoss.str().c_str(),currentTime_);
      SCIPwriteTransProblem(scip_, bndoss.str().c_str(), "bnd", false);

      SCIPdebugMessage( "done writing\n" );
   }

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::writeCuts()
{
   SCIP_Bool writeCutsAfterProp = true;
   if( writeCutsAfterProp )
   {
      char* outfilestr = "cuts.sdc";

      SCIPdebugMessage( "WRITING cuts to file %s\n", outfilestr);

      SCIP_CALL( SCIPwriteTransProblem(scip_, "cuts.sdc", "sdc", FALSE) );

      SCIPdebugMessage( "done writing\n" );
   }

   return SCIP_OKAY;
}

/** initialization method of propagator */
SCIP_DECL_PROPINIT(PropOBRA::scip_init)
{
   return SCIP_OKAY;
}

/** execution method of propagator */
SCIP_DECL_PROPEXEC(PropOBRA::scip_exec)
{
   SCIP_CALL( applyOBRA(result) );
   return SCIP_OKAY;
}

/** presolving method of propagator */
SCIP_DECL_PROPPRESOL( PropOBRA::scip_presol )
{
   SCIPdebugMessage( "entered Presolving of Constraintless Conshdlr CtrlDifferential \n" );

   SDensureValidStructure(scip );

   SCIPdebugMessage( "Running Propagation of CtrlDifferential routine as part of presolving\n" );

   SCIP_CALL( applyOBRA(result) );

   return SCIP_OKAY;
}


/** apply one round of obra */
SCIP_RETCODE PropOBRA::applyOBRA(SCIP_RESULT* result)
{

   /* Make sure parameters are the way we want them */
   {
      SCIP_Bool val;
      SCIP_CALL(SCIPgetBoolParam(scip_, "presolving/donotmultaggr", &val));
      assert(val == TRUE);
   }

   /* Don't run in probing */
   if( SCIPinProbing( scip_ ) )
      return SCIP_OKAY;

   SCIP_CLOCK* propClock;

   /* Start timing */
   SCIP_CALL( SCIPclockCreate(& propClock , SCIP_CLOCKTYPE_DEFAULT) );
   SCIPclockSetTime(propClock,0);
   SCIPstartClock(scip_, propClock);

   /* Get parameters on how to run */
   int writeFreq;
   SCIP_Bool addCuts;
   SCIP_Bool addMultiTimeCuts;
   int cutFreq;
   SCIP_CALL( SCIPgetIntParam( scip_, "propagating/obra/writeFreq", &writeFreq ) );
   SCIP_CALL( SCIPgetBoolParam( scip_, "propagating/obra/addCuts", &addCuts ) );
   SCIP_CALL( SCIPgetBoolParam( scip_, "propagating/obra/addMultiTimeCuts", &addMultiTimeCuts ) );
   SCIP_CALL( SCIPgetIntParam( scip_, "propagating/obra/cutFreq", &cutFreq ) );

   /* Configure the constTime,multiTime  and algebraic PropagationPatterns */
   constTimePattern_.setCutConf3d( cutConf3d_ );
   constTimePattern_.setUseUnitCuts(false);
   multiTimePattern_.setUseUnitCuts(useUnitCuts_);
   algebraicPattern_.setUseUnitCuts(true);
   algebraicPattern_.setAddCuts(false);
   controlPattern_.setUseUnitCuts(true);
   controlPattern_.setAddCuts(false);


   structure_ = SDgetStructure(scip_);

   SCIP_Real totalBoundReduction( 0 );
   int nPropagatedVars( 0 );
   int nchgbds( 0 );

   SCIPinfoMessage(scip_, NULL, "\n");

   for( currentTime_ = structure_->startTimeIteration(); structure_->timesLeft(); currentTime_ = structure_->incrementTime())
   {
      if( breakTime_ == -1 || currentTime_ < breakTime_)
      {
         SCIPdebugMessage("t = %i\n",currentTime_);
         if( writeFreq != -1 && currentTime_ % writeFreq == 0)
         {
            char* paramstr,*paramstr2;
            std::ostringstream oss;
            SCIPgetStringParam(scip_,"propagating/obra/outFile",&paramstr);
            SCIPgetStringParam(scip_,"propagating/obra/outDir",&paramstr2);
            oss << paramstr2 << paramstr << "_" << lookback_ << "_" << currentTime_ << ".cip";
            SCIPdebugMessage("WRITING transformed problem to file %s at t=%i\n",oss.str().c_str(),currentTime_);
            SCIPwriteTransProblem(scip_, oss.str().c_str(), "cip", false);
         }

         if( boundWriteFreq_!= -1 && currentTime_ % boundWriteFreq_ == 0)
         {
            SCIPdebugMessage("WRITING bounds to file %s at t=%i\n","current_bounds.bnd",currentTime_);
            SCIPwriteTransProblem(scip_, "current_bounds.bnd", "bnd", false);
         }
         /*
          * Create, allocate and configure Subscip
          */
         SCIP_CALL( createAndConfigureSubscip() );

         SCIP_Bool boundsDiverge(false);
         SCIPdbgMsg("calling propBoundsAtTwithSubscip, currentTime = %i\n",currentTime_);
         SCIP_CALL( propBoundsAtTwithSubscip(&nPropagatedVars, &nchgbds, &totalBoundReduction, &boundsDiverge));

         /* Clean up allocated maps, empty subscip_ */
         SCIPcppDbgMsg("Freeing hashmaps" << std::endl);
         SCIPhashmapFree(&varmap_);
         SCIPhashmapFree(&consmap_);
         /* Free subscip_ */
         SCIPcppDbgMsg("Freeing subscip_" << std::endl);
         SCIP_CALL( SCIPfree(&subscip_) );

         if( boundsDiverge)
         {
            SCIPdebugMessage("breaking for boundsDiverge at t = %i\n",currentTime_);
            break;
         }

      } /* Close stop iteration at given time */
      else if( currentTime_ == breakTime_)
      {
         SCIPinfoMessage(scip_, NULL, "Stopping at t = %i, (set via parameter prop/obra/breakTime)\n", breakTime_);
         SCIPdebugMessage("breaking for breakTime\n");
         break;
      }
      printProgress();
      writeProgress(SCIPclockGetTime(propClock));
   } /* Close iteration over times */

   SCIPclockStop( propClock, scip_->set );

   int nSubscips = constTimePattern_.stats_.nSubscips + constTimePattern_.stats_.nSubscips;
   SCIP_Real aggSolvingTime =    constTimePattern_.stats_.aggSolutionTime
                               + multiTimePattern_.stats_.aggSolutionTime
                               + algebraicPattern_.stats_.aggSolutionTime
                               + controlPattern_.stats_.aggCutsSolutionTime;

   /* Display the summary of this obra run */
   printSummary(nSubscips, aggSolvingTime, addCuts, addMultiTimeCuts, breakTime_, propClock);
   closeProgressFile(SCIPclockGetTime(propClock));

   SCIP_CALL( writeAfterProp(breakTime_) );

   SCIP_CALL( writeCuts() );

   SCIPclockFree( &propClock );

   *result = SCIP_DIDNOTFIND;
   return SCIP_OKAY;
}


SCIP_RETCODE PropOBRA::prepareConstTimeStatePattern()
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   constTimePattern_.clearVars();
   constTimePattern_.setScip(scip_);
   constTimePattern_.setSubscip(subscip_);
   constTimePattern_.setCurrentTime(currentTime_);
   SCIP_CALL( constTimePattern_.setAddCuts(addCuts_) );

   /* Iterate over variables that will create the space of the linear cut */
   for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
   {
      SCIP_VAR* var(structure_->getDiffConsVar());
      if( var != NULL)
      {
         /* Add the scip and subscip variables corresponding the the differential variable */
         assert( SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(var)) != NULL);
         constTimePattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(var)));
         SCIPdebugMessage("added variable  %s\n",SCIPvarGetName(var));
      }
      else
      {
         SCIPdebugMessage("Constraint %s has no forward variable\n",SCIPconsGetName(pairIt->first));
      }
   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::prepareAlgebraicPattern()
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   algebraicPattern_.clearVars();
   algebraicPattern_.setScip(scip_);
   algebraicPattern_.setSubscip(subscip_);
   algebraicPattern_.setCurrentTime(currentTime_);

   /* Iterate over algebraic variables and add to pattern */
   for( structure_->startLevelIteration(currentTime_ - 1); structure_->levelsLeft(currentTime_ - 1); structure_->incrementLevel())
   {
      for( structure_->startLevelConsIteration(); structure_->levelConsLeft() ; structure_->incrementLevelCons())
      {
         if( structure_->currentLevelConsHasVar() ) /* Only if constraint has forward variable */
         {
            SCIP_CONS* cons(structure_->getCurrentLevelConsCons());
            SCIP_VAR* var(structure_->getCurrentLevelConsOrigVar());
            assert(cons != NULL);

            if( !SCIPconsIsDeleted(cons) )
            {
               SCIPdebugMessage("Adding variable %s to algebraicPattern_\n", SCIPvarGetName(var));
               algebraicPattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(var)));
            }
            else
            {
               SCIPdbgMsg("not adding deleted cons to algebraicPattern %s\n", SCIPconsGetName(cons));
            }

         } /* Close only constraints with forward variable */
      } /* Close loop over constraints of level */
   } /* Close loop over levels */
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::prepareControlPattern()
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   controlPattern_.clearVars();
   controlPattern_.setScip(scip_);
   controlPattern_.setSubscip(subscip_);
   controlPattern_.setCurrentTime(currentTime_);

	   SCIPdebugMessage(" Step 8: Propagating bounds to control variables at t=%i\n",currentTime_);
	   for( structure_->startControlVarIteration(currentTime_ - 1); structure_->controlVarsLeft(currentTime_ - 1);structure_->incrementControlVar() )
	   {
		   SCIP_VAR* var(structure_->getControlVarAtTOrig());
		   SCIP_VAR* subscipVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(var));
		   assert(subscipVar != NULL);
		   controlPattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(var)));
	   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::prepareMultiTimeStatePattern(SCIP_VAR* lastVar)
{

   VarVec subscipVars;

   if( lastVar == NULL)
   {
      SCIPdebugMessage("Constraint has no forward variable\n");
      return SCIP_OKAY;
   }

   /* Configure pattern */
   multiTimePattern_.clearVars();
   multiTimePattern_.setScip(scip_);
   multiTimePattern_.setSubscip(subscip_);
   multiTimePattern_.setCurrentTime(currentTime_);

   std::vector<SCIP_VAR*> lastVars(structure_->getDiffConsLastVars(multiTimeCutLookback_));

   /* Add the scip and subscip variables corresponding the the differential variable */
   SCIPdbgMsg("adding variable %s\n",SCIPvarGetName(lastVar));
   multiTimePattern_.addVar(lastVar, (SCIP_VAR*) SCIPhashmapGetImage(varmap_,SCIPvarGetTransVar(lastVar)));
   boost::cmatch matches;

   if( !boost::regex_match(SCIPvarGetName(lastVar), matches, structure_->getVarRegex() ))
      assert(false);

   std::string varName(matches[1].first,matches[1].second);
   std::string varTimeString(matches[5].first,matches[5].second);
   std::string varControlString(matches[2].first,matches[2].second);
   std::string varLevelString(matches[3].first,matches[3].second);
   std::string varTypeString(matches[4].first,matches[4].second);

   /* Iterate over previous variables of the same state and add to pattern */
   for( int i=1; i <= multiTimeCutLookback_ - 1; ++i)
   {
      SCIP_VAR* var;
      std::ostringstream oss;
      oss << "t_" << varName << "(" << currentTime_ - i << ")";
      var = SCIPfindVar(scip_,oss.str().c_str());
      /* Make sure variable exists in subscip */
      SCIP_VAR* subscipVar;
      subscipVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap_,var);
      if( subscipVar != NULL)
    	  multiTimePattern_.addVar(var, subscipVar);
   }

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::createAndConfigureSubscip()
{
   assert(scip_ != NULL);

   SCIP_CALL( SCIPcreate(&subscip_) );

   /* Include default plugins */
   SCIP_CALL(SCIPincludeDefaultPlugins(subscip_));

   /* --- Configure subscip for obra ---- */

   /* do not abort subproblem on CTRL-C */
   SCIP_CALL( SCIPsetBoolParam(subscip_, "misc/catchctrlc", FALSE) );

#ifndef SCIP_DEBUG
   /* disable statistic timing inside sub SCIP */
   SCIP_CALL( SCIPsetBoolParam(subscip_, "timing/statistictiming", FALSE) );
#endif

   /* forbid call of heuristics and separators solving sub-CIPs */
   SCIP_CALL( SCIPsetSubscipsOff(subscip_, TRUE) );

   /* --- Configure subscip from obra parameters  ---- */

   /* Set reoptimization depending on obra parameters */
   if( reoptimize_ == TRUE )
   {
      SCIP_CALL( SCIPsetBoolParam(subscip_, "reoptimization/enable", TRUE));
   }

   /* Set timelimit depending on obra parameters */
   SCIP_CALL( SCIPsetRealParam(subscip_,"limits/time",subscipTimeLimit_) );

   /* Set nodelimit depending on obra parameters*/
   SCIP_CALL( SCIPsetLongintParam(subscip_,"limits/nodes",subscipNodeLimit_) );

   /* Set gaplimit depending on obra parameters*/
   SCIP_CALL( SCIPsetRealParam(subscip_,"limits/gap",subscipGapLimit_) );

   /* Mute subscips depending on obra parameters*/
   if(subscipMute_ == true)
   {
      SCIP_CALL( SCIPsetIntParam(subscip_, "display/verblevel", 0) );
   }

   /* Create and allocate consmap and varmap
    * The varmap will map transformed variables of the main scip to original variables of the subscip
    * */
   SCIP_CALL( SCIPhashmapCreate(&consmap_, SCIPblkmem(subscip_), SCIPgetNConss(scip_)) );
   SCIP_CALL( SCIPhashmapCreate(&varmap_, SCIPblkmem(subscip_), SCIPcalcHashtableSize(SCIPgetNVars(scip_))) );

   return SCIP_OKAY;

}

/** Adds a constraint in scip with its variables to subscip
 *  and copies the bounds of the variables  */
SCIP_RETCODE PropOBRA::addConsWithVars(SCIP_CONS* currentCons, SCIP_Bool noObj, SCIP_Bool global, SCIP_Bool copysol)
{
   int nConsVars;
   SCIP_VAR** consvars;
   SCIP_Bool success;
   SCIP_CONS* targetcons = NULL;
   SCIP_SOL* scipSol;

   assert(currentCons != NULL);
   assert(scip_ != NULL);
   assert(subscip_ != NULL);
   assert(varmap_ != NULL);
   assert(consmap_ != NULL);

   scipSol = SCIPgetBestSol(scip_);

   SCIPdebugMessage("    adding cons %s with Vars from scip \n",SCIPconsGetName(currentCons));

   if (SCIPconsIsOriginal(currentCons))
      currentCons = SCIPconsGetTransformed(currentCons);

   assert(currentCons != NULL);

    //Add constraint to subscip

   SCIP_CONSHDLR* conshdlr;
   conshdlr = SCIPconsGetHdlr(currentCons);
   SCIP_CALL( SCIPgetConsCopy(scip_, subscip_, currentCons, &targetcons, conshdlr, varmap_, consmap_, NULL,
         SCIPconsIsInitial(currentCons), SCIPconsIsSeparated(currentCons),
         SCIPconsIsEnforced(currentCons), SCIPconsIsChecked(currentCons),
         SCIPconsIsPropagated(currentCons), FALSE, SCIPconsIsModifiable(currentCons),
         SCIPconsIsDynamic(currentCons), SCIPconsIsRemovable(currentCons), FALSE, TRUE, &success) );


   /* Set original bounds in target scip from local/global bounds in source scip
    * necessary, since the this runs in the presolving of the source scip only original bounds are copied */

   SCIP_CALL( SCIPgetConsNVars(scip_, currentCons, &nConsVars, &success) );
   assert(success);
   SCIP_CALL( SCIPallocBufferArray(scip_, &consvars, nConsVars) );
   SCIP_CALL( SCIPgetConsVars(scip_, currentCons, consvars, nConsVars, &success) );
   assert(success);

   for( int v = 0; v < nConsVars; v++ )
   {
      SCIP_VAR* sourcevar = consvars[v];
      SCIP_VAR* targetvar = (SCIP_VAR*) SCIPhashmapGetImage(varmap_,consvars[v]);

      SCIPdebugMessage("    considering %s variable %s %p\n",SCIPvarIsOriginal(consvars[v]) ? "original" : "transformed", SCIPvarGetName(consvars[v]), (void*) consvars[v]);

      assert(targetvar != NULL);
      assert((global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)) <= (global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));
      SCIPchgVarLb(subscip_, targetvar, global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar));
      SCIPchgVarUb(subscip_, targetvar, global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar));
      assert(SCIPisEQ(scip_, SCIPvarGetLbLocal(targetvar), global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)));
      assert(SCIPisEQ(scip_, SCIPvarGetUbLocal(targetvar), global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));

      if (noObj)
         SCIP_CALL( SCIPchgVarObj(subscip_,targetvar,0) );

      if (scipSol != NULL && copysol == TRUE)
      {
         SCIP_Real solVal = SCIPgetSolVal(scip_,scipSol,consvars[v]);
         (*solMap_)[targetvar] = solVal;
      }

   }
   SCIPfreeBufferArray(scip_, &consvars); //TODO _SD allocating buffer outside of loop could increase performance?

   /* add the copied constraint to target SCIP if the copying process was valid */
   if( success )
   {
      SCIPdebugMessage("    copied constraint %s to subscip\n",SCIPconsGetName(currentCons));
      assert(targetcons != NULL);
       /* add constraint to target SCIP */
       SCIP_CALL( SCIPaddCons(subscip_, targetcons) );
       /* release constraint once for the creation capture */
       SCIP_CALL( SCIPreleaseCons(subscip_, &targetcons) );
   }
   else
   {
      SCIPdebugMessage("failed to copy constraint %s\n", SCIPconsGetName(currentCons));
      assert(FALSE);
   }

   return SCIP_OKAY;
}


SCIP_RETCODE PropOBRA::addHistoricAndCurrentAlgebraicCons()
{
   int addTime;
   int firstAddTime(currentTime_ - 1 - lookback_);
   if( firstAddTime < 0)
      firstAddTime = 0;
   SCIPdebugMessage(" Step 2: Adding algebraic constraints and variables for t=%i,...,%i\n",firstAddTime,currentTime_ - 1);

   for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
   {
      SCIPdbgMsg("   Adding algebraic constraints at t=%i\n",addTime);
      for( structure_->startAlgebraicConsIteration(addTime); structure_->algebraicConsLeft(addTime);structure_->incrementAlgebraicCons())
      {
         SCIPdbgMsg("entered algebraicCons iteration\n");
         SCIP_CONS* cons(structure_->getAlgebraicCons());
         if( cons != nullptr && !SCIPconsIsDeleted(cons) )
         {
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cons));
            SCIP_CALL( addConsWithVars(cons, true, true, TRUE) );
         }
         else
         {
            SCIPdbgMsg("not adding deleted cons %s\n", SCIPconsGetName(cons));
         }
      }
      SCIPcppDbgMsg("   Added Constraints and Variables" << std::endl);
   }
   return SCIP_OKAY;
}


/** Method executing bound propagation using a subscip for differential and algebraic constraints at one given time
 *
 *  input:
 *  - scip                 : SCIP main data structure of the original problem
 *  - subscip              : SCIP main data structure for the subscip, with created empty problem and settings
 *  - currentTime          : Bounds of variables at the given currentTime will (hopfeully) be tightened
 *  - lookback         : The number of historical constraints to be considered in bound tightening
 *  - varmap               : A preallocated sufficiently large varmap to be used for the subscip (contents will be lost)
 *  - consmap              : A preallocated sufficently large consmap to be used for the subscip (contents will be lost)
 *  - nPropagatedVars      : Pointer to an integer, which is incrementend by one for each propagated variable, or NULL
 *  - nchgbds              : Pointer to an integer, which is incrementend by one for each changed bound or NULL
 *
 *  In Addition to the call parameters, this method depends on the availability of a valid problem structure
 *
 *  The method sequentially completes two tasks:
 *  1) Bound propagation to algebraic variables at t = currentTime -1 using the algebraic constraints at t = currentTime -1
 *     and additionally lookback earlier constraints
 *  2) Bound propagation to differential variables at t = currentTime using the algebraic constraints at t = currentTime
 *     and additionally lookback earlier constraints
 *
 *  These tasks are divided into 6 smaller steps, see comments in code and SCIPdebugMessages
 *
 */
SCIP_RETCODE PropOBRA::propBoundsAtTwithSubscip( int* nPropagatedVars, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge)
{
   SCIPdbgMsg("Entering propBoundsAtTWithSubscip, currentTime_ is %i\n",currentTime_);

   /*
    * 1: Free Subscip and emtpy hashmaps
    */
   SCIP_CALL(SCIPcreateProb(subscip_, "algebraicPropagationSubScip", NULL, NULL,         NULL, NULL, NULL, NULL, NULL));
   SCIP_CALL( SCIPaddParamsSD(subscip_));

   solMap_ = new std::map<SCIP_VAR*, SCIP_Real>;

   /* We want to use structure exploiting heuristic in the subproblem, so we need to initialize an SD problem */
   SCIP_CALL( SDinit(subscip_));

   SCIPhashmapRemoveAll(varmap_);
   SCIPhashmapRemoveAll(consmap_);

   /*
    * 2: Add historic and current algebraic constraints to subscip
    */
   addHistoricAndCurrentAlgebraicCons();


   /*
    * 3: Add historic differential constraints to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - lookback_);
      if( firstAddTime < 0 )
         firstAddTime = 0;
      SCIPdebugMessage(" Step 3: Adding historic differential constraints to subscip at t=%i,...,%i\n",firstAddTime, currentTime_ - 1);
      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         for( structure_->startDiffConsIteration(addTime); structure_->diffConsLeft(addTime); structure_->incrementDiffCons())
         {
            SCIP_CONS* cons(structure_->getDiffConsCons());
            SCIPdebugMessage("   Adding Constraint %s\n",SCIPconsGetName(cons));
            if( cons != nullptr)
            {
               SCIP_CALL( addConsWithVars(cons, true, true, TRUE) );
            }
         }
      }
      //SCIPcppDbgMsg(" Added Constraints and Variables" << std::endl);
   }

   /*
    * 4: Add historic cuts to state variables to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - lookback_);
      if( firstAddTime < 0 )
         firstAddTime = 0;
      SCIPdebugMessage(" Step 4: Adding state cut constraints to subscip at t=%i,...,%i\n",firstAddTime, currentTime_ - 1);
      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         SCIPdebugMessage("   Adding cut constraints at t=%i\n",addTime);
         for( structure_->startCutIteration(addTime); structure_->cutsLeft(addTime); structure_->incrementCut())
         {
            SCIP_CONS* cut(structure_->getCut());
            assert(!SCIPconsIsDeleted(cut));
            SCIPdbgMsg("   Adding Constraint %s\n",SCIPconsGetName(cut));
            /* Add this constraint and its variables */
            SCIP_CALL( addConsWithVars(cut, true, true, FALSE) );
         }
      }
   }

   /*
    * 5: Propagate algebraic constraints
    */
   //@todo: Use a propagation pattern for this as well

   if( propagateAlgebraic_ && (currentTime_ >= 1) )
   {
      /* Use propagationPattern for algebraic vars */
      SCIP_CALL( prepareAlgebraicPattern());
      SCIP_CALL( algebraicPattern_.setSolMap(solMap_));
      SCIP_CALL( algebraicPattern_.propagate(currentTime_));
      SCIPdebugMessage("#### Done with Step 7_2\n");
   }

   /*
    * 6: Add differential constraints at current time to subscip
    */
   SCIPdebugMessage(" Step 6: Adding differential constraints at t=%i\n",currentTime_);
   if( !(*boundsDiverge) ) {
      ConsVarVec::iterator pairIt;
      for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
      {
         SCIP_CONS * cons(structure_->getDiffConsCons());

         if( cons != nullptr && !SCIPconsIsDeleted(cons) )
         {
            assert(!SCIPconsIsDeleted(cons));
            SCIPdebug( SCIP_CALL_ABORT( SCIPprintCons(scip_, cons, NULL) ) );
            SCIPdebug( SCIPinfoMessage(scip_, NULL, ";\n") );
            SCIP_CONS * currentCons(structure_->getDiffConsCons());
            SCIPdebugMessage(" Adding Constraint %s\n",SCIPconsGetName(currentCons));
            /* Add this constraint and its variables */
            SCIP_CALL( addConsWithVars(currentCons, true, true, TRUE) );
         }
         else
         {
            SCIPdbgMsg("not adding deleted cons %s\n", SCIPconsGetName(cons));
         }
      }
   }


   /*
    * 7_1: propagation of states 'vertically', 'horizontally' and 'diagonally'
    */
   if(  currentTime_ >= 1 && propagateStates_ && !(*boundsDiverge) )
   {
      SCIPdebugMessage("#### Step 7_2: Propagating bounds to differential variables at t=%i\n",currentTime_);
      ConsVarVec::iterator pairIt;

      SCIP_CALL( prepareConstTimeStatePattern());
      SCIP_CALL( constTimePattern_.setSolMap(solMap_));
      SCIP_CALL( constTimePattern_.buildHyperCube() );

      SCIP_CALL( constTimePattern_.propagate(currentTime_));
      SCIPdebugMessage("#### Done with Step 7_2\n");
   } /* Close Step 7_1 */


   /*
    * 7_2: Propagation of states from different times
    */
   if( currentTime_ >= 1 && addMultiTimeCuts_ && !(*boundsDiverge) )
   {
      SCIPdbgMsg("multitimelookback = %i\n",multiTimeCutLookback_);
      SCIPdebugMessage("#### Step 7_3: Propagating bounds to differential variables at t=%i...%i\n",currentTime_ - multiTimeCutLookback_ + 1,currentTime_);
      ConsVarVec::iterator pairIt;

      for( structure_->startDiffConsIteration(); structure_->diffConsLeft(); structure_->incrementDiffCons())
      {
         SCIP_VAR* var(structure_->getDiffConsVar());
         SCIP_CONS* cons(structure_->getDiffConsCons());
         SCIPdebugMessage("  Creating multitime cuts on Variable %s --> %s\n",SCIPvarGetName(var),SCIPconsGetName(cons));

         SCIP_CALL( prepareMultiTimeStatePattern(var));
         SCIP_CALL( multiTimePattern_.setSolMap(solMap_));
         SCIP_CALL(multiTimePattern_.buildHyperCube() );
         SCIP_CALL(multiTimePattern_.propagate(currentTime_));
         SCIP_CALL(multiTimePattern_.resetObjVals());

      }
      SCIPdebugMessage("#### Done with Step 7_3\n");
   } /* Close Step 7_2 */

   /*
    * 8: Propagation of control variables
    */
   if( propagateControls_ )
   {
      SCIPdebugMessage("#### Step 8: Propagating bounds to control variables at t=%i\n",currentTime_);
      ConsVarVec::iterator pairIt;

      SCIP_CALL( prepareControlPattern());
      SCIP_CALL( controlPattern_.setSolMap(solMap_));
      SCIP_CALL( controlPattern_.propagate(currentTime_));
      SCIPdebugMessage("#### Done with Step 8\n");
   }

   SCIP_CALL( SCIPfreeTransform(subscip_) );

   if( (*boundsDiverge) )
   {
      SCIPdebugMessage("Bounds diverge at  t=%i\n",currentTime_);
   }

   delete solMap_;

   return SCIP_OKAY;
}













