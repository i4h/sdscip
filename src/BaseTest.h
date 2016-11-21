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

/**@file    BaseTest.h
 * @brief   Base class for unit tests
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDSCIP_BASETEST_H_
#define SDSCIP_BASETEST_H_

#include <iostream>
#include <sstream>


namespace I4H {

class BaseTest
{
public:
   BaseTest();
   virtual ~BaseTest();

   /** Test that expression evaluates to true */
   virtual void test(bool t);

   /** Test that a and b are equal */
   virtual void testEqual(double a, double b);

   /** Run all tests */
   virtual void runAll() = 0;

   /* Successful checks while executing tests */
   int nSuccess_;

   /* Number of detected errors executing tests */
   int nError_;

   /* Number of executed tests */
   int nExecutedTests_;

   friend std::ostream& operator << (std::ostream& os, const BaseTest& derivedTest) {
     return derivedTest.toString(os); // polymorphic print via reference
   }

   /** Pure virtual toString method  */
   virtual std::ostream& toString(std::ostream&) const = 0;

   /* To be called by every test */
   void testStart();

   /** Output summary of tests */
   std::string summaryString() const;

private:

   double epsilon_ = 1e-6;


};

} /* namespace I4H */

#endif /* SDSCIP_BASETEST_H_ */
