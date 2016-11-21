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

/**@file    ConstRateEvaluator.cpp
 * @brief   Rate evaluator for constant rates (used for testing)
 * @author  Ingmar Vierhaus
 *
 */


#include "ConstRateEvaluator.h"
using namespace sdscip;


ConstRateEvaluator::ConstRateEvaluator(int nStates, SCIP* scip) :
   PointRateEvaluator(nStates, scip)
{}

ConstRateEvaluator::ConstRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip) :
   PointRateEvaluator(_nStates, _nAlgebraic, _nControls, _scip)
{}

ConstRateEvaluator::~ConstRateEvaluator()
{ }

void ConstRateEvaluator::setXdots(std::vector<SCIP_EXPR*> xDot)
{
   //SCIPwarningMessage("ConstRateEvaluator does not use derivative information, but setXdot was called\n");
}

SCIP_EXPR* ConstRateEvaluator::getXdot(int nDim)
{
   return NULL;
}

std::string ConstRateEvaluator::getName() const
{
   return std::string("ConstRateEvaluator");
}

PointRateEvaluator* ConstRateEvaluator::clone()
{
   return (new ConstRateEvaluator(*this));
}

std::vector<SCIP_Real> ConstRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states)
{
   std::vector<SCIP_Real> rates(nStates_, 1.0);
   for( int i = 1; i < nStates_; ++i)
   {
      rates[i] = rates[i] + i * 1.0;
   }
   return rates;

}
std::vector<SCIP_Real> ConstRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params)
{
   assert(params == NULL);
   return getRates(t, states);
}
