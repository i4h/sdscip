/*
 * BaseTest.h
 *
 *  Created on: 31.10.2016
 *      Author: bzfvierh
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

   /** Output summary of tests */
   std::string summaryString() const;

private:

   int nError_;
   int nSuccess_;

   double epsilon_ = 1e-6;


};

} /* namespace I4H */

#endif /* SDSCIP_BASETEST_H_ */
