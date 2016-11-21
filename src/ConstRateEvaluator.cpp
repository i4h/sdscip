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
