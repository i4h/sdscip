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

/**@file    TestODEintegrator.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TESTODEINTEGRATOR_H_
#define TESTODEINTEGRATOR_H_

#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"
#include "SDSCIPtest.h"

namespace sdscip
{

class TestODEintegrator : public SDSCIPtest
{
public:
   TestODEintegrator(SCIP* scip);
   virtual ~TestODEintegrator();

   std::ostream& toString(std::ostream& strm) const;

   int getNsuccess();
   int getNerrors();

   void runAll();

   /* sim tests */
   void runSimTests();
   void runConstRateEvaluatorTest();
   void runPredatorPreySimTest();
   void runPredatorPreySimIntermediateStepsTest();

   /* sb tests */
   void runSBtests();
   void runPredatorPreySBsimTest();
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
