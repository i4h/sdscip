/*
 * SDproblemStructure.h
 *
 *  Created on: 03.02.2015
 *      Author: bzfvierh
 */

#ifndef SDPROBLEMSTRUCTURE_H_
#define SDPROBLEMSTRUCTURE_H_

#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <sstream>

#include "sdscip.h"
#include "SDVarBasic.h"
#include "SDproblemStructureInterface.h"



namespace ctrl {


class SDproblemStructure : public SDproblemStructureInterface
{
public:

   /* Classes used for construction */
   typedef std::vector<SCIP_VAR*> VarVec;
   typedef std::map<unsigned int, unsigned int> IntIntMap;
   typedef std::pair<SCIP_CONS*,SCIP_VAR*> ConsVarPair;
   typedef std::pair<SD_VAR_TYPE, SCIP_VAR*> TypeVarPair;
   typedef std::map<unsigned int, SCIP_VAR* > IntVarMap;
   typedef std::vector< ConsVarPair > ConsVarVec;
   typedef std::pair < SD_CONS_TYPE, ConsVarVec> TypeConsPair;
   typedef std::map <int, TypeConsPair> LevelConsMap;

   // Classes used for instance variables
   typedef std::map<unsigned int, ConsVarVec > ExplicitDifferentialMap;
   typedef std::map<unsigned int, std::vector<SCIP_CONS*> > AlgebraicMap;
   typedef std::map<unsigned int, LevelConsMap > AlgebraicConsMap;
   typedef std::map<unsigned int, std::map<unsigned int, TypeVarPair > > VarTimeTypeMap;
   typedef std::map<unsigned int, VarVec > VarVecMap;
   typedef std::map<unsigned int, std::vector<SCIP_CONS*> > PropCutMap;

   SDproblemStructure(SCIP* scip);
   virtual ~SDproblemStructure();

   /* Reset state of this instance */
   SCIP_RETCODE clear();

   /* Notify problemStructure that initial read of problem structure is finished */

   SCIP_RETCODE doneReading();

   /* Methods for building problem structure */
   SCIP_RETCODE addControlVar(SCIP_VAR* var,int index, unsigned int firstTime, unsigned int lastTime, int sdVarId);
   SCIP_RETCODE addVariable(int index,SCIP_VAR* var,unsigned int time, SDproblemStructureInterface::SD_VAR_TYPE type, int sdVarId);
   SCIP_RETCODE addAlgebraicCons(SCIP_CONS* cons, SCIP_VAR* forwardVar, unsigned int time, int level, SDproblemStructureInterface::SD_CONS_TYPE type, int sdVarId);
   SCIP_RETCODE addExplicitDifferential(SCIP_CONS* cons, SCIP_VAR* explicitVar, int index, unsigned int time, int sdVarId);
   SCIP_RETCODE addCut(SCIP_CONS* cut, unsigned int time);
   void registerTime(unsigned int time);

   /** Methods for traversing problem structure */

   /* Iterate time steps of the problem */
   int startTimeIteration();
   int startTimeIteration(int time);
   bool timesLeft();
   unsigned int incrementTime();
   unsigned int getCurrentTime();

   unsigned int getLastTime();

   /* Iterate variables */
   void startVarIteration();
   bool varsLeft();
   void incrementVar();
   SDVarBasic getCurrentVar();

   /* Iterate state variables */
   void startStateVarIteration();
   bool stateVarsLeft();
   void incrementStateVar();
   SCIP_VAR* getCurrentStateVar();

   /* Iterate differential constraints with forward variables*/
   void startDiffConsIteration();
   void startDiffConsIteration(unsigned int time);
   bool diffConsLeft();
   bool diffConsLeft(unsigned int time);
   void incrementDiffCons();
   SCIP_VAR* getDiffConsVar();
   /* Get a vector with the variables of the current differential constraint that go back n times
    * i.e. getDiffConsLastVars(2) when current diffconsvar is x(5) should return a vector with x(3),x(4),x(5)
    */
   std::vector<SCIP_VAR*> getDiffConsLastVars(int n);

   SCIP_CONS* getDiffConsCons();

   /* Iterate control variabels  */
   void startControlVarIteration();
   void startControlVarIteration(unsigned int time);
   bool controlVarsLeft();
   bool controlVarsLeft(unsigned int time);
   void incrementControlVar();
   SCIP_VAR* getControlVar();

   void startControlVarAtTIteration();
   void startControlVarAtTIteration(unsigned int time);
   bool controlVarsAtTLeft();
   bool controlVarsAtTLeft(unsigned int time);
   void incrementControlVarAtT();
   SCIP_VAR* getControlVarAtT();


