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

/**@file    HyperCube.h
 * @brief   @todo
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
