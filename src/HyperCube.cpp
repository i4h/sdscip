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

/**@file    HyperCube.cpp
 * @brief   Hypercube class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#include "HyperCube.h"
#include <cmath>

namespace sdscip {

HyperCube::HyperCube() :
   ndim_(0)
{ }

HyperCube::HyperCube(int _ndim) :
   ndim_(_ndim)
{
   for (int i = 0; i < ndim_; ++i)
      extent_.push_back(std::pair<double,double>(0,0));
}

HyperCube::~HyperCube()
{
   // TODO Auto-generated destructor stub
}

std::string HyperCube::toString() {
   std::ostringstream o;
   o << ndim_ << "-dim Hypercube:" << std::endl;
   for (Extent::iterator it = this->beginIt(); it != this->endIt(); ++it) {
      o << it->first << std::string(", ") << it->second << std::endl;
   }
   return o.str();
}

HyperCube::Extent::iterator HyperCube::beginIt() {
   return extent_.begin();
}
HyperCube::Extent::iterator HyperCube::endIt() {
   return extent_.end();
}

HyperCube::ConstExtentIterator HyperCube::constBeginIt() const {
   return extent_.begin();
}
HyperCube::ConstExtentIterator HyperCube::constEndIt() const {
   return extent_.end();
}


double HyperCube::getLowerExtent(int dim) const {
   return extent_[dim].first;
}

double HyperCube::getHigherExtent(int dim) const {
   return extent_[dim].second;
}

double HyperCube::getExtent(int dim) const {
   return extent_[dim].second - extent_[dim].first;
}

bool HyperCube::areExtentsFinite(SCIP* scip) const {
   for (int i = 0; i < ndim_; ++i)
   {
	   double extent(this->getExtent(i));
   	   if (SCIPisZero(scip, extent) || SCIPisInfinity(scip,extent) || SCIPisInfinity(scip,-extent))
   		   return false;
   }
   return true;
}

/*
 * Finds the extent that is closes to one and returns the inverse as normalization factor
 */
double HyperCube::getNormalizationFactor() const {
	double normExtent;
	for (int i = 0; i < ndim_; ++i)
	{
		double extent(this->getExtent(i));
		if (i == 0)
		{
			normExtent = extent;
		}
		else
		{
			if (abs(normExtent-1) > abs(extent - 1))
				normExtent = extent;
		}
	}
	return 1/normExtent;
}

void HyperCube::addDim(double lower, double higher) {
	assert(lower <= higher);
	extent_.push_back(std::pair<double,double>(lower,higher));
	++ndim_;
}

/*
 * Checks if a vector is inside of this hypercube
 */
bool HyperCube::contains(sdscip::Vector vec) {
   assert(vec.getDim() == ndim_);
   sdscip::Vector::Components::iterator vecIt(vec.beginIt());
   for (Extent::iterator it = this->beginIt(); it != this->endIt(); ++it) {
      if (*vecIt < it->first)
         return false;
      if (*vecIt > it->second)
         return false;
      ++vecIt;
   }
   return true;
}

/*
 * Checks if a vector is inside of this hypercube using the scip comparison functions
 */
bool HyperCube::contains(SCIP* scip, sdscip::Vector vec) {
   assert(vec.getDim() == ndim_);
   sdscip::Vector::Components::iterator vecIt(vec.beginIt());
   for (Extent::iterator it = this->beginIt(); it != this->endIt(); ++it) {
      SCIPcppDbgMsg("comparing component " << *vecIt << " with lower extent " << it->first << std::endl);
      if (SCIPisLT(scip,*vecIt,it->first))
         return false;
      SCIPcppDbgMsg("comparing component " << *vecIt << " with higher extent " << it->second << std::endl);
      if (SCIPisGT(scip, *vecIt,it->second))
         return false;

      ++vecIt;
   }
   return true;
}


/*
 * Checks if a vector is on one of the faces of the cube using the scip comparison functions
 */
bool HyperCube::isOnFace(SCIP* scip, sdscip::Vector vec) {
   assert(vec.getDim() == ndim_);
   sdscip::Vector::Components::iterator vecIt(vec.beginIt());
   for (Extent::iterator it = this->beginIt(); it != this->endIt(); ++it) {
      SCIPcppDbgMsg("comparing component " << std::setprecision(16) << *vecIt << " with lower extent " << it->first << std::endl);
      if (SCIPisEQ(scip,*vecIt,it->first))
         return true;
      SCIPcppDbgMsg("comparing component " << std::setprecision(16) << *vecIt << " with higher extent " << it->second << std::endl);
      if (SCIPisEQ(scip, *vecIt,it->second))
         return true;
      ++vecIt;
   }
   return false;
}

/*
 * Checks if a vector is on one of the vertices of the cube using the scip comparison functions
 */
bool HyperCube::isOnVertex(SCIP* scip, sdscip::Vector vec) {
   assert(vec.getDim() == ndim_);
   sdscip::Vector::Components::iterator vecIt(vec.beginIt());
   for (Extent::iterator it = this->beginIt(); it != this->endIt(); ++it) {
      /* If a single vector component is not on the higher or lower extent, the vector does not point to a vertex */
      if (!SCIPisEQ(scip,*vecIt,it->first) && !SCIPisEQ(scip,*vecIt,it->second))
         return false;
      ++vecIt;
   }
   return true;
}


/*
 * Finds the vertex of the hypercube that is severed by the hyperplane.
 * If no vertex is found, a 0-dim orthant is returned
 * function also returns the intersections of the edges
 */
