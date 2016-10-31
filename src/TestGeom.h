/*
 * TestGeom.h
 *
 *  Created on: 05.02.2014
 *      Author: bzfvierh
 */

#ifndef SDSCIP_TESTGEOM_H_
#define SDSCIP_TESTGEOM_H_

#include <iostream>
#include "sdscip.h"
#include "Point.h"
#include "Vector.h"
#include "Orthant.h"
#include "OrthantList.h"
#include "HyperCube.h"
#include "HyperPlane.h"
#include "BaseTest.h"



namespace sdscip {

class TestGeom : public sdscip::BaseTest
{
public:
   TestGeom(SCIP* _scip);
   virtual ~TestGeom();
   void runAll();
   void runCurrent();
   void testContains();
   void testIsOnFace();
   void testIsOnVertex();
   void testFindSeveredVertex();
   void testVectorOperators();
   void testIntersection();
   void testGetSeparatedVolume();
   void testHyperCubeIntersects();
   HyperCube unitCube() const;
   void test(bool t);
   void testEqual(double a, double b);
   void testVectorLength();


private:
   SCIP* scip_;
   int nSuccess_;
   double eps_;
   int ndim_;
};

}

#endif /* SDSCIP_TESTGEOM_H_ */
