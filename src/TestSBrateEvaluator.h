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
#include "SDSCIPtest.h"

namespace sdscip
{

class TestSBrateEvaluator : public SDSCIPtest
{
public:
   TestSBrateEvaluator(SCIP* scip);
   virtual ~TestSBrateEvaluator();

   std::ostream& toString(std::ostream& strm) const;

   int getNsuccess();
   int getNerrors();

   void runAll();
   void runBoundTests();

private:
};

}

#endif /* TESTSBRATEVALUATOR_H_ */