HyperCube::VertexIntersectionsPair HyperCube::findSeveredVertex(const sdscip::HyperPlane * plane) const {
   assert(plane->getDim() == ndim_);
   sdscip::OrthantList oList(ndim_);

   for(OrthantList::OrthantIterator it = oList.beginIt(); it != oList.endIt(); ++it)
   {
      //std::cout << "Considering orthant " << it->toString() << std::endl;
      std::vector<sdscip::Line> edges(this->getEdges(*it));
      std::vector<sdscip::Vector> intersections;
      bool cutOff(true);
      for(std::vector<sdscip::Line>::iterator lineIt = edges.begin();  lineIt != edges.end(); ++lineIt) {
         //std::cout << "checking if plane cuts line " << std::endl << lineIt->toString() << std::endl;
         sdscip::Vector intersection(lineIt->intersection(plane));
         //std::cout << "Found intersection " << intersection.toString() << std::endl;
         if (intersection.getDim() == 0) {
            cutOff = false;
            //std::cout << "Untouched edge, breaking" << std::endl;
            break;
         }
         intersections.push_back(intersection);
      } //End of loop over vertices of this edge
      if (cutOff)
         return HyperCube::VertexIntersectionsPair(*it,intersections);
   }
   //std::cout << "Returning empty orthant " << std::endl;
   return HyperCube::VertexIntersectionsPair(Orthant(0),std::vector<sdscip::Vector>());

}


/*
 * Returns the volume separated from the hypercube by the hyperplane.
 * Only works when one vertex of the cube is severed completely
 * Returns 0 if no vertex was found, or
 */

double HyperCube::getSeparatedVolume(const sdscip::HyperPlane * plane) const {
   sdscip::HyperCube::VertexIntersectionsPair pair = this->findSeveredVertex(plane);
   sdscip::Orthant orth(pair.first);
   std::vector<sdscip::Vector> intersections(pair.second);
   if (orth.getDim() == 0) {
      //std::cout << "No cleanly severed vertex found" << std::endl;
      return 0;
   }
   sdscip::Vector vertex(this->getVertex(orth));
   double vol(1);
   /* Calculated pyramid sides */
   for (
      std::pair<sdscip::Orthant::ConstHalfSpaceIterator,std::vector<sdscip::Vector>::const_iterator > it(orth.constBeginIt(),intersections.begin());
      it.first != orth.constEndIt() && it.second != intersections.end();
      ++(it.first), ++(it.second)
   ) {
      int dim = it.second - intersections.begin();
      //std::cout << "it.first is " << *(it.first).toString() << std::endl;
      double component((*it.second).getComponent(dim));
      if (*it.first) //Positive halfspace
         vol = vol * (extent_[dim].second - component);
      else //Negative halfspace
         vol = vol * (component - extent_[dim].first);
   }
   return (vol / ndim_);
}

double HyperCube::getRelativeSeparatedVolume(const sdscip::HyperPlane * plane) const {
   double vol(this->getSeparatedVolume(plane));
   return vol / this->getVolume();
}

double HyperCube::getVolume() const {
   if (ndim_ == 0)
      return 0;

   double vol(1);
   for (ConstExtentIterator it = this->constBeginIt(); it != this->constEndIt(); ++it) {
      vol = vol * (it->second - it->first);
   }
   return vol;
}




/*
 * Gets the Edges of the HyperCube that end in the Vertex associated with orth
 */
std::vector<sdscip::Line> HyperCube::getEdges(sdscip::Orthant orth) const {
   std::vector<sdscip::Line> lines;
   sdscip::Vector a(this->getVertex(orth));
   //std::cout << "Got Vertex a: " << a.toString() << std::endl;
   for (Orthant::HalfSpaceIterator it = orth.beginIt(); it != orth.endIt(); ++it) {
      int dim = it - orth.beginIt();
      sdscip::Vector b(a);
      if (*it)
         b.setComponent(dim,this->getLowerExtent(dim));
      else
         b.setComponent(dim,this->getHigherExtent(dim));
      lines.push_back(sdscip::Line(a,b));
   }

   return lines;



}
/*
 * Gets the point representing the Edge associated with orth
 */
sdscip::Vector HyperCube::getVertex(sdscip::Orthant orth) const {
   assert(ndim_ == orth.getDim());
   sdscip::Vector vertex;
   ConstExtentIterator extentIt = constBeginIt();
   for (Orthant::HalfSpaceIterator it = orth.beginIt(); it != orth.endIt(); ++it) {
      if (*it)
         vertex.addDim(extentIt->second);
      else
         vertex.addDim(extentIt->first);
      extentIt++;
   }
   return vertex;
}

/*
 * Checks if a hyperplane intersects with the cube
 * For an intersection to exist, at least one vertex of the cube must be in the direction of the
 * normal vector of the plane, and the other one in the opposite direction. We compute projections of
 * vectors from the plane point to the vertex until we find one of both
 */
bool HyperCube::intersects(const sdscip::HyperPlane plane) const {
   assert(ndim_ == plane.getDim());
   bool foundPos(false);
   bool foundNeg(false);

   const sdscip::Vector planeVec(*plane.getVector());
   const sdscip::Vector planePoint(*plane.getPoint());

   sdscip::OrthantList oList(ndim_);

   for(OrthantList::OrthantIterator it = oList.beginIt(); it != oList.endIt(); ++it)
   {
      //std::cout << "Considering orthant " << it->toString() << std::endl;
      sdscip::Vector vertex(this->getVertex(*it));
      sdscip::Vector r(vertex - planePoint);
      double projection(r*planeVec);
      if (projection >= 0)
         foundPos = true;
      else
         foundNeg = true;

      if (foundPos && foundNeg)
         break;
   }
   return (foundPos && foundNeg);
}





}
