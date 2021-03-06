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
 */

#ifndef __PROP_OBRA_H__
#define __PROP_OBRA_H__

#include "sdscip.h"
#include "objscip/objscip.h"
#include "PropagationPattern.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>      // std::ofstream
#include <string>
#include "scip/clock.h"
#include "objscip/objscipdefplugins.h"
#include "scip/cons.h"

namespace sdscip
{

struct Statistics
{
   SCIP_Real remainingBounds = 0;
   int nSubscips = 0;


   void reset()
   {
      remainingBounds = 0;
      nSubscips = 0;
   }

   Statistics() : remainingBounds(0.0) {}
};

class PropOBRA: public scip::ObjProp
{
public:

   /** default constructor */
   PropOBRA(
      SCIP* scip
      )
      : ObjProp(
    		  scip,                                              /**< SCIP data structure */
    		  "obra", 									              /** name of the propagator */
    		  "optimization based reachability analysis",        /** description of the propagator */
    		   1,                                                /** default priority of the propagator */
    		   -1,                                               /** freq */
    		   0,                                                /** delay */
     		   SCIP_PROPTIMING_BEFORELP,                         /** timingmask */
    		   0,                                                /** presolpriority */
    		   0,                                                /** presolmaxrounds */
    		   SCIP_PRESOLTIMING_FAST                            /** presoltiming */
      )
      ,signal_(false)
      ,currentTime_(0)
      ,progressTime_(0)
      ,progressStep_(0.0)
      ,structure_()
      ,constTimePattern_()
      ,algebraicPattern_()
      ,multiTimePattern_(1)
      ,cutFile_(NULL)
      ,outFile_(NULL)
      ,outDir_(NULL)

      ,progressFile_(NULL)
      ,nSubscipsPerTime_(0)
   {

      scip_ = scip;

      /* Parameters about propagation */
      SCIPaddIntParam(scip,
             "propagating/obra/breakTime",
             "Timestep, at which propagation is stopped. Set to -1 for no limit",
             &breakTime_, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/lookback",
             "Number of historic Constraints to be used in bound propagation (0: conventional bound propagation)",
             &lookback_, FALSE, 5, 0, 1000, NULL, NULL);

      SCIPaddRealParam(scip,
             "propagating/obra/cancelBound",
             "Give up obra when a computed bound is outside of [-cancelBound, cancelBound]",
             &cancelBound_, FALSE, 1e6,-1e20, 1e20, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/propagateAlgebraic",
             "Should bounds of algebraic variables be propagated explicitly?",
             &propagateAlgebraic_, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/propagateStates",
             "Should bounds of state variables be propagated explicitly?",
             &propagateStates_, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/propagateControls",
             "Should bounds of control variables be propagated (back) explicitly?",
             &propagateControls_, FALSE, FALSE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/addCuts",
             "Add propcuts for states during propagation?",
             &addCuts_, FALSE, FALSE, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/cutFreq",
             "Frequency in (Problem) Time in which to try adding bounds diagonal to the state axes realized as cuts (-1: Disabled)",
             &cutFreq_, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/addMultiTimeCuts",
             "Should we add cuts connecting one state variable at multiple times ",
             &addMultiTimeCuts_, FALSE, FALSE, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/cutConf3d",
             "What kinds of cuts are added to problems with 3 state variables",
             &cutConf3d_, FALSE, 2, 0, 2, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/multiTimeCutLookback",
             "How many times should the multiTimeStateCut incorporate",
             &multiTimeCutLookback_, FALSE, 2, 2, 1000, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/useUnitCuts",
             "Choose the slope of the cut independent of current bounds",
             &useUnitCuts_, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/tryMainSol",
             "Should we try the best solution form mainscip in subscip",
             NULL, FALSE, TRUE, NULL, NULL);


      /* Parameters about output */
      SCIPaddBoolParam(scip,
             "propagating/obra/writeAfterProp",
             "Write transformed problem to file after propagation",
             &writeAfterProp_, FALSE, FALSE, NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/outFile",
             "Prefix for cip files written during propagation",
             &outFile_, FALSE, "obra", NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/outDir",
             "Directory to write output files to, format directory/, default is ./",
             &outDir_, FALSE, "./", NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/writeCutsAfterProp",
             "Write cuts to file after propagation",
             &writeCutsAfterProp_, FALSE, FALSE, NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/cutFile",
             "Filename of sdc file to write to after propagation",
             &cutFile_, FALSE, "transprob.cip", NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/writeFreq",
             "(Problem) Time Intervals in which to write the problem before propagating to time",
             &writeFreq_, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/boundWriteFreq",
             "(Problem) Time Intervals in which to write the bounds during propagation",
             &boundWriteFreq_, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/writeProgress",
             "Write progress info to a file during propagation",
             &writeProgress_, FALSE, FALSE, NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/progressFile",
             "Filename of file to write progress to",
             &progressFile_, FALSE, "progress.log", NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/writeSubscips",
             "Write original subscips to a file before solving a pattern",
             &writeSubscips_, FALSE, FALSE, NULL, NULL);

      /* Define parameters for settings of the subscip */
      SCIPaddStringParam(scip,
             "propagating/obra/subscipSetFile",
             "Filename to read subscip settings from (subscip.set)",
             NULL, FALSE, "subscip.set", NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/reoptimize",
             "Enable reoptimization in subscips",
             &reoptimize_, FALSE, FALSE, NULL, NULL);

      SCIPaddRealParam(scip,
            "propagating/obra/subscipGapLimit",
            "Gap Limit for the subscips",
            &subscipGapLimit_, FALSE, 0.001, 0.0, SCIP_REAL_MAX, NULL, NULL);

      SCIPaddRealParam(scip,
            "propagating/obra/subscipTimeLimit",
            "Timelimit for the subscips",
            &subscipTimeLimit_, FALSE, 100, 0.0, SCIP_REAL_MAX, NULL, NULL);

      SCIPaddRealParam(scip,
            "propagating/obra/timeLimit",
            "Timelimit for one obra run (enforced by successively updating setting subscip timelimits)",
            &timeLimit_, FALSE, 3600, 0.0, SCIP_REAL_MAX, NULL, NULL);

      SCIPaddLongintParam(scip,
             "propagating/obra/subscipNodeLimit",
             "Node Limit for subscips, -1: no limit",
             &subscipNodeLimit_, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/subscipWriteLogs",
             "Write subscip output to logfile",
             &subscipWriteLogs_, FALSE, FALSE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/subscipMute",
             "Disable Output of subscips",
             &subscipMute_, FALSE, TRUE, NULL, NULL);

      varRegex_.assign(std::string("(?:t_)+([A-Za-z0-9_]+)\\(([0-9]+,)?([0-9]+)\\)"), boost::regex_constants::icase);
      consRegex_.assign(std::string("[A-Za-z0-9]+_([A-Za-z0-9_]+)\\(([0-9]+,)?([0-9]+)\\)"), boost::regex_constants::icase);

      /* Set identifiers in patterns */
      constTimePattern_.identifier_ = 's';
      algebraicPattern_.identifier_ = 'a';
      controlPattern_.identifier_ = 'c';
      multiTimePattern_.identifier_ = 'm';
   }

