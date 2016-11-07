/*
 * TestSBratEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
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
