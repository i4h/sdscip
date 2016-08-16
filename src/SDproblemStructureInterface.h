/*
 * SDproblemStructureInterface.h
 *
 *  Created on: 05.02.2015
 *      Author: bzfvierh
 */

#ifndef SDPROBLEMSTRUCTUREINTERFACE_H_
#define SDPROBLEMSTRUCTUREINTERFACE_H_

#include <vector>
#include <map>
#include <boost/regex.hpp>

#include "scip/scip.h"
#include "SDVarBasic.h"
#include "sdo/ButcherTableau.hpp"

namespace ctrl {

class SDproblemStructureInterface
{
public:

   using BoundKey = std::pair<int, SCIP_BOUNDTYPE>;
   using BoundMap = std::map<BoundKey, SCIP_Real>;

   enum SD_CONS_TYPE
   {
      DEFAULT_ALGEBRAIC_CONS = 0
      ,MIN = 5
      ,MAX = 6
      ,SOS2_LOOKUP = 8
   };

   enum SD_VAR_TYPE
   {
      STATE = 0
      ,ALGEBRAIC= 1
      ,CONTROL = 11
   };


   virtual ~SDproblemStructureInterface() {}
   SDproblemStructureInterface(SCIP* scip) :

         scip_(scip)
   {
      setRegexes();
   }

   /* The interface provides regular expressions*/
   boost::regex varRegex_;
   boost::regex consRegex_;

   SCIP* scip_;

   void setRegexes()
   {
      varRegex_.assign(std::string("(?:(?:t_)*)+([A-Za-zäöüÄÖÜß0-9 ]+)_?([a-z])?(?:_([0-9]*))?(?:_([0-9]*))?\\(([0-9]+)(?:,[0-9]+)*\\)"), boost::regex_constants::icase);
      /* this matches a constraint name with the format prefix_ConstraintName_Level_Type(Time,stepIndex) */
      consRegex_.assign(std::string("(?:[t_]*)?[A-Za-zäöüÄÖÜß0-9\\-]+_([A-Za-zäöüÄÖÜß0-9\\-]+)_?([0-9]+)?_?([0-9]+)?_?([a-z0-9]+)?\\(([0-9]+)(?:,[0-9]+)*\\)"), boost::regex_constants::icase);
   }
   boost::regex getConsRegex() {
      return consRegex_;
   }
   boost::regex getVarRegex() {
      return varRegex_;
   }

   /* Reset state of this instance */
   virtual SCIP_RETCODE clear() = 0;

   /* Check expressions in xDot for absolute continuity  */
   virtual bool isXdotContinuous() {
      assert(false);
      return true;
   };

   /* Returns if the problem is a simulation problem, i.e. there are no non-degenerate intervals in initial set or in control variables */
   virtual bool isSimulation() {
      assert(false);
      return true;
   };

   /* Notify problemStructure that initial read of problem structure is finished */
   virtual SCIP_RETCODE doneReading() = 0;

   /* Methods for building problem structure */
   virtual SCIP_RETCODE addControlVar(SCIP_VAR* var,int index, unsigned int firstTime, unsigned int lastTime, int sdVarId) = 0;
   virtual SCIP_RETCODE addVariable(int index,SCIP_VAR* var,unsigned int time, SD_VAR_TYPE type, int sdVarId) = 0;
   virtual SCIP_RETCODE addAlgebraicCons( SCIP_CONS* cons, SCIP_VAR* forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId) = 0;
   virtual SCIP_RETCODE addExplicitDifferential(SCIP_CONS* cons, SCIP_VAR* explicitVar, int index, unsigned int time, int sdVarId) = 0;
   virtual SCIP_RETCODE addCut(SCIP_CONS* cut, unsigned int time) = 0;

   /* Get general information about the problem */
   virtual unsigned int getNStates();
   virtual unsigned int getNControls();
   virtual unsigned int getNAlgebraic();
   /* Strings with the names of the states of the problem, sorted alphabetically! */
   virtual std::vector<std::string> getStateVarNames();
   virtual std::vector<std::string> getAlgebraicVarNames();
   virtual std::vector<std::string> getControlVarNames();

   /* Gets a variable name from varId */
   std::string getVarName(unsigned int varId);
   virtual void setStateVarNames(std::vector<std::string>) {}
   virtual void setControlVarNames(std::vector<std::string>) {}
   virtual void setAlgebraicVarNames(std::vector<std::string>) {}


   /* Gets a variable id from index */
   //TODO _reformulate
   virtual int getVarId(int varIndex);

   /* Gets variables and constraints created by cons_nonlinear at currentTime */
   //TODO _reformulate

   /** Methods for traversing problem structure */

