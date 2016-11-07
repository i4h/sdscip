/*
 * BaseTest.cpp
 *
 *  Created on: 31.10.2016
 *      Author: bzfvierh
 */

#include "BaseTest.h"

namespace I4H {

BaseTest::BaseTest() :
      ,nSuccess_(0)
      ,nError_(0)
      ,nExecutedTests_(0)
{ }

BaseTest::~BaseTest() {}

void BaseTest::test(bool t)
{
   if (t)
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      nError_++;
   }
}

void BaseTest::testEqual(double a, double b)
{
   if (-epsilon_ <= a -b <= epsilon_)
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      nError_++;
   }
}

std::string BaseTest::summaryString() const
{
   std::ostringstream oss;
   oss << "Executed " << nExecutedTests_ << " tests " << std::endl;
   oss << "Assertions passed: " << nSuccess_ << ", Asserts failed : " << nError_;
   return oss.str();
}


} /* namespace I4H */
