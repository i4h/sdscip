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

/**@file    SDproblemStructureExtendedInterface.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDPROBLEMSTRUCTUREINTERFACE_H_
#define SDPROBLEMSTRUCTUREINTERFACE_H_

#include <vector>
#include <map>
#include <boost/regex.hpp>

#include "sdscip.h"
#include "SDVarBasic.h"

namespace sdscip {

class SDproblemStructureExtendedInterface
{
public:

   virtual ~SDproblemStructureExtendedInterface() {}

   /* The interface provides regular expressions*/
   boost::regex varRegex_;
   boost::regex consRegex_;

   void setRegexes()
   {
      SCIPdbgMsg("setting regexes\n");
      SCIPdebugMessage("setting rexes\n");
      printf("Setting regexes\n");
      varRegex_.assign(std::string("(?:t_)+([A-Za-z0-9]+)_?([a-z])?(?:_([0-9*]))?(?:_([0-9*]))?\\(([0-9]+)(?:,[0-9]+)*\\)"), boost::regex_constants::icase);
      /* this matches a constraint name like prefix_ConstraintName_Level_Type(Time,uninterestingIndex) */
      consRegex_.assign(std::string("(?:t_)?[A-Za-z0-9\\-]+_([A-Za-z0-9\\-]+)_?([0-9]+)?_?([0-9]+)?_?([a-z0-9]+)?\\(([0-9]+)(?:,[0-9]+)*\\)"), boost::regex_constants::icase);
   }
   boost::regex getConsRegex() {
      return consRegex_;
   }
   boost::regex getVarRegex() {
      return varRegex_;
   }

   /* Interface methods */

   /* Reset state of this instance */
   virtual SCIP_RETCODE clear() = 0;

   /* Notify that initial read of problem structure is finished */
   virtual SCIP_RETCODE doneReading() = 0;

   /* Methods for building problem structure */
   virtual SCIP_RETCODE addControlVar(SCIP_VAR* var,int index, unsigned int firstTime, unsigned int lastTime) = 0;
   virtual SCIP_RETCODE addVariable(int index,SCIP_VAR* var,unsigned int time, int type) = 0;
   virtual SCIP_RETCODE addAlgebraicCons(SCIP_CONS* cons, SCIP_VAR* forwardVar, unsigned int time, int level, int type) = 0;
   virtual SCIP_RETCODE addExplicitDifferential(SCIP_CONS* cons, SCIP_VAR* explicitVar, int index, unsigned int time) = 0;
   virtual SCIP_RETCODE addCut(SCIP_CONS* cut, unsigned int time) = 0;
   virtual void registerTime(unsigned int time) = 0;

   /** Methods for traversing problem structure */

   /* Iterate time steps of the problem */
   virtual int startTimeIteration() = 0;
   virtual bool timesLeft() = 0;
   virtual unsigned int incrementTime() = 0;
   virtual unsigned int getLastTime() = 0;

   /* Iterate variables */
   virtual void startVarIteration() = 0;
   virtual bool varsLeft() = 0;
   virtual void incrementVar() = 0;
   virtual SDVarBasic getCurrentVar() = 0;

   /* Iterate differential constraints with forward variables */
   virtual void startDiffConsIteration() = 0;
   virtual void startDiffConsIteration(unsigned int time) = 0;
   virtual bool diffConsLeft() = 0;
   virtual bool diffConsLeft(unsigned int time) = 0;
   virtual void incrementDiffCons() = 0;
   virtual SCIP_VAR* getDiffConsVar() = 0;
   /* Get a vector with the variables of the current differential constraint that go back n timesteps
    * i.e. getDiffConsLastVars(2) when current diffconsvar is x(5) should return a vector with pointers to x(3),x(4),x(5)
    */
   std::vector<SCIP_VAR*> getDiffConsLastVars(int n) = 0;
   virtual SCIP_CONS* getDiffConsCons() = 0;

   /* Iterate control variabels  */
   virtual void startControlVarIteration() = 0;
   virtual void startControlVarIteration(unsigned int time) = 0;
   virtual bool controlVarsLeft() = 0;
   virtual bool controlVarsLeft(unsigned int time) = 0;
   virtual void incrementControlVar() = 0;
   virtual SCIP_VAR* getControlVar() = 0;

   /* Iterate list of algebraic constraints with forward variables */
   virtual void startAlgebraicConsIteration() = 0;
   virtual void startAlgebraicConsIteration(unsigned int time) = 0;
   virtual bool algebraicConsLeft() = 0;
   virtual bool algebraicConsLeft(unsigned int time) = 0;
   virtual void incrementAlgebraicCons() = 0;
   virtual SCIP_CONS* getAlgebraicCons() = 0;

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
   virtual int getCurrentLevelType() = 0;

   /* Iterate constraints and (if set) forward variables at current time and level */
   virtual void startLevelConsIteration() = 0;
   virtual bool levelConsLeft() = 0;
   virtual void incrementLevelCons() = 0;
   virtual SCIP_CONS* getCurrentLevelConsCons() = 0;

   //TODO
   /* Returns the appropriate min/max/sos2 (...?) object representing the complete level */
   //virtual ???? getCurrentLevelConsObject() = 0;

   virtual SCIP_VAR* getCurrentLevelConsVar() = 0;
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

};

} /* namespace sdscip */

#endif /* SDPROBLEMSTRUCTUREINTERFACE_H_ */
