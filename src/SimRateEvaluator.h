/*
 * SimRateEvaluator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef SDSCIP_SIMRATEEVALUATOR_H_
#define SDSCIP_SIMRATEEVALUATOR_H_

#include "PointRateEvaluator.h"
#include "BoundMapHelpers.cpp"
#include <string>

namespace ctrl{

class SimRateEvaluator: public PointRateEvaluator
{
public:
   SimRateEvaluator(int _nStates, SCIP* scip);
   SimRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~SimRateEvaluator();

   SCIP_EXPR* getXdot(int nDim);

   std::string getName();

   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states);
   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params);

private:

};

}

#endif /* SDSCIP_SIMRATEEVALUATOR_H_ */
