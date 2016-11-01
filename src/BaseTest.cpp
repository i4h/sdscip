#define SCIP_DBG
/*
 * BaseTest.cpp
 *
 *  Created on: 31.10.2016
 *      Author: bzfvierh
 */

#include "BaseTest.h"

namespace sdscip {

BaseTest::BaseTest(SCIP* _scip) :
      scip_(_scip)
      ,nSuccess_(0)
      ,nError_(0)
      ,nExecutedTests_(0)
{
}


BaseTest::~BaseTest() {}

void BaseTest::test(bool t)
{
   if (t)
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      assert(false);
   }
}

void BaseTest::testEqual(double a, double b)
{
   // std::cout << "testing equality of " << a << " and " << b << std::endl;
   if (SCIPisEQ(scip_,a,b))
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      assert(false);
   }
}

std::string BaseTest::summaryString() const
{
   std::ostringstream oss;
   oss << "Executed " << nExecutedTests_ << " tests " << std::endl;
   oss << "Asserts passed: " << nSuccess_ << ", Asserts failed : " << nError_;
   return oss.str();
}


} /* namespace sdscip */
