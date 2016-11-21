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

/**@file    TestSBrateEvaluator.h
 * @brief   Test class for Scott, Barton rate evaluator
 * @author  Ingmar Vierhaus
 *
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
