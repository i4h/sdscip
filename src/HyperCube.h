/*
 * HyperCube.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
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


namespace SDgeom {

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
   typedef std::pair<SDgeom::Orthant,std::vector<SDgeom::Vector> > VertexIntersectionsPair;
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
   bool contains(SDgeom::Vector vec);
   bool contains(SCIP* scip, SDgeom::Vector vec);
   bool isOnFace(SCIP* scip, SDgeom::Vector vec);
   bool isOnVertex(SCIP* scip, SDgeom::Vector vec);
   VertexIntersectionsPair findSeveredVertex(const SDgeom::HyperPlane * plane) const;
   double getSeparatedVolume(const SDgeom::HyperPlane * plane) const;
   double getRelativeSeparatedVolume(const SDgeom::HyperPlane * plane) const;
   double getVolume() const;
   SDgeom::Vector getVertex(SDgeom::Orthant orth) const;
   std::vector<SDgeom::Line> getEdges(SDgeom::Orthant orth) const;
   bool intersects(const SDgeom::HyperPlane plane) const;


private:
   int ndim_;
   Extent extent_;
};

}

#endif /* HYPERCUBE_H_ */
