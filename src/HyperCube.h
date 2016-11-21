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

/**@file    HyperCube.h
 * @brief   Hypercube class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#ifndef HYPERCUBE_H_
#define HYPERCUBE_H_

#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "Line.h"
#include "Orthant.h"
#include "OrthantList.h"
#include "HyperPlane.h"
#include "sdscip.h"


namespace sdscip {

class Line;
class Vector;
class Orthant;
class HyperPlane;
class OrthantList;

class HyperCube
{



public:
   typedef std::vector<std::pair<double,double> >  Extent ;
   typedef std::vector<std::pair<double,double> >::iterator  ExtentIterator ;
   typedef std::vector<std::pair<double,double> >::const_iterator  ConstExtentIterator ;
   typedef std::pair<sdscip::Orthant,std::vector<sdscip::Vector> > VertexIntersectionsPair;
   HyperCube();
   HyperCube(int _ndim);
   virtual ~HyperCube();
   std::string toString();
   void addDim(double, double);
   Extent::iterator beginIt();
   Extent::iterator endIt();
   ConstExtentIterator constBeginIt() const;
   ConstExtentIterator constEndIt() const;

   double getLowerExtent(int dim) const;
   double getHigherExtent(int dim) const;
   double getExtent(int dim) const;
   bool areExtentsFinite(SCIP* scip) const;
   double getNormalizationFactor() const;
   bool contains(sdscip::Vector vec);
   bool contains(SCIP* scip, sdscip::Vector vec);
   bool isOnFace(SCIP* scip, sdscip::Vector vec);
   bool isOnVertex(SCIP* scip, sdscip::Vector vec);
   VertexIntersectionsPair findSeveredVertex(const sdscip::HyperPlane * plane) const;
   double getSeparatedVolume(const sdscip::HyperPlane * plane) const;
   double getRelativeSeparatedVolume(const sdscip::HyperPlane * plane) const;
   double getVolume() const;
   sdscip::Vector getVertex(sdscip::Orthant orth) const;
   std::vector<sdscip::Line> getEdges(sdscip::Orthant orth) const;
   bool intersects(const sdscip::HyperPlane plane) const;


private:
   int ndim_;
   Extent extent_;
};

}

#endif /* HYPERCUBE_H_ */
