/*
 * TestGeom.h
 *
 *  Created on: 05.02.2014
 *      Author: bzfvierh
 */

#ifndef SDSCIP_TESTGEOM_H_
#define SDSCIP_TESTGEOM_H_

#include <iostream>
#include <sstream>
#include "sdscip.h"
#include "Point.h"
#include "Vector.h"
#include "Orthant.h"
#include "OrthantList.h"
#include "HyperCube.h"
#include "HyperPlane.h"
#include "SDSCIPtest.h"



namespace sdscip {

class TestGeom : public SDSCIPtest
{
public:
   TestGeom(SCIP* _scip);
   virtual ~TestGeom();
   std::ostream& toString(std::ostream& strm) const;
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
   void testVectorLength();


private:
   double eps_;
   int ndim_;
};

}

#endif /* SDSCIP_TESTGEOM_H_ */
