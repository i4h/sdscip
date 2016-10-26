//#define SCIP_DBG
/*
 * SDproblemStructureInterface.cpp
 *
 *  Created on: 05.02.2015
 *      Author: bzfvierh
 */


#include "SDproblemStructureInterface.h"

//TODO: When everything is implemented, this can be removed

namespace ctrl {




/* Empty implementations to let the user know what is missing */

SCIP_VAR* SDproblemStructureInterface::getCurrentLevelConsVar()
{
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_VAR* SDproblemStructureInterface::getCurrentLevelConsOrigVar()
{
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

int SDproblemStructureInterface::getVarId(int varIndex)
{
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

int SDproblemStructureInterface::startTimeIteration(int time)
{
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

void SDproblemStructureInterface::startControlVarAtTIteration()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
}

void SDproblemStructureInterface::startControlVarAtTIteration(unsigned int time)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
}

bool SDproblemStructureInterface::controlVarsAtTLeft()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return false;
}

bool SDproblemStructureInterface::controlVarsAtTLeft(unsigned int time)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

void SDproblemStructureInterface::incrementControlVarAtT()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
}

SCIP_VAR* SDproblemStructureInterface::getControlVarAtT()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_VAR* SDproblemStructureInterface::getControlVarAtTOrig()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}


SCIP_VAR* SDproblemStructureInterface::getNthsControlVar(unsigned int n)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* var(NULL);
   return var;
}

SCIP_Bool SDproblemStructureInterface::isControlVar(SCIP_VAR* var) {
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return false;
}

/** Returns the first time in which the variable appears
 *  if var is no control variable returns -1 */
int SDproblemStructureInterface::getControlVarBeginTime(SCIP_VAR* var) {
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return -1;
}

SCIP_Bool SDproblemStructureInterface::isStateVar(SCIP_VAR* var) {
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return false;
}

int SDproblemStructureInterface::getNParamsPerTime() {
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

/** Returns the first time in which the variable appears
 *  if var is no control variable returns -1 */
int SDproblemStructureInterface::getStateVarTime(SCIP_VAR* var) {
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return -1;
}

std::vector<std::string> SDproblemStructureInterface::getStateVarNames()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::vector<std::string>();
}

std::vector<std::string> SDproblemStructureInterface::getControlVarNames()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::vector<std::string>();
}

std::vector<std::string> SDproblemStructureInterface::getAlgebraicVarNames()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::vector<std::string>();
}

unsigned int SDproblemStructureInterface::getNStates()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

unsigned int SDproblemStructureInterface::getNControls()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

unsigned int SDproblemStructureInterface::getNAlgebraic()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

std::pair<unsigned int, unsigned int> SDproblemStructureInterface::getVarTimes(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::pair<unsigned int, unsigned int>(0,0);
}
SCIP_VAR* SDproblemStructureInterface::getNext(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* returnVar(NULL);
   return returnVar;
}
SCIP_VAR* SDproblemStructureInterface::getPrevious(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* returnVar(NULL);
   return returnVar;
}
unsigned int SDproblemStructureInterface::getConsTime(SCIP_VAR* var)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

void SDproblemStructureInterface::startStateVarIteration()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
}

bool SDproblemStructureInterface::stateVarsLeft()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return false;
}

void SDproblemStructureInterface::incrementStateVar()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
}

SCIP_VAR* SDproblemStructureInterface::getCurrentStateVar()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* var = NULL;
   return var;
}

SCIP_VAR* SDproblemStructureInterface::getCurrentStateVarOrig()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   SCIP_VAR* var = NULL;
   return var;
}

int SDproblemStructureInterface::getCurrentStateVarId()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

unsigned int SDproblemStructureInterface::getCurrentTime()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0;
}

SCIP_EXPR** SDproblemStructureInterface::getXdot()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_EXPR** SDproblemStructureInterface::getXdotAlgebraic()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_EXPR** SDproblemStructureInterface::getAlgebraicExpressions()
{
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   exit(1);
}

SCIP_Real* SDproblemStructureInterface::getXdotParams()
{
   return getXdotParams((int) getCurrentTime());
}

SCIP_Real* SDproblemStructureInterface::getXdotParams(int time)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_Real* SDproblemStructureInterface::getXdotParams(SCIP_Real time)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return NULL;
}

SCIP_Real SDproblemStructureInterface::getTinit()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0.0;
}

SCIP_Real SDproblemStructureInterface::getTfinal()
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return 0.0;
}


/* Helpers */

std::string SDproblemStructureInterface::implode( const std::string &glue, const std::vector<std::string> &pieces )
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

/* Working implementations using pure virtual interface functions */

sdo::ButcherTableau SDproblemStructureInterface::getButcherTableau(SCIP* scip, const char* discretization)
{
   std::string discretizationstr(discretization);
   return getButcherTableau(scip, discretizationstr);
}

