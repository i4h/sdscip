/*
 * TestODEintegrator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef TESTODEINTEGRATOR_H_
#define TESTODEINTEGRATOR_H_

#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"

namespace ctrl
{

class TestODEintegrator
{
public:
   TestODEintegrator(SCIP* scip);
   virtual ~TestODEintegrator();

   int getNsuccess();
   int getNerrors();

   void runAll();
   void runSimTests();
   void runSBtests();

   void runConstRateEvaluatorTest();
   void runPredatorPreySimTest();
   void runPredatorPreySBsimTest();
   void runPredatorPreySimIntermediateStepsTest();
   void runPredatorPreySBcontrolTest();
   void runPredatorPreySBglobalBoundsTest();
   void runPredatorPreySBboundsTest();

   std::vector<std::string> getTestDiscretizations();

   std::vector<SCIP_EXPR*> getXdotPredatorPrey();


private:
   SCIP* scip_;
   SCIP* subscip_; /* Private scip to hold memory for testing expressions */
   int nSuccess_;
   int nErrors_;
};

}

#endif /* TESTODEINTEGRATOR_H_ */
