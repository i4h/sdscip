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

/**@file    ODEintegrator.cpp
 * @brief   Base class for ODE integrators
 * @author  Ingmar Vierhaus
 *
 */


#include "ODEintegrator.h"

namespace sdscip
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
   tableau_= sdscip::SDproblemStructureInterface::getButcherTableau(_scip, _discretization);
}


SCIP_Real ODEintegrator::getT()
{
   return t_;
}

void ODEintegrator::printVec(std::vector<double> vec, std::string message)
{
   sdscip::Vector temp(vec);
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

void ODEintegrator::setNStates(int states)
{
   nStates_ = states;
}

}
