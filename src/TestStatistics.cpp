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

/**@file    TestStatistics.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "TestStatistics.h"

namespace I4H
{


TestStatistics::TestStatistics() :
   BaseTest()
{ }

TestStatistics::~TestStatistics()
{
}

std::ostream& TestStatistics::toString(std::ostream& strm) const {
  return strm << "TestStatistics";
}


int TestStatistics::getNsuccess()
{
   return nSuccess_;
}

int TestStatistics::getNerror()
{
   return nError_;
}

void TestStatistics::runAll()
{
   testMean();
}

void TestStatistics::testMean()
{
   testStart();

   I4H::Statistics stats;

   double val(0);
   for (int i = 0; i < 10001; i++)
   {
      stats.addVal(val);
      val += 0.0001;
   }
   testEqual(stats.mean(), 0.5);
   testEqual(stats.max(), 1);
   testEqual(stats.min(), 0);
}



}
