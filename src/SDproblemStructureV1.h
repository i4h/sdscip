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

/**@file    SDproblemStructureV1.h
 * @brief   SDO problem structure version used by ReaderVOP
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDPROBLEMSTRUCTUREV1_H_
#define SDPROBLEMSTRUCTUREV1_H_

#include <vector>
#include <unordered_map>
#include <map>
#include "SDList.h"

#include "sdscip.h"
#include "SDVarBasic.h"
#include "SDproblemStructureInterface.h"



namespace sdscip
{


class SDproblemStructureV1 : public SDproblemStructureInterface
{
public:

   using AlgebraicMap = std::map<unsigned int, std::vector<SCIP_CONS *> >;

   SDproblemStructureV1( SCIP *scip );
   virtual ~SDproblemStructureV1();

   /* Reset state of this instance */
   SCIP_RETCODE clear();

   SCIP_RETCODE checkIsSimulation();
   bool isSimulation();

   SCIP_RETCODE isExprContinuous(SCIP_EXPR* expr, SCIP_Bool& isContinuous);
   SCIP_RETCODE checkXdotContinuity();
   bool isXdotContinuous();

   /* Notify problemStructure that initial read of problem structure is finished */
   SCIP_RETCODE doneReading();

   /* Methods for building problem structure */
   SCIP_RETCODE addControlVar( SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime, int sdVarId );

   SCIP_RETCODE addVariable( int index, SCIP_VAR *var, unsigned int time, SD_VAR_TYPE type, int sdVarId );

   SCIP_RETCODE addAlgebraicCons( SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId );

   SCIP_RETCODE addExplicitDifferential( SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time, int sdVarId );

   SCIP_RETCODE addCut( SCIP_CONS *cut, unsigned int time );

   /** Methods for traversing problem structure */

   /* Iterate time steps of the problem */
   int startTimeIteration();
   int startTimeIteration(int time);

   bool timesLeft();

   unsigned int incrementTime();
   unsigned int getCurrentTime();

   SCIP_Bool isStateVar(SCIP_VAR* var);
   int getStateVarTime(SCIP_VAR* var);
   SCIP_Bool isControlVar(SCIP_VAR* var);
   int getControlVarBeginTime(SCIP_VAR* var);


   /* Get the last time represented in the current problem structure */
   unsigned int getLastTime();

   /* Iterate variables */
   void startVarIteration();

   bool varsLeft();

   void incrementVar();

   SDVarBasic getCurrentVar();

   /* Iterate differential constraints with forward variables*/
   void startDiffConsIteration();

   void startDiffConsIteration( unsigned int time );

   bool diffConsLeft();

   bool diffConsLeft( unsigned int time );

   void incrementDiffCons();

   SCIP_VAR *getDiffConsVar();
   /* Get a vector with the variables of the current differential constraint that go back n timesteps
    * i.e. getDiffConsLastVars(2) when current diffconsvar is x(5) should return a vector with pointers to x(3),x(4),x(5)
    */
   std::vector<SCIP_VAR *> getDiffConsLastVars( int n );

   SCIP_CONS *getDiffConsCons();

   /* Iterate control variabels  */
   void startControlVarIteration();
   
   void startControlVarIteration( unsigned int time );
   
   bool controlVarsLeft();

   bool controlVarsLeft( unsigned int time );
   
   void incrementControlVar();

   SCIP_VAR *getControlVar();

   void startControlVarAtTIteration();

   void startControlVarAtTIteration( unsigned int time );

   bool controlVarsAtTLeft();

   bool controlVarsAtTLeft( unsigned int time );

   void incrementControlVarAtT();

   SCIP_VAR *getControlVarAtT();

   SCIP_VAR *getControlVarAtTOrig();

   /* Get particular control variables */

   /* This function gets the control variable(s) at position n in the list of individual control variables ordered by time
    * of first appearance. This is NOT equivalent to the list of control variables at time t.
    */
   SCIP_VAR *getNthsControlVar( unsigned int n );

   unsigned int getNStates();
   unsigned int getNControls();
   unsigned int getNAlgebraic();

   /* Iterate state variables //TODO */
   void startStateVarIteration();
   bool stateVarsLeft();
   void incrementStateVar();
   SCIP_VAR* getCurrentStateVar();
   SCIP_VAR* getCurrentStateVarOrig();
   int getCurrentStateVarId();

   std::vector<std::string> getStateVarNames();

   std::vector<std::string> getControlVarNames();
   std::vector<std::string> getAlgebraicVarNames();

   void setStateVarNames( std::vector<std::string> stateVarNames );

   void setControlVarNames( std::vector<std::string> controlVarNames );

   void setAlgebraicVarNames( std::vector<std::string> algebraicVarNames );

   SCIP_EXPR** getXdot();
   SCIP_EXPR** getXdotAlgebraic();
   SCIP_EXPR** getAlgebraicExpressions();

   using SDproblemStructureInterface::getXdotParams;
   SCIP_Real* getXdotParams( int time );
   int getNParamsPerTime();

   SCIP_Real* getXdotParams(SCIP_Real time);

   void setXdotParams( std::vector<SCIP_Real> xdotParams, unsigned int nParamsPerTime );

   void setXdot( std::vector<SCIP_EXPR *> xdot );
   void setAlgebraicExpressions(  std::vector<SCIP_EXPR *> algebraicExpr );
   /* Iterate cuts */
   void startCutIteration();
   void startCutIteration( unsigned int time );
   bool cutsLeft();
   bool cutsLeft( unsigned int time );
   void incrementCut();
   SCIP_CONS *getCut();

   /* Iterate constraint levels at given time */

   void startLevelIteration();

   void startLevelIteration( unsigned int time );

   bool levelsLeft();

   bool levelsLeft( unsigned int time );

   void incrementLevel();

   int getCurrentLevel();

   SD_CONS_TYPE getCurrentLevelType();

   /* Iterate constraints and (if set) forward variables at current time and level */
   void startLevelConsIteration();

   bool levelConsLeft();

   void incrementLevelCons();

   SCIP_CONS *getCurrentLevelConsCons();

   void setXdotAlgebraic(std::vector<SCIP_EXPR*> xdotAlgebraic);

   SCIP_VAR* getCurrentLevelConsVar();
   SCIP_VAR* getCurrentLevelConsOrigVar();

   bool currentLevelConsHasVar();

   /** Methods for obtaining information from structure through scip pointers */
   std::pair<unsigned int, unsigned int> getVarTimes( SCIP_VAR *var );

   SCIP_VAR *getNext( SCIP_VAR *var );

   SCIP_VAR *getPrevious( SCIP_VAR *var );

   unsigned int getConsTime( SCIP_VAR *var );

   /* Getters and setters */
   bool isValid() const;

   SCIP_RETCODE setIsValid( bool isValid );

   bool isReformulated() const;

   SCIP_RETCODE setIsReformulated( bool isReformulated );

   bool isTranformed() const;

   SCIP_RETCODE setIsTransformed(bool isReformulated);

   SCIP_Real getTinit();

   SCIP_Real getTfinal();

   SCIP_Real getTstep();

   void setTstep(SCIP_Real);

   void setTinit(SCIP_Real tinit);

   void setTfinal(SCIP_Real tfinal);

   BoundMap getStrictBounds();

   void setStrictBounds(BoundMap boundMap);

