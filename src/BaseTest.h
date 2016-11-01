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
#include "sdscip.h"
//#include "Point.h"
//#include "Vector.h"
//#include "Orthant.h"
//#include "OrthantList.h"
//#include "HyperCube.h"
//#include "HyperPlane.h"


namespace sdscip {

class BaseTest
{
public:
   BaseTest(SCIP* _scip);
   virtual ~BaseTest();

   /** Test that expression evaluates to true */
   void test(bool t);

   /** Test that a and b are equal */
   void testEqual(double a, double b);

   /** Run all tests */
   virtual void runAll() = 0;

   /** Pointer to a SCIP instance, needed for memory management,
     * floating point comparisons, etc.
     * */
   SCIP* scip_;

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


};

} /* namespace sdscip */

#endif /* SDSCIP_BASETEST_H_ */