   /* Iterate time steps of the problem */
   virtual int startTimeIteration() = 0;
   virtual int startTimeIteration(int time);
   virtual bool timesLeft() = 0;
   virtual unsigned int incrementTime() = 0;
   virtual unsigned int getCurrentTime();

   /* Get the last time represented in the current problem structure */
   virtual unsigned int getLastTime() = 0;

   /* Iterate variables */
   virtual void startVarIteration() = 0;
   virtual bool varsLeft() = 0;
   virtual void incrementVar() = 0;
   virtual SDVarBasic getCurrentVar() = 0;

   /* Iterate state variables */
   virtual void startStateVarIteration();
   virtual bool stateVarsLeft();
   virtual void incrementStateVar();
   virtual SCIP_VAR* getCurrentStateVar();
   virtual SCIP_VAR* getCurrentStateVarOrig();
   virtual int getCurrentStateVarId();

   /* Iterate differential constraints with forward variables*/
   virtual void startDiffConsIteration() = 0;
   virtual void startDiffConsIteration(unsigned int time) = 0;
   virtual bool diffConsLeft() = 0;
   virtual bool diffConsLeft(unsigned int time) = 0;
   virtual void incrementDiffCons() = 0;
   virtual SCIP_VAR* getDiffConsVar() = 0;
   /* Get a vector with the variables of the current differential constraint that go back n timesteps
    * i.e. getDiffConsLastVars(2) when current diffconsvar is x(5) should return a vector with pointers to x(3),x(4),x(5)
    */
   virtual std::vector<SCIP_VAR*> getDiffConsLastVars(int n) = 0;
   virtual SCIP_CONS* getDiffConsCons() = 0;

   /* Iterate control variables  */
   virtual void startControlVarIteration() = 0;
   virtual void startControlVarIteration(unsigned int time) = 0;
   virtual bool controlVarsLeft() = 0;
   virtual bool controlVarsLeft(unsigned int time) = 0;
   virtual void incrementControlVar() = 0;
   virtual SCIP_VAR* getControlVar() = 0;

   virtual void startControlVarAtTIteration();
   virtual void startControlVarAtTIteration(unsigned int time);
   virtual bool controlVarsAtTLeft();
   virtual bool controlVarsAtTLeft(unsigned int time);
   virtual void incrementControlVarAtT();
   virtual SCIP_VAR* getControlVarAtT();
   virtual SCIP_VAR* getControlVarAtTOrig();


   /* Get particular control variables */

   /* This function gets the control variable(s) at position n in the list of individual control variables ordered by time
    * of first appearance. This is NOT equivalent to the list of control variables at time t.
    */
   virtual SCIP_VAR* getNthsControlVar(unsigned int n);
   virtual SCIP_Bool isControlVar(SCIP_VAR* var);
   virtual int getControlVarBeginTime(SCIP_VAR* var);
   virtual SCIP_Bool isStateVar(SCIP_VAR* var);
   virtual int getStateVarTime(SCIP_VAR* var);


   /* Iterate list of algebraic constraints with forward variables */
   virtual void startAlgebraicConsIteration() {
      startLevelIteration();
      startLevelConsIteration();
   }

   virtual void startAlgebraicConsIteration(unsigned int time) {
      startLevelIteration(time);
      startLevelConsIteration();
   }

   virtual bool algebraicConsLeft() {
      if(!levelConsLeft())
      {
         if(!levelsLeft())
            return false;
         incrementLevel();
         if(levelsLeft())
         {
            startLevelConsIteration();
            return levelConsLeft();
         }
         return false;
      }
      return true;
   }

   virtual bool algebraicConsLeft(unsigned int time) {
      if(!levelConsLeft())
      {
         if(!levelsLeft(time))
            return false;
         incrementLevel();
         if(levelsLeft(time))
         {
            startLevelConsIteration();
            return levelConsLeft();
         }
         return false;
      }
      return true;
   }

   virtual void incrementAlgebraicCons() {
      incrementLevelCons();
   }

   virtual SCIP_CONS* getAlgebraicCons() {
      return getCurrentLevelConsCons();
   }

   virtual SCIP_VAR* getAlgebraicVar() {
      return getCurrentLevelConsVar();
   }

   virtual SCIP_VAR* getAlgebraicVarOrig() {
      return getCurrentLevelConsOrigVar();
   }


   /* Iterate cuts */
   virtual void startCutIteration() = 0;
   virtual void startCutIteration(unsigned int time) = 0;
   virtual bool cutsLeft() = 0;
   virtual bool cutsLeft(unsigned int time) = 0;
   virtual void incrementCut() = 0;
   virtual SCIP_CONS* getCut() = 0;

