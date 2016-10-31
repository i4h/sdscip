/*
 * TestSBrateEvaluator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef TESTSBRATEVALUATOR_H_
#define TESTSBRATEVALUATOR_H_

#include "sdscip.h"
#include "SBrateEvaluator.h"

namespace sdscip
{

class TestSBrateEvaluator
{
public:
   TestSBrateEvaluator(SCIP* scip);
   virtual ~TestSBrateEvaluator();

   int getNsuccess();
   int getNerrors();

   void runAll();
   void runBoundTests();

private:
   SCIP* scip_;
   int nSuccess_;
   int nErrors_;
};

}

#endif /* TESTSBRATEVALUATOR_H_ */
