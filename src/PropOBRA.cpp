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

SCIP_RETCODE PropOBRA::printSummary(SCIP* scip, int nSubscips, SCIP_Real aggSolvingTime, SCIP_Bool addCuts, SCIP_Bool addMultiTimeCuts, int breakTime, SCIP_CLOCK* propClock)
{
   std::multimap<int, std::string> dst;
   std::map<int, std::string>::iterator iter;

   SCIPinfoMessage( scip, NULL, "-------------------------------------------------------------------------\n" );
   SCIPinfoMessage(scip,NULL,"| CtrlDifferential General Statistics in depth %5i                    |\n",SCIPgetDepth(scip));
   SCIPinfoMessage(scip,NULL,"| HistoricCons parameter:          %-4i                                 |\n",historicCons_);
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

   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::writeAfterProp(SCIP* scip, int breakTime)
{
   SCIP_Bool writeAfterPropParam;
   if( SCIPgetBoolParam( scip, "propagating/obra/writeAfterProp", &writeAfterPropParam ) && writeAfterPropParam )
   {
      char* outfilestr, *outdirstr;
      std::ostringstream oss,bndoss;
      SCIPgetStringParam( scip, "propagating/obra/outFile", &outfilestr );
      SCIPgetStringParam( scip, "propagating/obra/outDir", &outdirstr );
      oss << outdirstr << outfilestr << "_" << historicCons_ << "_" << ( breakTime < 0 ? currentTime_ : breakTime - 1 ) << ".cip";

      SCIPdebugMessage( "WRITING transformed problem to file %s at t=%i\n", oss.str().c_str(), currentTime_ );
      SCIPwriteTransProblem(scip, oss.str().c_str(),"cip", false);
      bndoss << outdirstr << outfilestr << "_" << historicCons_ << "_" << currentTime_ << ".bnd";
      SCIPdebugMessage("WRITING bounds to file %s at t=%i\n",bndoss.str().c_str(),currentTime_);
      SCIPwriteTransProblem(scip, bndoss.str().c_str(), "bnd", false);

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
   SCIP_CALL( applyOBRA(scip, result) );
   return SCIP_OKAY;
}

/** presolving method of propagator */
SCIP_DECL_PROPPRESOL( PropOBRA::scip_presol )
{
   SCIPdebugMessage( "entered Presolving of Constraintless Conshdlr CtrlDifferential \n" );

   SDensureValidStructure(scip );

   SCIPdebugMessage( "Running Propagation of CtrlDifferential routine as part of presolving\n" );

   SCIP_CALL( applyOBRA(scip, result) );

   return SCIP_OKAY;
}

/** apply one round of obra */
SCIP_RETCODE PropOBRA::applyOBRA(SCIP* scip, SCIP_RESULT* result)
{
   /* Make sure parameters are the way we want them */
   {
      SCIP_Bool val;
      SCIP_CALL(SCIPgetBoolParam(scip, "constraints/nonlinear/reformulate", &val));
      SCIP_CALL(SCIPgetBoolParam(scip, "presolving/donotmultaggr", &val));
      assert(val == TRUE);
   }

   /* Don't run in probing */
   if( SCIPinProbing( scip ) )
      return SCIP_OKAY;

   SCIP_CLOCK* propClock;

   /* Start timing */
   SCIP_CALL( SCIPclockCreate(& propClock , SCIP_CLOCKTYPE_DEFAULT) );
   SCIPclockSetTime(propClock,0);
   SCIPclockStart(propClock,scip->set);

   /* Get parameters on how to run */
   int breakTime;
   int writeFreq;
   SCIP_Bool addCuts;
   SCIP_Bool addMultiTimeCuts;
   int cutFreq;
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/breakTime", &breakTime ) );
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/writeFreq", &writeFreq ) );
   SCIP_CALL( SCIPgetBoolParam( scip, "propagating/obra/addCuts", &addCuts ) );
   SCIP_CALL( SCIPgetBoolParam( scip, "propagating/obra/addMultiTimeCuts", &addMultiTimeCuts ) );
   SCIP_CALL( SCIPgetIntParam( scip, "propagating/obra/cutFreq", &cutFreq ) );

   /* Configure the constTime,multiTime  and algebraic PropagationPatterns */
   constTimePattern_.setCutConf3d( cutConf3d_ );
   constTimePattern_.setUseUnitCuts(false);
   multiTimePattern_.setUseUnitCuts(useUnitCuts_);
   algebraicPattern_.setUseUnitCuts(true);
   algebraicPattern_.setAddCuts(false);
   controlPattern_.setUseUnitCuts(true);
   controlPattern_.setAddCuts(false);


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
         if( writeFreq != -1 && currentTime_ % writeFreq == 0)
         {
            char* paramstr,*paramstr2;
            std::ostringstream oss;
            SCIPgetStringParam(scip,"propagating/obra/outFile",&paramstr);
            SCIPgetStringParam(scip,"propagating/obra/outDir",&paramstr2);
            oss << paramstr2 << paramstr << "_" << historicCons_ << "_" << currentTime_ << ".cip";
            SCIPdebugMessage("WRITING transformed problem to file %s at t=%i\n",oss.str().c_str(),currentTime_);
            SCIPwriteTransProblem(scip, oss.str().c_str(), "cip", false);
         }
         /*
          * Create, allocate and configure Subscip
          */
         SCIP* subscip;
         SCIP_HASHMAP* consmap;
         SCIP_HASHMAP* varmap;

         SCIP_CALL( createAndConfigureSubscip(scip, &subscip, &consmap, &varmap) );


         SCIP_Bool boundsDiverge(false);
         SCIPdbgMsg("calling propBoundsAtTwithSubscip, currentTime = %i\n",currentTime_);
         SCIP_CALL( propBoundsAtTwithSubscip(scip, subscip, varmap, consmap, &nPropagatedVars, &nchgbds, &totalBoundReduction, &boundsDiverge));

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

      } /* Close stop iteration at given time */
      else if( currentTime_ == breakTime)
      {
         SCIPdebugMessage("breaking for breakTime\n");
      }
      printProgress();
   } /* Close iteration over times */

   SCIPclockStop( propClock, scip->set );

   int nSubscips = constTimePattern_.stats_.nSubscips + constTimePattern_.stats_.nSubscips;
   SCIP_Real aggSolvingTime    = constTimePattern_.stats_.aggSolutionTime    + multiTimePattern_.stats_.aggSolutionTime;

   /* Display the summary of this obra run */
   printSummary(scip, nSubscips, aggSolvingTime, addCuts, addMultiTimeCuts, breakTime, propClock);

   SCIP_CALL( writeAfterProp(scip, breakTime) );

   SCIPclockFree( &propClock );

   *result = SCIP_DIDNOTFIND;
   return SCIP_OKAY;
}


