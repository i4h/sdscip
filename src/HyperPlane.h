/*
 * HyperPlane.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#ifndef HYPERPLANE_H_
#define HYPERPLANE_H_

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include "Vector.h"



namespace SDgeom {


class Vector;

class HyperPlane
{



public:
   typedef Vector::Components::iterator ComponentIterator;
   HyperPlane();
   HyperPlane(int _ndim);
   HyperPlane(SDgeom::Vector);
   HyperPlane(Vector _vector, Vector _point);
   virtual ~HyperPlane();
   std::string toString() const;
   void addDim(double);
   int getDim() const;
   const SDgeom::Vector * getVector() const;
   const SDgeom::Vector * getPoint() const;
   Vector::Components::iterator vecBeginIt();
   Vector::Components::iterator vecEndIt();
   Vector::Components::iterator pointBeginIt();
   Vector::Components::iterator pointEndIt();

private:
   int ndim_;
   Vector vector_;
   Vector point_;

};

}

#endif /* HYPERPLANE_H_ */