   /** destructor */
   virtual ~PropOBRA()
   {
   }

   virtual SCIP_DECL_PROPINIT(scip_init);
   virtual SCIP_DECL_PROPEXEC(scip_exec);
   virtual SCIP_DECL_PROPPRESOL(scip_presol);

private:

   SCIP_RETCODE printTimeProgressHeader(int tStart, int tFinal, int steps, int nChars);
   SCIP_RETCODE printProgress();
   SCIP_RETCODE closeProgressFile(SCIP_Real solvingTime);
   SCIP_RETCODE writeProgress(SCIP_Real solvingTime);
   SCIP_RETCODE printSummary( int nSubscips, SCIP_Real aggSolvingTime, SCIP_Bool addCuts, SCIP_Bool addMultiTimeCuts, int breakTime, SCIP_CLOCK* propClock);
   SCIP_RETCODE writeAfterProp( int breakTime);
   SCIP_RETCODE writeCuts( );


   SCIP_RETCODE applyOBRA(SCIP_RESULT* result);

   /* Preparation methods */
   SCIP_RETCODE createAndConfigureSubscip();

   /* In-looop parts of obra */

   SCIP_RETCODE propBoundsAtTwithSubscip( int* nPropagatedVars, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge);

   SCIP_RETCODE addConsWithVars(SCIP_CONS* currentCons, SCIP_Bool noObj, SCIP_Bool global, SCIP_Bool copysol);

   SCIP_RETCODE prepareConstTimeStatePattern();
   SCIP_RETCODE prepareMultiTimeStatePattern( SCIP_VAR* lastVar);
   SCIP_RETCODE prepareAlgebraicPattern();
   SCIP_RETCODE prepareControlPattern();


   SCIP_RETCODE addHistoricAndCurrentAlgebraicCons();

   //SCIP_RETCODE addConsWithVars(SCIP_CONS* cons, SCIP_Bool noObj);
   SCIP_RETCODE propagateDifferentialWithPattern( int* nNewCons, SCIP_Bool * boundsDiverge);
   SCIP_RETCODE addPlanesWithSubscip( int nVars, SCIP_VAR** origVars, SCIP_VAR** subscipObjectiveVars, int* nNewCons );

   SCIP_Bool signal_;
   int currentTime_;
   int progressTime_; /* time shown in progress bar */
   SCIP_Real progressStep_; /* time shown in progress bar */
   sdscip::SDproblemStructureInterface* structure_;
   Statistics stats_;
   boost::regex varRegex_;
   boost::regex consRegex_;
   PropagationPattern constTimePattern_;
   PropagationPattern algebraicPattern_;
   PropagationPattern controlPattern_;
   PropagationPattern multiTimePattern_;
   SCIP_HASHMAP* consmap_;
   SCIP_HASHMAP* varmap_;
   std::map<SCIP_VAR*, SCIP_Real>* solMap_;
   SCIP* scip_;
   SCIP* subscip_;

   /* Parameters */
   SCIP_Real subscipGapLimit_;
   int lookback_;
   SCIP_Real cancelBound_;
   int breakTime_;
   SCIP_Real subscipTimeLimit_;
   SCIP_Real timeLimit_;
   SCIP_Longint subscipNodeLimit_;
   SCIP_Bool subscipWriteLogs_;
   SCIP_Bool subscipMute_;
   SCIP_Bool propagateAlgebraic_;
   SCIP_Bool propagateStates_;
   SCIP_Bool propagateControls_;
   SCIP_Bool writeAfterProp_;
   SCIP_Bool writeCutsAfterProp_;
   char* cutFile_;
   char* outFile_;
   char* outDir_;
   int boundWriteFreq_;
   SCIP_Bool writeProgress_;
   std::ofstream progressOfs_;
   char* progressFile_;
   int writeFreq_;
   SCIP_Bool addCuts_;
   int cutFreq_;
   SCIP_Bool  addMultiTimeCuts_;
   int cutConf3d_;
   SCIP_Bool writeSubscips_;
   int multiTimeCutLookback_;
   SCIP_Bool useUnitCuts_;
   SCIP_Bool reoptimize_;
   int nSubscipsPerTime_;
   SCIP_CLOCK* propClock_;

};

}

#endif
