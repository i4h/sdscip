/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 2012-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*    Copyright (C) 2016      Helmut-Schmidt University Hamburg              */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Lesser General Public License        */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.*/
/*                                                                           */
/*                                                                           */
/* Based on SCIP - Solving Constraint Integer Programs                       */
/* Copyright (C) 2002-2016 Zuse Institute Berlin                             */
/* SCIP is distributed under the terms of the SCIP Academic Licence,         */
/* see file COPYING in the SCIP distribution.                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    TestGeom.h
 * @brief   Test for geometry classes used in SD-SCIP
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