sdo::ButcherTableau SDproblemStructureInterface::getButcherTableau(SCIP* scip, std::string discretization)
{
   sdo::ButcherTableau tableau;

   if( discretization == "rk2" )
   {
      tableau.setTableau(sdo::ButcherTableau::RUNGE_KUTTA_2);
   }
   else if( discretization == "rk3" )
   {
      SCIPwarningMessage(scip, "Runge kutta 3 method currently uses wrong parameters in last intermediate step. Using Heun's order 3 method instead\n");
//       tableau.setTableau(sdo::ButcherTableau::RUNGE_KUTTA_3);
      tableau.setTableau(sdo::ButcherTableau::HEUN);
   }
   else if( discretization == "heun" )
   {
      tableau.setTableau(sdo::ButcherTableau::HEUN);
   }
   else if( discretization == "rk4" )
   {
      SCIPwarningMessage(scip, "Runge kutta 4 method uses wrong parameters in last intermediate step\n");
      tableau.setTableau(sdo::ButcherTableau::RUNGE_KUTTA_4);
   }
   else if( discretization == "imid2" )
   {
      tableau.setTableau(sdo::ButcherTableau::IMPLICIT_MIDPOINT_2);
   }
   else if( discretization == "gl4" )
   {
      tableau.setTableau(sdo::ButcherTableau::GAUSS_LEGENDRE_4);
   }
   else if( discretization == "euler" )
   {
      tableau.setTableau(sdo::ButcherTableau::EULER);
   }
   else
   {
      SCIPerrorMessage("Unknown value for discretization method: '%s'. Using 'rk2' instead\n", discretization.c_str());
      tableau.setTableau(sdo::ButcherTableau::RUNGE_KUTTA_2);
   }
   return tableau;
}
bool SDproblemStructureInterface::isTranformed() const
{
   return true;
}
SCIP_RETCODE SDproblemStructureInterface::setIsTransformed(bool _isReformulated)
{
   return SCIP_OKAY;
}

std::string SDproblemStructureInterface::getStateVarList()
{
   return implode(std::string(", "),this->getStateVarNames());
}

std::string SDproblemStructureInterface::getControlVarList()
{
   return implode(std::string(", "),this->getControlVarNames());
}

std::string SDproblemStructureInterface::getAlgebraicVarList()
{
   return implode(std::string(", "),this->getAlgebraicVarNames());
}


std::string SDproblemStructureInterface::getVarBasename(SCIP_VAR* var)
{
   /* Get basename */
   boost::cmatch matches;
   if (boost::regex_match(SCIPvarGetName(var), matches, getVarRegex()) )
   {
      std::string varName(matches[1].first,matches[1].second);
      return varName;
   }
   else
   {
      SCIPerrorMessage("unable to parse variable %s\n", SCIPvarGetName(var));
      SCIPABORT();
      return std::string();
   }
}

std::vector<SCIP_Interval> SDproblemStructureInterface::getStateBounds()
{
   std::vector<SCIP_Interval> stateBounds;
   for (startStateVarIteration(); stateVarsLeft();incrementStateVar())
   {
      SCIP_VAR* var = getCurrentStateVar();
      SCIP_Interval interval;
      interval.inf = SCIPvarGetLbLocal(var);
      interval.sup = SCIPvarGetUbLocal(var);
      stateBounds.push_back(interval);
   }
   return stateBounds;
}

SDproblemStructureInterface::BoundMap SDproblemStructureInterface::getStateBoundsMap()
{
   SDproblemStructureInterface::BoundMap stateBounds;
   for (startStateVarIteration(); stateVarsLeft();incrementStateVar())
   {
      int varId = getCurrentStateVarId();
      SCIP_VAR* var = getCurrentStateVar();
      SCIP_Real lb = SCIPvarGetLbLocal(var);
      SCIP_Real ub = SCIPvarGetUbLocal(var);
      if (!SCIPisInfinity(scip_, -1.0*lb))
         stateBounds[BoundKey(varId, SCIP_BOUNDTYPE_LOWER)] = lb;
      if (!SCIPisInfinity(scip_, ub))
         stateBounds[BoundKey(varId, SCIP_BOUNDTYPE_UPPER)] = ub;
   }
   return stateBounds;
}

std::vector<SCIP_Interval> SDproblemStructureInterface::getControlBounds()
{
   std::vector<SCIP_Interval> controlBounds;
   for (startControlVarAtTIteration(); controlVarsAtTLeft(); incrementControlVarAtT())
   {
      SCIP_VAR* var = getControlVarAtT();
      SCIP_Interval interval;
      interval.inf = SCIPvarGetLbLocal(var);
      interval.sup = SCIPvarGetUbLocal(var);
      controlBounds.push_back(interval);
   }
   return controlBounds;
}

