/*
 * ODEintegrator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef ODEINTEGRATOR_H_
#define ODEINTEGRATOR_H_

#include "ProbDataSD.h"
//#include "PointRateEvaluatorInterface.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "Vector.h"
#include <string>
#include "sdscip.h"

namespace sdscip
{

class ODEintegrator
{

public:

   ODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls);
   virtual ~ODEintegrator() = default;
   void setXdots(std::vector<SCIP_EXPR*> xDot);
   SCIP_Real getT();
   SCIP* getScip();

   void printVec(std::vector<double> vec, std::string message);
   void printXdot();

   int getNStates();
   int getNControls();
   int getNAlgebraic();

   //* Just for testing */
   void setNStates(int states);


protected:
   SCIP* scip_;
   int nStates_;
   int nControls_;
   int nAlgebraic_;
   SCIP_Real dt_;
   int nIntermediateSteps_;
   SCIP_Real dtIntermediate_;
   SCIP_Real t_;
   std::string discretization_;
   sdo::ButcherTableau tableau_;

};
}
#endif /* ODEINTEGRATOR_H_ */