   /* Iterate constraint levels at given time */
   virtual void startLevelIteration() = 0;
   virtual void startLevelIteration(unsigned int time) = 0;
   virtual bool levelsLeft() = 0;
   virtual bool levelsLeft(unsigned int time) = 0;
   virtual void incrementLevel() = 0;
   virtual int getCurrentLevel() = 0;
   virtual SD_CONS_TYPE getCurrentLevelType() = 0;

   /* Iterate constraints and (if set) forward variables at current time and level */
   virtual void startLevelConsIteration() = 0;
   virtual bool levelConsLeft() = 0;
   virtual void incrementLevelCons() = 0;
   virtual SCIP_CONS* getCurrentLevelConsCons() = 0;
   virtual SCIP_VAR* getCurrentLevelConsVar();
   virtual SCIP_VAR* getCurrentLevelConsOrigVar();
   virtual bool currentLevelConsHasVar() = 0;

   /** Methods for obtaining information from structure through scip pointers */
   virtual std::pair<unsigned int, unsigned int> getVarTimes(SCIP_VAR* var); /* Return start and end time of variable appearance */
   virtual SCIP_VAR* getNext(SCIP_VAR* var); /* Get variable that is next in time*/
   virtual SCIP_VAR* getPrevious(SCIP_VAR* var); /* Get variable that is previous in time */
   virtual unsigned int getConsTime(SCIP_VAR* var);

   /* Getters and setters */
   virtual bool isValid() const = 0;
   virtual SCIP_RETCODE setIsValid(bool isValid) = 0;
   virtual bool isReformulated() const = 0;
   virtual SCIP_RETCODE setIsReformulated(bool isReformulated) = 0;
   virtual bool isTranformed() const;
   virtual SCIP_RETCODE setIsTransformed(bool isReformulated);
   /* Helpers */
   virtual std::string getVarBasename(SCIP_VAR* var);
   virtual std::string getStateVarList();
   virtual std::string getControlVarList();
   virtual std::string getAlgebraicVarList();
   std::string implode( const std::string &glue, const std::vector<std::string> &pieces );


   /* Get derivatives of state variables with parameters */
   virtual SCIP_EXPR** getXdot();
   virtual SCIP_EXPR** getXdotAlgebraic();
   virtual SCIP_EXPR** getAlgebraicExpressions();
   virtual SCIP_Real* getXdotParams();
   virtual int getNParamsPerTime();
   virtual SCIP_Real* getXdotParams(int time);
   //TODOs:
   virtual SCIP_Real* getXdotParams(SCIP_Real time);
   virtual SCIP_Real getTinit();
   virtual SCIP_Real getTfinal();

   /* returns a bound map with all strict state bounds of the problem,
    * i.e. bounds that invalidate absolute continuity if they are violated
    */
   virtual BoundMap getStrictBounds() {
      assert(false);
      return BoundMap();
   };
   virtual void setStrictBounds(BoundMap) {};
   virtual SCIP_Real getTstep() { return -1; }
   virtual void setTstep(SCIP_Real) {}
   virtual void setTinit(SCIP_Real tinit) {}
   virtual void setTfinal(SCIP_Real tfinal) {}

   virtual void setXdotParams(std::vector<SCIP_Real>, unsigned int nParamsPerTime) {}
   virtual void setXdot(std::vector<SCIP_EXPR*>) {}
   virtual void setXdotAlgebraic(std::vector<SCIP_EXPR*>) {}
   virtual void setAlgebraicExpressions(  std::vector<SCIP_EXPR *> algebraicExpr ) {}

   static sdo::ButcherTableau getButcherTableau(SCIP* scip, const char* discretization);
   static sdo::ButcherTableau getButcherTableau(SCIP* scip, std::string discretization);

   std::vector<SCIP_Interval> getStateBounds();
   BoundMap getStateBoundsMap();

   std::vector<SCIP_Interval> getControlBounds();

   /* Returns a vector of intervals that include the current control bound intervals as well as the oldControlBounds given as parameter */
   std::vector<SCIP_Interval> getMaxControlBounds(const std::vector<SCIP_Interval>& oldControlBounds);

   /* Returns a vector of intervals that include the current state bound intervals as well as the oldStateBounds given as parameter */
   std::vector<SCIP_Interval> getMaxStateBounds(const std::vector<SCIP_Interval>& oldStateBounds);

   /* Returns a BoundMap that returns bounds that the current state bound intervals as well as the oldStateBounds given as parameter,
    * iff the bounds are better than infinity */
   BoundMap getMaxStateBoundsBoundMap(const std::vector<SCIP_Interval>& oldStateBounds);
};

} /* namespace ctrl */

#endif /* SDPROBLEMSTRUCTUREINTERFACE_H_ */
