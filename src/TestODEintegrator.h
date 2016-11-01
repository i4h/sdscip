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
#include "BaseTest.h"

namespace sdscip
{

class TestODEintegrator : public BaseTest
{
public:
   TestODEintegrator(SCIP* scip);
   virtual ~TestODEintegrator();

   std::ostream& toString(std::ostream& strm) const;

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

   void createVar(SCIP_VAR* &var, const char* name , SCIP_Real lb, SCIP_Real ub, SCIP_Real obj, SCIP_VARTYPE vartype);
   std::vector<SCIP_EXPR*> getXdotPredatorPrey();


private:
   /* Private scip to hold memory for testing expressions */
   SCIP* subscip_;

   /* Vars to be released in destructor */
   std::vector<SCIP_VAR*> subscipVars_;

   /* Expressions to be freed in destructor */
   std::vector<SCIP_EXPR*> subscipExpressions_;

};

}

#endif /* TESTODEINTEGRATOR_H_ */
