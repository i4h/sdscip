/*
 * TestGeom.h
 *
 *  Created on: 05.02.2014
 *      Author: bzfvierh
 */

#ifndef TESTGEOM_H_
#define TESTGEOM_H_

#include <iostream>
#include "scip/scip.h"
#include "Point.h"
#include "Vector.h"
#include "Orthant.h"
#include "OrthantList.h"
#include "HyperCube.h"
#include "HyperPlane.h"



namespace SDgeom {


class TestGeom
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

#endif /* TESTGEOM_H_ */