private:

   AlgebraicMap propCuts_;

   std::size_t nStates_;
   std::size_t nAlgebraic_;
   std::size_t nControls_;

   std::vector<SDVariable> algebraic_;
   std::vector<SDVariable> explDiff_;
   std::vector<SDControl> control_;

   bool isValid_;
   bool isReformulated_;
   bool atTimeZero_;
   bool isXdotContinuous_;
   bool isSimulation_;
   bool isTranformed_;

   unsigned int currentTime_;

   std::vector<SDVariable>::iterator algebraicIt_;
   std::vector<SDVariable>::iterator explDiffIt_;
   std::vector<SDControl>::iterator controlIt_;
   std::vector<SDControl>::iterator controlItEnd_;
   SDListBuilder<SDVariable, int> algebraicBuilder_;
   SDListBuilder<SDVariable, int> explDiffBuilder_;
   SDListBuilder<SDControl, int> controlBuilder_;
   std::vector<SCIP_CONS *>::iterator cutsIt_;

   int levelLeft_;

   std::unordered_map<std::pair<int, int>, SDCons, boost::hash<std::pair<int, int>> > minmax_map_;
   std::unordered_map<SCIP_VAR*, SDVariable *> backwardDiffVarMap_;
   std::unordered_map<SCIP_VAR*, SDVariable *> backwardAlgebraicVarMap_;
   std::unordered_map<SCIP_VAR*, SDControl *> backwardCtrlMap_;

   SDproblemStructureInterface::SD_VAR_TYPE varIterState;

   std::vector<SCIP_EXPR *> xdot_;
   std::vector<SCIP_EXPR *> xdotAlgebraic_;
   std::vector<SCIP_EXPR *> algebraicExpr_;
   std::vector<SCIP_Real> xdotParams_;
   unsigned int nParamsPerTime_;
   std::vector<std::string> algebraicVarNames_;
   std::vector<std::string> stateVarNames_;
   std::vector<std::string> controlVarNames_;

   BoundMap boundMap_;
   SCIP_Real tinit;
   SCIP_Real tfinal;
   SCIP_Real tstep;

};

} /* namespace sdscip */

#endif /* SDPROBLEMSTRUCTUREV1_H_ */
