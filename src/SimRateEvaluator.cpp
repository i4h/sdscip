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

/**@file    SimRateEvaluator.cpp
 * @brief   Rate evaluator for solution of ODEs without degrees of freedom
 * @author  Ingmar Vierhaus
 *
 */


#include "SimRateEvaluator.h"

using namespace sdscip;


SimRateEvaluator::SimRateEvaluator(int nStates, SCIP* scip) :
   PointRateEvaluator(nStates, scip)
{}

SimRateEvaluator::SimRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip) :
   PointRateEvaluator(_nStates, _nAlgebraic, _nControls, _scip)
{}


SimRateEvaluator::~SimRateEvaluator()
{ }

std::string SimRateEvaluator::getName() const
{
   return std::string("SimRateEvaluator");
}

PointRateEvaluator* SimRateEvaluator::clone()
{
   return (new SimRateEvaluator(*this));
}


std::vector<SCIP_Real> SimRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states)
{
   return getRates(t, states, NULL);
}

std::vector<SCIP_Real> SimRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> varValues, SCIP_Real* params )
{
   computeAlgebraic(varValues, params);

   SCIPdbgMsg("done computing algebraic\n");
   std::vector<SCIP_Real> rates(nStates_);
   for( int i = 0; i < nStates_; ++i)
   {
      SCIPexprEval(xDot_[i], &varValues[0], params, &rates[i]);
   }

   SCIPdbgMsg("done with states, varValues: %s\n",valVecToString(varValues).c_str());
   SCIPdbgMsg("cmputed rates: %s\n", valVecToString(rates).c_str());
   return rates;

}


