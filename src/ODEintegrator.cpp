#define SCIP_DBG

/*
 * ODEintegrator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#include "ODEintegrator.h"

namespace ctrl
{

ODEintegrator::ODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls) :
   scip_(_scip)
   ,nStates_(_nStates)
   ,nControls_(_nControls)
   ,nAlgebraic_(_nAlgebraic)
   ,dt_(_dt)
   ,nIntermediateSteps_(_nIntermediateSteps)
   ,dtIntermediate_(_dt / _nIntermediateSteps)
   ,t_(0)
   ,discretization_(_discretization)
{
   /* Get butcher tableau for selected discretization scheme */
   tableau_= ctrl::SDproblemStructureInterface::getButcherTableau(_scip, _discretization);
}

ODEintegrator::~ODEintegrator()
{
   // TODO Auto-generated destructor stub
}




SCIP_Real ODEintegrator::getT()
{
   return t_;
}

void ODEintegrator::printVec(std::vector<double> vec, std::string message)
{
   SDgeom::Vector temp(vec);
   SCIPdbgMsg("%s = %s\n",message.c_str(), temp.toString().c_str());
}

SCIP* ODEintegrator::getScip()
{
   return scip_;
}

int ODEintegrator::getNStates()
{
   return nStates_;
}
int ODEintegrator::getNControls()
{
   return nControls_;
}

int ODEintegrator::getNAlgebraic()
{
   return nControls_;
}

}
