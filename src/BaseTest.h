/*
 * BaseTest.h
 *
 *  Created on: 31.10.2016
 *      Author: bzfvierh
 */

#ifndef SDSCIP_BASETEST_H_
#define SDSCIP_BASETEST_H_

#include <iostream>
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
   BaseTest();
   virtual ~BaseTest();

   void test(bool t);

   int nSuccess_;
   int nError_;


};

} /* namespace sdscip */

#endif /* SDSCIP_BASETEST_H_ */
