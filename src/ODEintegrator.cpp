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
