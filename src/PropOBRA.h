/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 20016     Ingmar Vierhaus <mail@ingmar-vierhaus.de>      */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#include
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/**@file   PropOBRA.h
 * @brief  Propagating bounds of control problems by solving auxiliary OBRAs, implementing Scott, Barton 2012
 * @author Ingmar Vierhaus
 */
/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __PROP_OBRA_H__
#define __PROP_OBRA_H__

#include "objscip/objscip.h"
#include "PropagationPattern.h"
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "scip/clock.h"
#include "objscip/objscipdefplugins.h"

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
      ,multiTimePattern_(1)
   {
      /* add parameters */
      SCIPaddIntParam(scip,
             "propagating/obra/historicCons",
             "Number of historic Constraints to be used in bound propagation (0: conventional bound propagation)",
             NULL, FALSE, 5, 0, 1000, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/breakTime",
             "Timestep, at which propagation is stopped. Set to -1 for no limit",
             NULL, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddRealParam(scip,
         "propagating/obra/subscipTimeLimit",
         "Timelimit for the subscips",
         FALSE, FALSE, 1e20, 0.0, SCIP_REAL_MAX, NULL, NULL);

      SCIPaddLongintParam(scip,
             "propagating/obra/subscipNodeLimit",
             "Node Limit for subscips, -1: no limit",
             NULL, FALSE, 10000, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/muteSubscip",
             "Disable Output of subscips",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/propagateAlgebraic",
             "Should bounds of algebraic variables be propagated explicitly?",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/propagateStates",
             "Should bounds of state variables be propagated explicitly?",
             NULL, FALSE, TRUE, NULL, NULL);


      SCIPaddBoolParam(scip,
             "propagating/obra/propagateControls",
             "Should bounds of control variables be propagated (back) explicitly?",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/subscipSetFile",
             "Filename to read subscip settings from (subscip.set)",
             NULL, FALSE, "subscip.set", NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/writeAfterProp",
             "Write transformed problem to file after propagation",
             NULL, FALSE, FALSE, NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/outFile",
             "Filename of cip file to write to after Propagation",
             NULL, FALSE, "transprob.cip", NULL, NULL);

      SCIPaddStringParam(scip,
             "propagating/obra/outDir",
             "Directory to write output files to, format directory/, default is ./",
             NULL, FALSE, "./", NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/writeFreq",
             "(Problem) Time Intervals in which to write the problem during propagation",
             NULL, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/addCuts",
             "Add propcuts for states during propagation?",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/cutFreq",
             "Frequency in (Problem) Time in which to try adding bounds diagonal to the state axes realized as cuts (-1: Disabled)",
             NULL, FALSE, -1, -1, INT_MAX, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/addMultiTimeCuts",
             "Should we add cuts connecting one state variable at multiple times ",
             NULL, FALSE, FALSE, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/obra/cutConf3d",
             "What kinds of cuts are added to problems with 3 state variables",
             NULL, FALSE, 0, 0, 2, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/writeSubscips",
             "Write subscips to a file (overwrites on every solve)",
             NULL, FALSE, FALSE, NULL, NULL);


      SCIPaddIntParam(scip,
             "propagating/obra/multiTimeCutLookback",
             "How many times should the multiTimeStateCut incorporate",
             NULL, FALSE, 2, 2, 1000, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/useUnitCuts",
             "Choose the slope of the cut independent of current bounds",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/obra/reoptimize",
             "Enable reoptimization in subscips",
             NULL, FALSE, FALSE, NULL, NULL);

      varRegex_.assign(std::string("(?:t_)+([A-Za-z0-9_]+)\\(([0-9]+,)?([0-9]+)\\)"), boost::regex_constants::icase);
      consRegex_.assign(std::string("[A-Za-z0-9]+_([A-Za-z0-9_]+)\\(([0-9]+,)?([0-9]+)\\)"), boost::regex_constants::icase);
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
   SCIP_RETCODE printSummary(SCIP* scip, int nSubscips, SCIP_Real aggSolvingTime, SCIP_Bool addCuts, SCIP_Bool addMultiTimeCuts, int breakTime, int historicCons, SCIP_CLOCK* propClock);
   SCIP_RETCODE applyOBRA(SCIP* scip, SCIP_RESULT* result);
   SCIP_RETCODE writeAfterProp(SCIP* scip, int breakTime, int historicCons);
   SCIP_RETCODE ensureCurrentStructure(SCIP* scip);
   SCIP_RETCODE addConsWithVars(SCIP_CONS* cons, SCIP* scip, SCIP* subscip,SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, SCIP_Bool noObj);
   SCIP_RETCODE propBoundsAtTwithSubscip(SCIP* scip, SCIP* subscip, int historicCons, SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, int* nPropagatedVars, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge);
   SCIP_RETCODE propBoundWithSubscip( SCIP* scip, SCIP_VAR* origVar, SCIP* subscip, SCIP_VAR* subscipObjectiveVar, int* nchgbds, SCIP_Real* totalBoundReduction, SCIP_Bool* boundsDiverge, std::map<SCIP_VAR*, SCIP_Real>* solMap );
   SCIP_RETCODE addPlanesWithSubscip(SCIP* scip, int nVars, SCIP_VAR** origVars, SCIP* subscip, SCIP_VAR** subscipObjectiveVars, int* nNewCons );
   SCIP_RETCODE prepareConstTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_HASHMAP* varmap);
   SCIP_RETCODE prepareMultiTimeStatePattern(SCIP* scip, SCIP* subscip, SCIP_VAR* lastVar, SCIP_HASHMAP* varmap);
   SCIP_RETCODE propagateDifferentialWithPattern(SCIP* scip, SCIP* subscip, int* nNewCons, SCIP_Bool * boundsDiverge);

   SCIP_Bool signal_;
   int currentTime_;
   int progressTime_; /* time shown in progress bar */
   SCIP_Real progressStep_; /* time shown in progress bar */
   sdscip::SDproblemStructureInterface* structure_;
   Statistics stats_;
   boost::regex varRegex_;
   boost::regex consRegex_;
   PropagationPattern constTimePattern_;
   PropagationPattern multiTimePattern_;
};

}

#endif
