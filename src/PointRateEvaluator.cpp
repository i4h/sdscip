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

/**@file    PointRateEvaluator.cpp
 * @brief   ODE integrator class for scalar ODEs
 * @author  Ingmar Vierhaus
 *
 */


#include "PointRateEvaluator.h"


namespace sdscip {

PointRateEvaluator::PointRateEvaluator(int _nStates, SCIP* _scip) :
   PointRateEvaluator( _nStates, 0, 0, _scip)
{
   assert(false);
}

PointRateEvaluator::PointRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip) :
   nStates_(_nStates)
   ,nAlgebraic_(_nAlgebraic)
   ,nControls_(_nControls)
   ,scip_(_scip)
   ,xDot_(NULL)
   ,algebraicExpressions_(NULL)
{ }


void PointRateEvaluator::setXdot(std::vector<SCIP_EXPR*> &xDot)
{
   SCIPdbgMsg("got xDot with %lu elements\n",xDot.size());
   xDot_ = &xDot[0];
}

void PointRateEvaluator::setXdot(SCIP_EXPR** xDot)
{
   SCIPdbgMsg("setting xdots\n");
   xDot_ = xDot;
}

std::string PointRateEvaluator::getName() const
{
   return std::string("PointRateEvaluator");
}

SCIP_EXPR* PointRateEvaluator::getXdot(int nDim)
{
   return xDot_[nDim];
}

void PointRateEvaluator::printXdot()
{
   SCIPdbgMsg("printing xDot\n");
   for( int i = 0; i < nStates_; ++i)
   {
      SCIPinfoMessage(scip_, NULL, "\\dot x(%i): ", i);
      SCIPexprPrint(xDot_[i], SCIPgetMessagehdlr(scip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(scip_, NULL, "\n");
   }
}

void PointRateEvaluator::setAlgebraicExpressions(SCIP_EXPR** algebraicExpressions)
{
   SCIPdbgMsg("setting xdotAlgebraics\n");
   algebraicExpressions_ = algebraicExpressions;
}

SCIP_EXPR* PointRateEvaluator::getXdotAlgebraic(int nDim)
{
   return algebraicExpressions_[nDim];
}

void PointRateEvaluator::printXdotAlgebraic()
{
   SCIPdbgMsg("Algebraic Expressions:\n");
   for( int i = 0 ; i < nAlgebraic_ ; ++i)
   {
      SCIPdbgMsg("i = %i\n",i);
      SCIPinfoMessage(scip_, NULL, "y(%i): ",i);
      SCIPexprPrint(algebraicExpressions_[i], SCIPgetMessagehdlr(scip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(scip_, NULL, "\n");
   }

   SCIPdbgMsg("State Expressions\n");
   for( int i = 0; i < nStates_  ; ++i)
   {
      SCIPinfoMessage(scip_, NULL, "\\dot x(%i): ",i);
      SCIPexprPrint(xDot_[i], SCIPgetMessagehdlr(scip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(scip_, NULL, "\n");
   }
}

void PointRateEvaluator::computeAlgebraic(std::vector<SCIP_Real> &varValues, SCIP_Real * params)
{
   SCIPdbgMsg("computingAlgebraic, varValues: %s\n",valVecToString(varValues).c_str());
   /* Compute varValues[i >= nStates_ + nControls_] using algebraic expressions */
   for( int i = 0; i < nAlgebraic_; ++i)
   {
      SCIPdbgMsg("evaluating algebraicExpressions[%i]\n", i);
      SCIP_Real result;
      SCIPexprEval(algebraicExpressions_[i], &varValues[0], params, &result);
      SCIPdbgMsg("result is %g\n", result);
      varValues[nStates_ + nControls_ + i] = result;

   }
   SCIPdbgMsg("done with algebraic, varValues: %s\n",valVecToString(varValues).c_str());
}

}




