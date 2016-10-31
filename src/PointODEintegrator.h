/*
 * PointODEintegrator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef POINTODEINTEGRATOR_H_
#define POINTODEINTEGRATOR_H_

#include "ODEintegrator.h"
#include "ProbDataSD.h"
#include "PointRateEvaluator.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "Vector.h"
#include <string>
#include "sdscip.h"
#include <fstream>

namespace sdscip
{


class PointODEintegrator : public ODEintegrator
{
   friend class ReduceODEintegrator;
public:
   PointODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls, PointRateEvaluator::POINT_RATE_EVALUATOR_TYPE _rateEvalType);
   ~PointODEintegrator();

   PointRateEvaluator* rateEvaluator();

   std::vector<SCIP_Real> getStates();

   std::vector<SCIP_Real> getControls();
   SCIP_Real getState(int dim);
   SCIP_Real getAlgebraic(int varId);
   SCIP_Real getControl(int varId);
   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states);
   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states, std::vector<SCIP_Real> controls);

   void step();
   void step(SCIP_Real* startParams, SCIP_Real* endParams);

   /* Helpers */
   std::string toString();

   std::string statesToString();
   std::string algebraicToString();
   void writeStates(std::ofstream& outFile);
   std::string controlsToString();
   void setXdots(std::vector<SCIP_EXPR*> xDot);
   void printXdot();

   void computeAlgebraic(SCIP_Real* params);
   void setControls(const std::vector<SCIP_Interval>& controls);
   void setEndControls(const std::vector<SCIP_Interval>& endControls);

private:
/** First nStates_ items contain state var values,
   * following nControls items contain control values,
   * following nAlgebraic items contain space reserved
   * for the values of algebraic variables (are set by rateEvluator)
   * **/
   std::vector<SCIP_Real> varValues_;
   SCIP_Real tAlgebraic_;

   PointRateEvaluator* rateEvaluator_;
   std::vector<SCIP_Real> endControls_; /* To be used in the integration step */
};
}
#endif /* POINTODEINTEGRATOR_H_ */
