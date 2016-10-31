/*
 * PointRateEvaluator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
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

   void setXdot(std::vector<SCIP_EXPR*> xDot);
   void setXdot(SCIP_EXPR** xDot);
   SCIP_EXPR* getXdot(int nDim);

   virtual std::string getName() = 0;

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
