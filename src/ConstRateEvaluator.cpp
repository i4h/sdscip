/*
 * ConstRateEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#include "ConstRateEvaluator.h"
using namespace ctrl;


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

std::string ConstRateEvaluator::getName()
{
   return std::string("ConstRateEvaluator");
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
