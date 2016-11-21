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

/**@file    TestGeom.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
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
