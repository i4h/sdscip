/*
 * SimRateEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
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

std::string SimRateEvaluator::getName()
{
   return std::string("SimRateEvaluator");
}

std::vector<SCIP_Real> SimRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states)
{
   return getRates(t, states, NULL);
}

std::vector<SCIP_Real> SimRateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> varValues, SCIP_Real* params )
{
   computeAlgebraic(varValues, params);

   std::vector<SCIP_Real> rates(nStates_);
   for( int i = 0; i < nStates_; ++i)
   {
      SCIPexprEval(xDot_[i], &varValues[0], params, &rates[i]);
   }

   SCIPdbgMsg("done with states, varValues: %s\n",valVecToString(varValues).c_str());
   return rates;

}


