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

/**@file    BaseTest.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "BaseTest.h"

namespace I4H {

BaseTest::BaseTest() :
       nSuccess_(0)
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
   if ( (-epsilon_ <= a - b ) && ( a - b <= epsilon_) )
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      nError_++;
   }
}

void BaseTest::testStart()
{
   nExecutedTests_++;
}


std::string BaseTest::summaryString() const
{
   std::ostringstream oss;
   oss << "Executed " << nExecutedTests_ << " tests. ";
   oss << "Assertions: " << nSuccess_ << " passed, " << nError_ << " failed.";
   return oss.str();
}


} /* namespace I4H */
