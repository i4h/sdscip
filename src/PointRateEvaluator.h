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

/**@file    PointRateEvaluator.h
 * @brief   Rate evaluator for scalar rates
 * @author  Ingmar Vierhaus
 *
 */


#ifndef POINTRATEEVALUATOR_H_
#define POINTRATEEVALUATOR_H_

#include <string>
#include <vector>
#include "sdscip.h"
#include "BoundMapHelpers.cpp"

namespace sdscip
{

class ODEintegrator;

class PointRateEvaluator
{
   friend class SBrateEvaluator;
   friend class SimRateEvaluator;
public:
   enum POINT_RATE_EVALUATOR_TYPE
   {
      RATE_EVALUATOR_CONST = 0
      ,RATE_EVALUATOR_SIM = 1
   };

   //RateEvaluator();
   PointRateEvaluator(int _nStates, SCIP* scip);
   PointRateEvaluator(int _nStates, int _nAlgebraic, SCIP* _scip);
   PointRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~PointRateEvaluator() {};

   void setXdot(std::vector<SCIP_EXPR*> &xDot);
   void setXdot(SCIP_EXPR** xDot);
   SCIP_EXPR* getXdot(int nDim);

   virtual std::string getName()  const;

   /* Pure virtual clone method for polymorphic descendant classes */
   virtual PointRateEvaluator* clone() = 0;

   virtual std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> varValues) = 0;
   virtual std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> varValues, SCIP_Real* params) = 0;
   void computeAlgebraic(std::vector<SCIP_Real> &varValues, SCIP_Real * startParams);


   void printXdot();

   void printXdotAlgebraic();
   void setAlgebraicExpressions(SCIP_EXPR** xDot);
   SCIP_EXPR* getXdotAlgebraic(int nDim);

   int nStates_;
   int nAlgebraic_;
   int nControls_;

private:

   SCIP* scip_;
   SCIP_EXPR** xDot_;
   SCIP_EXPR** algebraicExpressions_;

};

}

#endif /* POINTRATEEVALUATOR_H_ */