   /* Get particular control variables */
   SCIP_VAR* getNthsControlVar(unsigned int n);
   SCIP_Bool isControlVar(SCIP_VAR* var);
   int getControlVarTime(SCIP_VAR* var);
   SCIP_Bool isStateVar(SCIP_VAR* var);
   int getStateVarTime(SCIP_VAR* var);


   unsigned int getNStates();
   unsigned int getNControls();
   std::vector<std::string> getStateVarNames();
   std::vector<std::string> getControlVarNames();


   /* Iterate list of algebraic constraints with forward variables */
   void startAlgebraicConsIteration();
   void startAlgebraicConsIteration(unsigned int time);
   bool algebraicConsLeft();
   bool algebraicConsLeft(unsigned int time);
   void incrementAlgebraicCons();
   SCIP_CONS* getAlgebraicCons();

   /* Iterate cuts */
   void startCutIteration();
   void startCutIteration(unsigned int time);
   bool cutsLeft();
   bool cutsLeft(unsigned int time);
   void incrementCut();
   SCIP_CONS* getCut();

   /* Iterate constraint levels at given time */
   void startLevelIteration();
   void startLevelIteration(unsigned int time);
   bool levelsLeft();
   bool levelsLeft(unsigned int time);
   void incrementLevel();
   int getCurrentLevel();
   SD_CONS_TYPE getCurrentLevelType(); // Maybe getCurrentLevelConsType?

   /* Iterate constraints and possibly forward variables at current time and level */
   void startLevelConsIteration();
   bool levelConsLeft();
   void incrementLevelCons();
   SCIP_CONS* getCurrentLevelConsCons();
   SCIP_VAR* getCurrentLevelConsVar();
   bool currentLevelConsHasVar();

   virtual std::pair<unsigned int, unsigned int> getVarTimes(SCIP_VAR* var); /* Return start and end time of variable appearance */
   virtual SCIP_VAR* getNext(SCIP_VAR* var); /* Get variable that is next in time*/
   virtual SCIP_VAR* getPrevious(SCIP_VAR* var); /* Get variable that is previous in time */
   virtual unsigned int getConsTime(SCIP_VAR* var);


   /* Getters and setters */
   bool isValid() const;
   SCIP_RETCODE setIsValid(bool isValid);
   bool isReformulated() const;
   SCIP_RETCODE setIsReformulated(bool isReformulated);
   boost::regex getConsRegex();
   boost::regex getVarRegex();

   /* Helpers */
   std::string getStateVarList();


private:
   SCIP_RETCODE setStateVars();
   SCIP_RETCODE setControlVars();
   std::string implode( const std::string &glue, const std::vector<std::string> &pieces );

   unsigned int nStates_;
   unsigned int nControls_;
   std::vector<std::string> stateVarNames_;
   std::vector<std::string> controlVarNames_;

   AlgebraicMap algebraic_;
   AlgebraicMap propCuts_;
   AlgebraicConsMap algebraicConstraints_;
   ExplicitDifferentialMap explicitDifferential_;
   VarTimeTypeMap variableTypes_;              /*variableTypes_[unsigned int time][int SCIPvarId] = std::pair<varType, Pointer>, varType= 0: state variable, varType = 1: algebraic */
   VarVecMap controlVariables_; /* Control variables at  the times of their first appearances */
   VarVecMap controlVariablesAtT_; /* All control variables that appear at given time */
   VarVecMap stateVariables_; /* State variables at times t, ordered according to the names in stateVarNames */
   IntIntMap stateVariableTimes_; /* stateVariableTimes_[SCIPfvarIndex] = varTime */
   IntIntMap controlVariableTimes_; /* stateVariableTimes_[SCIPfvarIndex] = varTime */


   bool isValid_;
   bool isReformulated_;
   bool atTimeZero_;

   unsigned int currentTime_;
   unsigned int lastTime_;

   /* Private iterators */
   std::map<unsigned int, TypeVarPair >::iterator varIt_;
   VarVec::iterator stateVarIt_;
   bool stateVarItProtector_;
   VarVec::iterator controlVarIt_;
   VarVec::iterator controlVarAtTIt_;
   std::vector<SCIP_CONS*>::iterator algebraicConsIt_;
   std::vector<SCIP_CONS*>::iterator cutsIt_;

   LevelConsMap::iterator levelIt_;
   ConsVarVec::iterator levelConsIt_;
   ConsVarVec::iterator diffConsIt_;

};

} /* namespace ctrl */

#endif /* SDPROBLEMSTRUCTURE_H_ */
