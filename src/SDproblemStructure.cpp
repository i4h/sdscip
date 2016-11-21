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

/**@file    SDproblemStructure.cpp
 * @brief   Old version of problem structure
 * @author  Ingmar Vierhaus
 *
 */


#include "SDproblemStructure.h"

namespace sdscip {

SDproblemStructure::SDproblemStructure(SCIP* scip) :
   SDproblemStructureInterface(scip)
{
   clear();
}

SCIP_RETCODE SDproblemStructure::clear() {
   /* Reset the state of this object */
   nStates_ = 0;
   isValid_ = false;
   currentTime_ = 0;
   atTimeZero_ = true;
   isReformulated_ = false;
   stateVarItProtector_ = false;
   lastTime_ = 0;
   algebraic_.clear();
   propCuts_.clear();
   algebraicConstraints_.clear();
   explicitDifferential_.clear();
   variableTypes_.clear();
   controlVariables_.clear();
   controlVariablesAtT_.clear();
   return SCIP_OKAY;
}

SDproblemStructure::~SDproblemStructure() {}

boost::regex SDproblemStructure::getConsRegex() {
   return consRegex_;
}

boost::regex SDproblemStructure::getVarRegex() {
   return varRegex_;
}

SCIP_RETCODE SDproblemStructure::setStateVars() {
   /* Get the basenames of the state vars at t = ?*/
   /* We expect this to be populated only once */
   assert(stateVarNames_.size() == 0);
   std::map<unsigned int, TypeVarPair >::iterator varIt;
   for (varIt = variableTypes_[3].begin(); varIt != variableTypes_[3].end(); ++varIt)
   {
      int type = varIt->second.first;
      if (type == STATE)
      {
         SCIP_VAR* var = varIt->second.second;
         /* Get basename */
         boost::cmatch matches;
         if (boost::regex_match(SCIPvarGetName(var), matches, getVarRegex()) )
         {
            std::string varName(matches[1].first,matches[1].second);
            stateVarNames_.push_back(varName);
         }
         else
         {
            SCIPerrorMessage("unable to match variable name %s\n", SCIPvarGetName(var));
         }
      }
   }
   nStates_ = stateVarNames_.size();


   /* Sort the state var names */
   std::sort(stateVarNames_.begin(), stateVarNames_.end());

   /* Populate state variables vector, by searching the variables at every time */
   for( int currentTime = startTimeIteration(); timesLeft(); currentTime = incrementTime() )
   {
      for( auto it = stateVarNames_.begin(); it != stateVarNames_.end(); ++it)
      {
         /* Build variable name */
        std::ostringstream os;
        os << "t_" << *it << "(" << currentTime << ")";
        std::string fullVarName(os.str());
        SCIP_VAR* var(SCIPfindVar(scip_, fullVarName.c_str()));
        if( var != NULL )
        {
           stateVariables_[currentTime].push_back(var);
           stateVariableTimes_[SCIPvarGetIndex(var)] = currentTime;
           SCIPdbgMsg("adding origvar %s with index %i at time %i\n", SCIPvarGetName(var), SCIPvarGetIndex(var), currentTime);
           if (SCIPgetStage(scip_) >= SCIP_STAGE_TRANSFORMED && SCIPvarIsOriginal(var))
           {
              SCIP_VAR* transvar;
              SCIPgetTransformedVar(scip_, var, &transvar );
              SCIPdbgMsg("adding transvar %s with index %i at time %i\n", SCIPvarGetName(transvar), SCIPvarGetIndex(transvar), currentTime);
              stateVariableTimes_[SCIPvarGetIndex(transvar)] = currentTime;
           }
        }
        else
        {
           SCIPerrorMessage("unable to find state var %s\n", fullVarName.c_str());
        }
      }
   }
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructure::setControlVars() {
   /* Get the basenames of the control vars at t = 1*/
   /* We expect this to be populated only once */
   assert(controlVarNames_.size() == 0);
   VarVec::iterator varIt;
   SCIPdbgMsg("setting control variables, starting iteration\n");
   for (varIt = controlVariablesAtT_[1].begin(); varIt != controlVariablesAtT_[1].end(); ++varIt)
   {
      SCIPdbgMsg("found one \n");
      SCIP_VAR* var(*varIt);
      /* Get basename */
      boost::cmatch matches;
      if (boost::regex_match(SCIPvarGetName(var), matches, getVarRegex()) )
      {
         std::string varName(matches[1].first,matches[1].second);
         controlVarNames_.push_back(varName);
      }
      else
      {
         SCIPerrorMessage("unable to match variable name %s\n", SCIPvarGetName(var));
      }

   }
   nControls_ = controlVarNames_.size();
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructure::doneReading()
{
   SCIP_CALL( setStateVars() );
   SCIP_CALL( setControlVars() );

   SCIPdbgMsg("setting structure to valid\n");
   this->setIsValid(true);


   return SCIP_OKAY;
}

 std::pair<unsigned int, unsigned int> SDproblemStructure::getVarTimes(SCIP_VAR* var)
{
   //TODO _SD: This only works for some cases ... pending better problemStructure implementation
   boost::cmatch matches;
   if (!boost::regex_match(SCIPvarGetName(var), matches, this->getVarRegex() ))
      assert(false);
   std::string varTimeString(matches[5].first,matches[5].second);
   int vartime = atoi(varTimeString.c_str());
   return std::pair<unsigned int, unsigned int>(vartime, vartime);
}

SCIP_VAR* SDproblemStructure::getNext(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* returnVar(NULL);
   return returnVar;
}
SCIP_VAR* SDproblemStructure::getPrevious(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* returnVar(NULL);
   return returnVar;
}
unsigned int SDproblemStructure::getConsTime(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

bool SDproblemStructure::isValid() const
{
   return isValid_;
}

SCIP_RETCODE SDproblemStructure::setIsValid(bool _isValid)
{
   isValid_ = _isValid;
   return SCIP_OKAY;
}

bool SDproblemStructure::isReformulated() const
{
   return isReformulated_;
}

SCIP_RETCODE SDproblemStructure::setIsReformulated(bool _isReformulated)
{
   isReformulated_ = _isReformulated;
   SCIPdebugMessage("setting isReformulated to true\n");
   assert(false);
   return SCIP_OKAY;
}

void SDproblemStructure::registerTime(unsigned int time)
{
   if (lastTime_ < time)
   {
      lastTime_ = time;
   }
}

SCIP_RETCODE SDproblemStructure::addControlVar(SCIP_VAR* var,int index, unsigned int firstTime, unsigned int lastTime, int sdVarId)
{
   this->registerTime(lastTime);
   controlVariables_[firstTime].push_back(var); /* Control is not necessarily time indexed, we add it to the first appearing time */
   SCIPdbgMsg("adding control var %s to controlVariables[%i]\n",SCIPvarGetName(var), firstTime);
   for (unsigned int i = firstTime; i <= lastTime; ++i)
      controlVariablesAtT_[i].push_back(var); /* Control is not necessarily time indexed, we add it to the first appearing time */

   /* Add control variable and its transformed to controlVariableTimes_ */
   controlVariableTimes_[SCIPvarGetIndex(var)] = firstTime;
   SCIPdbgMsg("adding origvar %s with index %i at time %i\n", SCIPvarGetName(var), SCIPvarGetIndex(var), firstTime);
   if (SCIPgetStage(scip_) >= SCIP_STAGE_TRANSFORMED && SCIPvarIsOriginal(var))
   {
      SCIP_VAR* transvar;
      SCIPgetTransformedVar(scip_, var, &transvar );
      SCIPdbgMsg("adding transvar %s with index %i at time %i\n", SCIPvarGetName(transvar), SCIPvarGetIndex(transvar), firstTime);
      controlVariableTimes_[SCIPvarGetIndex(transvar)] = firstTime;
   }

   return SCIP_OKAY;
}
SCIP_RETCODE SDproblemStructure::addVariable(int index,SCIP_VAR* var,unsigned int time, SDproblemStructureInterface::SD_VAR_TYPE type, int sdVarId)
{
   this->registerTime(time);
   if (variableTypes_[time].count(index) == 0)
   {
      SCIPcppDbgMsg("Adding Variable " << SCIPvarGetName(var) << "to bookeeping at time " << time << " as algebraic variable" << std::endl);
      variableTypes_[time][index] = TypeVarPair(type,var);
   }
   else
   {
      SCIPcppDbgMsg("Variable " << SCIPvarGetName(var) << "already exists in bookeeping" << std::endl);
   }

   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructure::addAlgebraicCons(SCIP_CONS* cons, SCIP_VAR* forwardVar, unsigned int time, int level, SDproblemStructureInterface::SD_CONS_TYPE type, int sdVarId)
{
   this->registerTime(time);

   /* Add constraint with time to bookkeeping of constraint handler */
   SCIPdbgMsg("Adding constraint %s to algebraic_ at time %i\n",SCIPconsGetName(cons), time);
   SCIPdbgMsg("Forward var is %s\n", forwardVar == NULL ? "NULL" : SCIPvarGetName(forwardVar));

   algebraic_[time].push_back(cons);

   /* A constraint with type 0 needs a forward variable */
   //assert(algebraicForwardVar != NULL || consType != 0);

   /* Determine details of the constraint and save to algebraicCons */
   ConsVarPair consVar(cons,forwardVar);
   if (algebraicConstraints_[time].count(level) == 0)
   {
      //Make a type/ConsVarVec pair to put there
      ConsVarVec cVVec;
      cVVec.push_back(consVar);

      algebraicConstraints_[time][level] = TypeConsPair(type,cVVec);
      SCIPdbgMsg("Adding typecons pair to algebraicConstraints at %i,%i\n",time,level);
   }
   else
   {
      SCIPdbgMsg("considering time %i, level %i, currently of type %i\n",time,level,algebraicConstraints_[time][level].first);
      //Assert that saved type is okay and push ConsVarPair into the vector at ->second
      assert(type == algebraicConstraints_[time][level].first);
      algebraicConstraints_[time][level].second.push_back(consVar);
      SCIPdbgMsg("Adding typecons pair to algebraicConstraints at %i,%i\n",time,level);
   }

   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructure::addExplicitDifferential(SCIP_CONS* cons, SCIP_VAR* explicitVar, int index, unsigned int time, int sdVarId)
{
   this->registerTime(time);

   SCIPdbgMsg("pushing var %s into explicitDifferential at time %i\n",SCIPvarGetName(explicitVar), time);
   explicitDifferential_[time].push_back(ConsVarPair(cons,explicitVar));
   //Declare the forward Variable as state variable
   //SCIPcppDbgMsg("Adding Variable " << SCIPvarGetName(explicitVar) << "to VariableType Bookkeeping as explicit" << std::endl);
   //SCIPcppDbgMsg("Variable Index is " << explicitVar->index << std::endl);
   SCIPcppDbgMsg("Adding/Replacing Variable " << SCIPvarGetName(explicitVar) << " to/in bookeeping as explicit differential variable" << std::endl);
   variableTypes_[time][index] = std::pair<SDproblemStructureInterface::SD_VAR_TYPE, SCIP_VAR*>(STATE,explicitVar);

   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructure::addCut(SCIP_CONS* cut, unsigned int time)
{
   propCuts_[time].push_back(cut);
   return SCIP_OKAY;
}

/* Iterate over times */

int SDproblemStructure::startTimeIteration()
{
   currentTime_ = 0;
   return 0;
}

int SDproblemStructure::startTimeIteration(int time)
{
   currentTime_ = time;
   return currentTime_;
}


bool SDproblemStructure::timesLeft()
{
   return (currentTime_ != lastTime_ + 1);
}

unsigned int SDproblemStructure::incrementTime()
{
   /* Awkward way to handle the fact that time starts at zero, but first entry in explicitDifferential is at t=1 */
   ++currentTime_;
   return currentTime_;
}

unsigned int SDproblemStructure::getCurrentTime()
{
   return currentTime_;
}

unsigned int SDproblemStructure::getLastTime()
{
   return lastTime_;
}

void SDproblemStructure::startVarIteration()
{
   varIt_ = variableTypes_[currentTime_].begin();
}

bool SDproblemStructure::varsLeft()
{
   return varIt_ != variableTypes_[currentTime_].end();
}

void SDproblemStructure::incrementVar() {
   ++varIt_;
}

SDVarBasic SDproblemStructure::getCurrentVar()
{
   SCIP_VAR* scipVar = varIt_->second.second;
   int type = varIt_->second.first;
   return SDVarBasic(scipVar, currentTime_, type);
}



/* State var Iteration methods */
void SDproblemStructure::startStateVarIteration()
{
   assert(stateVarItProtector_ == false);
   stateVarItProtector_ = true;
   stateVarIt_ = stateVariables_[currentTime_].begin();
}

bool SDproblemStructure::stateVarsLeft()
{
   if (stateVarIt_ == stateVariables_[currentTime_].end())
      stateVarItProtector_ = false;

   return stateVarIt_ != stateVariables_[currentTime_].end();
}

void SDproblemStructure::incrementStateVar() {
   ++stateVarIt_;
}

SCIP_VAR* SDproblemStructure::getCurrentStateVar() {

   if (SCIPgetStage(scip_) >= SCIP_STAGE_TRANSFORMED && SCIPvarIsOriginal(*stateVarIt_))
   {
      SCIP_VAR* transvar;
      SCIP_RETCODE retcode;
      retcode = SCIPgetTransformedVar(scip_, *stateVarIt_, &transvar );
      assert(retcode == SCIP_OKAY);
      return transvar;
   }
   else
      return *stateVarIt_;
}


void SDproblemStructure::startDiffConsIteration()
{
   diffConsIt_ = explicitDifferential_[currentTime_].begin();
}

void SDproblemStructure::startDiffConsIteration(unsigned int time)
{
   diffConsIt_ = explicitDifferential_[time].begin();
}


bool SDproblemStructure::diffConsLeft()
{
   return diffConsIt_ != explicitDifferential_[currentTime_].end();
}

bool SDproblemStructure::diffConsLeft(unsigned int time)
{
   return diffConsIt_ != explicitDifferential_[time].end();
}

void SDproblemStructure::incrementDiffCons()
{
   ++diffConsIt_;
}

SCIP_VAR* SDproblemStructure::getDiffConsVar()
{
   return diffConsIt_->second;
}

unsigned int SDproblemStructure::getNStates() {
   return nStates_;
}

unsigned int SDproblemStructure::getNControls() {
   return nControls_;
}

std::vector<std::string> SDproblemStructure::getStateVarNames() {
   return stateVarNames_;
}

std::vector<std::string> SDproblemStructure::getControlVarNames() {
   return controlVarNames_;
}


std::vector<SCIP_VAR*> SDproblemStructure::getDiffConsLastVars(int n)
{

   SCIP_VAR* startVar(diffConsIt_->second);
   std::vector<SCIP_VAR*> vars;
   vars.push_back(startVar);
#if 0
   boost::cmatch matches;
   if (!boost::regex_match(SCIPvarGetName(startVar), matches, structure_->getVarRegex() ))
      assert(false);

   int type(0);
   std::string varName(matches[1].first,matches[1].second);
   std::string varTimeString(matches[5].first,matches[5].second);
   std::string varControlString(matches[2].first,matches[2].second);
   std::string varLevelString(matches[3].first,matches[3].second);
   std::string varTypeString(matches[4].first,matches[4].second);

   /* Find variables of the same state in diffConsVec */
   for (int i=1; i <= multiTimecutLookback - 1; ++i)
   {
      ConsVarVec::iterator pairIt;
      //for ( pairIt = explicitDifferential_[currentTime_-i].begin(); pairIt != diffConsVec.end(); ++pairIt)

      ConsVarVec::iterator diffConsIt;
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
      if (subscipVar != NULL)
    	  multiTimePattern_.addVar(var, subscipVar);
   }
#endif

   return vars;

}


SCIP_CONS* SDproblemStructure::getDiffConsCons()
{
   return diffConsIt_->first;
}


/* Iterate control varis */
void SDproblemStructure::startControlVarIteration()
{
   SCIPdbgMsg("Starting control Var Iterations, vector has %lu elements\n", controlVariables_.size());
   controlVarIt_ = controlVariables_[currentTime_].begin();
}

void SDproblemStructure::startControlVarIteration(unsigned int time)
{
   SCIPdbgMsg("Starting control Var Iteration at t = %i, vector has %lu elements\n", time,  controlVariables_.size());
   controlVarIt_ = controlVariables_[time].begin();
}


bool SDproblemStructure::controlVarsLeft()
{
   return controlVarIt_ != controlVariables_[currentTime_].end();
}

bool SDproblemStructure::controlVarsLeft(unsigned int time)
{
   return controlVarIt_ != controlVariables_[time].end();
}

void SDproblemStructure::incrementControlVar() {
   ++controlVarIt_;
}

SCIP_VAR* SDproblemStructure::getControlVar() {
   return *controlVarIt_;
}

/* Iterate Control Variables At t */
void SDproblemStructure::startControlVarAtTIteration()
{
   controlVarAtTIt_ = controlVariablesAtT_[currentTime_].begin();
}

void SDproblemStructure::startControlVarAtTIteration(unsigned int time)
{
   controlVarAtTIt_ = controlVariablesAtT_[time].begin();
}

bool SDproblemStructure::controlVarsAtTLeft()
{
   return controlVarAtTIt_ != controlVariablesAtT_[currentTime_].end();
}

bool SDproblemStructure::controlVarsAtTLeft(unsigned int time)
{
   return controlVarAtTIt_ != controlVariablesAtT_[time].end();
}

void SDproblemStructure::incrementControlVarAtT() {
   ++controlVarAtTIt_;
}

SCIP_VAR* SDproblemStructure::getControlVarAtT() {
   return *controlVarAtTIt_;
}


SCIP_VAR* SDproblemStructure::getNthsControlVar(unsigned int n)
{
   /* Iterate over vector */
   for(VarVecMap::iterator it = controlVariables_.begin(); it != controlVariables_.end(); ++it)
   {
      if (  n  + 1 <= (it->second).size()  )
         return (it->second)[n];
      else
         n = n - ((it->second).size());
   }
   return NULL;
}

SCIP_Bool SDproblemStructure::isControlVar(SCIP_VAR* var)
{
   /* Find entry in stateVariableTimes_ vector */
   int index(SCIPvarGetIndex(var));

   if (controlVariableTimes_.find(index) == controlVariableTimes_.end())
      return false;
   else
      return true;
}

/** Returns the first time in which the variable appears
 *  if var is no control variable, return -1 */
int SDproblemStructure::getControlVarTime(SCIP_VAR* var)
{
   /* Find entry in stateVariableTimes_ vector */
   int index(SCIPvarGetIndex(var));

   if (controlVariableTimes_.find(index) != controlVariableTimes_.end())
      return controlVariableTimes_[index];
   else
      return false;
}

SCIP_Bool SDproblemStructure::isStateVar(SCIP_VAR* var)
{
   /* Find entry in stateVariableTimes_ vector */
   int index(SCIPvarGetIndex(var));

   if (stateVariableTimes_.find(index) == stateVariableTimes_.end())
      return false;
   else
      return true;
}

/** Returns the first time in which the variable appears
 *  if var is no control variable, return -1 */
int SDproblemStructure::getStateVarTime(SCIP_VAR* var)
{
   /* Find entry in stateVariableTimes_ vector */
   int index(SCIPvarGetIndex(var));

   if (stateVariableTimes_.find(index) != stateVariableTimes_.end())
      return stateVariableTimes_[index];
   else
      return false;
}

void SDproblemStructure::startAlgebraicConsIteration()
{
   algebraicConsIt_= algebraic_[currentTime_].begin();
}

void SDproblemStructure::startAlgebraicConsIteration(unsigned int time)
{
   algebraicConsIt_= algebraic_[time].begin();
}

bool SDproblemStructure::algebraicConsLeft()
{
   return algebraicConsIt_ != algebraic_[currentTime_].end();
}

bool SDproblemStructure::algebraicConsLeft(unsigned int time)
{
   return algebraicConsIt_ != algebraic_[time].end();
}

void SDproblemStructure::incrementAlgebraicCons() {
   ++algebraicConsIt_;
}

SCIP_CONS* SDproblemStructure::getAlgebraicCons() {
   return *algebraicConsIt_;
}

void SDproblemStructure::startCutIteration()
{
   cutsIt_= propCuts_[currentTime_].begin();
}

void SDproblemStructure::startCutIteration(unsigned int time)
{
   cutsIt_= propCuts_[time].begin();
}

bool SDproblemStructure::cutsLeft()
{
   return cutsIt_ != propCuts_[currentTime_].end();
}

bool SDproblemStructure::cutsLeft(unsigned int time)
{
   return cutsIt_ != propCuts_[time].end();
}

void SDproblemStructure::incrementCut() {
   ++cutsIt_;
}

SCIP_CONS* SDproblemStructure::getCut() {
   return *cutsIt_;
}

void SDproblemStructure::startLevelIteration()
{
   levelIt_ = algebraicConstraints_[currentTime_].begin();
}

void SDproblemStructure::startLevelIteration(unsigned int time)
{
   levelIt_ = algebraicConstraints_[time].begin();
}


bool SDproblemStructure::levelsLeft()
{
   return levelIt_ != algebraicConstraints_[currentTime_].end();
}

bool SDproblemStructure::levelsLeft(unsigned int time)
{
   return levelIt_ != algebraicConstraints_[time].end();
}


void SDproblemStructure::incrementLevel()
{
   ++levelIt_;
}

int SDproblemStructure::getCurrentLevel() {
   return levelIt_->first;
}

SDproblemStructureInterface::SD_CONS_TYPE SDproblemStructure::getCurrentLevelType() {
   return levelIt_->second.first;
}

void SDproblemStructure::startLevelConsIteration()
{
   levelConsIt_ = (levelIt_->second).second.begin();
}

bool SDproblemStructure::levelConsLeft()
{
   return levelConsIt_ != (levelIt_->second).second.end();
}

void SDproblemStructure::incrementLevelCons()
{
   ++levelConsIt_;
}

SCIP_CONS* SDproblemStructure::getCurrentLevelConsCons()
{
   return levelConsIt_->first;
}

SCIP_VAR* SDproblemStructure::getCurrentLevelConsVar()
{
   assert(levelConsIt_->second != NULL);
   return levelConsIt_->second;
}

bool SDproblemStructure::currentLevelConsHasVar()
{
   return levelConsIt_->second != NULL;
}

std::string SDproblemStructure::implode( const std::string &glue, const std::vector<std::string> &pieces )
{
    std::string a;
    int leng=pieces.size();
    for(int i=0; i<leng; i++)
    {
        a+= pieces[i];
        if (  i < (leng-1) )
            a+= glue;
    }
    return a;
}

std::string SDproblemStructure::getStateVarList()
{
   SCIPdbgMsg("getting statevarlist\n");
   return implode(std::string(", "),stateVarNames_);
}


} /* namespace sdscip */