std::vector<SCIP_Interval> SDproblemStructureInterface::getMaxControlBounds(const std::vector<SCIP_Interval>& oldControlBounds)
{
   std::vector<SCIP_Interval> maxControlBounds;
   auto oldBoundsIterator = oldControlBounds.begin();
   for (startControlVarAtTIteration(); controlVarsAtTLeft(); incrementControlVarAtT())
   {
      assert(oldBoundsIterator != oldControlBounds.end());
      SCIP_VAR* var = getControlVarAtT();
      SCIPdbgMsg("checking control var %s\n",SCIPvarGetName(var));
      SCIP_Interval interval;
      interval.inf = std::min(oldBoundsIterator->inf,SCIPvarGetLbLocal(var));
      SCIPdbgMsg("oldBounds infimum is %f, current control var infimum is %f, new bound is %f\n", oldBoundsIterator->inf,SCIPvarGetLbLocal(var), interval.inf);
      interval.sup = std::max(oldBoundsIterator->sup, SCIPvarGetUbLocal(var));
      SCIPdbgMsg("oldBounds supimum is %f, current control var supimum is %f, new bound is %f\n", oldBoundsIterator->sup,SCIPvarGetLbLocal(var), interval.sup);
      maxControlBounds.push_back(interval);
      ++oldBoundsIterator;
   }
   return maxControlBounds;
}

std::vector<SCIP_Interval> SDproblemStructureInterface::getMaxStateBounds(const std::vector<SCIP_Interval>& oldStateBounds)
{
   std::vector<SCIP_Interval> maxStateBounds;
   auto oldBoundsIterator = oldStateBounds.begin();
   for (startStateVarIteration(); stateVarsLeft(); incrementStateVar())
   {
      assert(oldBoundsIterator != oldStateBounds.end());
      SCIP_VAR* var = getCurrentStateVar();
      SCIPdbgMsg("checking state var %s\n",SCIPvarGetName(var));
      SCIP_Interval interval;
      interval.inf = std::min(oldBoundsIterator->inf,SCIPvarGetLbLocal(var));
      SCIPdbgMsg("oldBounds infimum is %f, current state var infimum is %f, new bound is %f\n", oldBoundsIterator->inf,SCIPvarGetLbLocal(var), interval.inf);
      interval.sup = std::max(oldBoundsIterator->sup, SCIPvarGetUbLocal(var));
      SCIPdbgMsg("oldBounds supimum is %f, current state var supimum is %f, new bound is %f\n", oldBoundsIterator->sup,SCIPvarGetLbLocal(var), interval.sup);
      maxStateBounds.push_back(interval);
      ++oldBoundsIterator;
   }
   return maxStateBounds;
}

SDproblemStructureInterface::BoundMap SDproblemStructureInterface::getMaxStateBoundsBoundMap(const std::vector<SCIP_Interval>& oldStateBounds)
{
   SDproblemStructureInterface::BoundMap maxStateBounds;
   auto oldBoundsIterator = oldStateBounds.begin();
   int stateId = 0;
   for (startStateVarIteration(); stateVarsLeft(); incrementStateVar())
   {
      assert(oldBoundsIterator != oldStateBounds.end());
      SCIP_VAR* var = getCurrentStateVar();
      SCIPdbgMsg("checking state var %s\n",SCIPvarGetName(var));
      /* Potential lower bound */
      SCIPdbgMsg("oldbound is %f, current local bound is %f\n", oldBoundsIterator->inf, SCIPvarGetLbLocal(var));
      SCIP_Real lb = std::min(oldBoundsIterator->inf,SCIPvarGetLbLocal(var));
      if (!SCIPisInfinity(scip_, -1.0*lb))
         maxStateBounds[SDproblemStructureInterface::BoundKey(stateId, SCIP_BOUNDTYPE_LOWER)] = lb;

      /* Potential upper bound */

      SCIPdbgMsg("oldbound is %f, current local bound is %f\n", oldBoundsIterator->sup, SCIPvarGetUbLocal(var));
      SCIP_Real ub = std::max(oldBoundsIterator->sup, SCIPvarGetUbLocal(var));
      if (!SCIPisInfinity(scip_, ub))
         maxStateBounds[SDproblemStructureInterface::BoundKey(stateId, SCIP_BOUNDTYPE_UPPER)] = ub;

      ++oldBoundsIterator;
      ++stateId;
   }
   return maxStateBounds;
}

std::string SDproblemStructureInterface::getVarName(unsigned int varId) {
   assert(varId < getNStates() + getNControls()+ getNAlgebraic());

   if (varId < getNStates())
      return getStateVarNames()[varId];
   else if( varId < getNStates() + getNControls())
      return getControlVarNames()[varId - getNStates()];
   else
      return getAlgebraicVarNames()[varId - getNStates() - getNControls()];

}

} /* namespace ctrl */
