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