SCIP_RETCODE PropOBRA::prepareConstTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap)
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   constTimePattern_.clearVars();
   constTimePattern_.setScip(scip);
   constTimePattern_.setSubscip(subscip);
   constTimePattern_.setCurrentTime(currentTime_);
   SCIP_CALL( constTimePattern_.setAddCuts(addCuts_) );

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

SCIP_RETCODE PropOBRA::prepareAlgebraicPattern(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap)
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   algebraicPattern_.clearVars();
   algebraicPattern_.setScip(scip);
   algebraicPattern_.setSubscip(subscip);
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
               algebraicPattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap,var));
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

SCIP_RETCODE PropOBRA::prepareControlPattern(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap)
{
   ConsVarVec::iterator pairIt;
   VarVec subscipVars;

   /* Configure pattern */
   controlPattern_.clearVars();
   controlPattern_.setScip(scip);
   controlPattern_.setSubscip(subscip);
   controlPattern_.setCurrentTime(currentTime_);

	   SCIPdebugMessage(" Step 8: Propagating bounds to control variables at t=%i\n",currentTime_);
	   for( structure_->startControlVarIteration(currentTime_ - 1); structure_->controlVarsLeft(currentTime_ - 1);structure_->incrementControlVar() )
	   {
		   SCIP_VAR* var(structure_->getControlVarAtTOrig());
		   SCIPdbgMsg("Got control var %s\n", SCIPvarGetName(var));
		   SCIP_VAR* subscipVar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,var);
		   SCIPdbgMsg("Got subscip var %s\n", SCIPvarGetName(subscipVar));
		   assert(subscipVar != NULL);
		   controlPattern_.addVar(var, (SCIP_VAR*) SCIPhashmapGetImage(varmap,var));
	   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropOBRA::prepareMultiTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_VAR* lastVar, SCIP_HASHMAP* varmap)
{

   VarVec subscipVars;

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

   std::vector<SCIP_VAR*> lastVars(structure_->getDiffConsLastVars(multiTimeCutLookback_));

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
   for( int i=1; i <= multiTimeCutLookback_ - 1; ++i)
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

SCIP_RETCODE PropOBRA::createAndConfigureSubscip(SCIP* scip, SCIP** subscipp, SCIP_HASHMAP** consmap, SCIP_HASHMAP** varmap)
{
   SCIP* subscip;
   assert(scip != NULL);

   SCIP_CALL( SCIPcreate(subscipp) );
   subscip = *subscipp;

   /* Include default plugins */
   SCIP_CALL(SCIPincludeDefaultPlugins(subscip));

   /* --- Configure subscip for obra ---- */

   /* do not abort subproblem on CTRL-C */
   SCIP_CALL( SCIPsetBoolParam(subscip, "misc/catchctrlc", FALSE) );

#ifndef SCIP_DEBUG
   /* disable statistic timing inside sub SCIP */
   SCIP_CALL( SCIPsetBoolParam(subscip, "timing/statistictiming", FALSE) );
#endif

   /* forbid call of heuristics and separators solving sub-CIPs */
   SCIP_CALL( SCIPsetSubscipsOff(subscip, TRUE) );

   /* --- Configure subscip from obra parameters  ---- */

   /* Set reoptimization depending on obra parameters */
   if( reoptimize_ == TRUE )
   {
      SCIP_CALL( SCIPsetBoolParam(subscip, "reoptimization/enable", TRUE));
   }

   /* Set timelimit depending on obra parameters */
   SCIP_CALL( SCIPsetRealParam(subscip,"limits/time",subscipTimeLimit_) );

   /* Set nodelimit depending on obra parameters*/
   SCIP_CALL( SCIPsetLongintParam(subscip,"limits/nodes",subscipNodeLimit_) );

   /* Mute subscips depending on obra parameters*/
   if(subscipMute_ == true)
   {
      SCIP_CALL( SCIPsetIntParam(subscip, "display/verblevel", 0) );
   }

   /* Create and allocate consmap and varmap */
   SCIP_CALL( SCIPhashmapCreate(consmap, SCIPblkmem(subscip), SCIPgetNConss(scip)) );
   SCIP_CALL( SCIPhashmapCreate(varmap, SCIPblkmem(subscip), SCIPcalcHashtableSize(SCIPgetNVars(scip))) );

   return SCIP_OKAY;

}

/** Adds a constraint in scip with its varaibles in to subscip
 *  and copies the bounds of the variables  */
SCIP_RETCODE PropOBRA::addConsWithVars(SCIP_CONS* currentCons, SCIP* scip, SCIP* subscip,SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, SCIP_Bool noObj, SCIP_Bool global, std::map<SCIP_VAR*, SCIP_Real>* solMap, SCIP_Bool copysol)
{
   int nConsVars;
   SCIP_VAR** consvars;
   SCIP_Bool success;
   SCIP_CONS* targetcons = NULL;
   SCIP_SOL* scipSol;

   assert(currentCons != NULL);
   assert(scip != NULL);
   assert(subscip != NULL);
   assert(varmap != NULL);
   assert(consmap != NULL);

   scipSol = SCIPgetBestSol(scip);

   SCIPdebugMessage("adding cons with Vars from scip in stage %i\n",SCIPgetStage(scip));

    //Add constraint to subscip

   SCIP_CONSHDLR* conshdlr;
   conshdlr = SCIPconsGetHdlr(currentCons);
   SCIP_CALL( SCIPgetConsCopy(scip, subscip, currentCons, &targetcons, conshdlr, varmap, consmap, NULL,
         SCIPconsIsInitial(currentCons), SCIPconsIsSeparated(currentCons),
         SCIPconsIsEnforced(currentCons), SCIPconsIsChecked(currentCons),
         SCIPconsIsPropagated(currentCons), FALSE, SCIPconsIsModifiable(currentCons),
         SCIPconsIsDynamic(currentCons), SCIPconsIsRemovable(currentCons), FALSE, TRUE, &success) );


   /* Set original bounds in target scip from local/global bounds in source scip
    * necessary, since the this runs in the presolving of the source scip only original bounds are copied */
   SCIP_CALL( SCIPgetConsNVars(scip, currentCons, &nConsVars, &success) );
   assert(success);
   SCIP_CALL( SCIPallocBufferArray(scip, &consvars, nConsVars) );
   SCIP_CALL( SCIPgetConsVars(scip, currentCons, consvars, nConsVars, &success) );
   assert(success);
   for( int v = 0; v < nConsVars; v++ )
   {
      SCIPdbgMsg("considering %s variable %s %p\n",SCIPvarIsOriginal(consvars[v]) ? "original" : "transformed", SCIPvarGetName(consvars[v]), (void*) consvars[v]);
      SCIP_VAR* sourcevar = consvars[v];
      SCIP_VAR* targetvar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,consvars[v]);

      assert(targetvar != NULL);
      SCIPdbgMsg("lhs = %e\n",(global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)));
      SCIPdbgMsg("rhs = %e\n",(global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));
      SCIPdbgMsg("delta = %e\n",global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar) - global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar));
      assert((global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)) <= (global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));
      SCIPchgVarLb(subscip, targetvar, global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar));
      SCIPchgVarUb(subscip, targetvar, global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar));
      assert(SCIPisEQ(scip, SCIPvarGetLbLocal(targetvar), global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)));
      assert(SCIPisEQ(scip, SCIPvarGetUbLocal(targetvar), global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));

      if (noObj)
         SCIP_CALL( SCIPchgVarObj(subscip,targetvar,0) );

      if (scipSol != NULL && copysol == TRUE)
      {
         SCIP_Real solVal = SCIPgetSolVal(scip,scipSol,consvars[v]);
         (*solMap)[targetvar] = solVal;
      }

   }
   SCIPfreeBufferArray(scip, &consvars); //TODO _SD allocating buffer outside of loop could increase performance?

   /* add the copied constraint to target SCIP if the copying process was valid */
   if( success )
   {
      SCIPdbgMsg("copied constraint %s to subscip\n",SCIPconsGetName(currentCons));
      assert(targetcons != NULL);
       /* add constraint to target SCIP */
       SCIP_CALL( SCIPaddCons(subscip, targetcons) );
       /* release constraint once for the creation capture */
       SCIP_CALL( SCIPreleaseCons(subscip, &targetcons) );
   }
   else
   {
      SCIPdebugMessage("failed to copy constraint %s\n", SCIPconsGetName(currentCons));
      assert(FALSE);
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
 */
SCIP_RETCODE PropOBRA::propBoundsAtTwithSubscip(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, int* nPropagatedVars, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge)
{


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
      int firstAddTime(currentTime_ - 1 - historicCons_);
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
            if( !SCIPconsIsDeleted(cons) )
            {
               SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cons));
               SCIP_CALL( addConsWithVars(cons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
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
      int firstAddTime(currentTime_ - historicCons_);
      if( firstAddTime < 0 )
         firstAddTime = 0;
      SCIPdebugMessage(" Step 3: Adding historic differential constraints to subscip at t=%i,...,%i\n",firstAddTime, currentTime_ - 1);
      for( addTime = firstAddTime; addTime < currentTime_; ++addTime)
      {
         for( structure_->startDiffConsIteration(addTime); structure_->diffConsLeft(addTime); structure_->incrementDiffCons())
         {
            SCIP_CONS* cons(structure_->getDiffConsCons());
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(cons));
            SCIP_CALL( addConsWithVars(cons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
         }
      }
      SCIPcppDbgMsg(" Added Constraints and Variables" << std::endl);
   }

   /*
    * 4: Add historic cuts to state variables to subscip
    */
   {
      int addTime;
      int firstAddTime(currentTime_ - historicCons_);
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
            SCIP_CALL( addConsWithVars(cut,scip,subscip, varmap, consmap, true, true, solMap, FALSE) );
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
      SCIP_CALL( prepareAlgebraicPattern(scip, subscip, varmap));
      SCIP_CALL( algebraicPattern_.setSolMap(solMap));
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

         if( !SCIPconsIsDeleted(cons) )
         {
            assert(!SCIPconsIsDeleted(cons));
            SCIPdebug( SCIP_CALL_ABORT( SCIPprintCons(scip, cons, NULL) ) );
            SCIPdebug( SCIPinfoMessage(scip, NULL, ";\n") );
            SCIP_CONS * currentCons(structure_->getDiffConsCons());
            SCIPdbgMsg(" Adding Constraint %s\n",SCIPconsGetName(currentCons));
            /* Add this constraint and its variables */
            SCIP_CALL( addConsWithVars(currentCons,scip,subscip, varmap, consmap, true, true, solMap, TRUE) );
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

      SCIP_CALL( prepareConstTimeStatePattern(scip, subscip, varmap));
      SCIP_CALL( constTimePattern_.setSolMap(solMap));
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

         SCIP_CALL( prepareMultiTimeStatePattern(scip, subscip, var, varmap));
         multiTimePattern_.toString();
         SCIP_CALL( multiTimePattern_.setSolMap(solMap));
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

      SCIP_CALL( prepareControlPattern(scip, subscip, varmap));
      SCIP_CALL( controlPattern_.setSolMap(solMap));
      SCIP_CALL( controlPattern_.propagate(currentTime_));
      SCIPdebugMessage("#### Done with Step 8\n");
   }

   SCIP_CALL( SCIPfreeTransform(subscip) );

   if( (*boundsDiverge) )
   {
      SCIPdebugMessage("Bounds diverge at  t=%i\n",currentTime_);
   }

   delete solMap;

   return SCIP_OKAY;
}













