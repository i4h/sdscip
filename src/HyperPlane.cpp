/*
 * HyperPlane.cpp
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#include "HyperPlane.h"

namespace SDgeom {

HyperPlane::HyperPlane() :
   ndim_(0)
{ }

HyperPlane::HyperPlane(int _ndim) :
   ndim_(_ndim)
   ,vector_(SDgeom::Vector(_ndim))
{

}

HyperPlane::HyperPlane(Vector _vector) :
   ndim_(_vector.getDim())
   ,vector_(_vector)
   ,point_(_vector)

{

}

HyperPlane::HyperPlane(Vector _vector, Vector _point) :
   ndim_(_vector.getDim())
   ,vector_(_vector)
   ,point_(_point)

{ }


HyperPlane::~HyperPlane()
{
   // TODO Auto-generated destructor stub
}

std::string HyperPlane::toString() const {
   std::ostringstream o;
   o << ndim_ << "-dim Hyperplane, Point: " << point_.toString() <<", Normalvector: " << vector_.toString() << std::endl;
   return o.str();
}



Vector::Components::iterator HyperPlane::vecBeginIt() {
   return vector_.beginIt();
}
Vector::Components::iterator HyperPlane::vecEndIt() {
   return vector_.endIt();
}

Vector::Components::iterator HyperPlane::pointBeginIt() {
   return point_.beginIt();
}
Vector::Components::iterator HyperPlane::pointEndIt() {
   return point_.endIt();
}


void HyperPlane::addDim(double value) {
   vector_.addDim(value);
   ++ndim_;
}

int HyperPlane::getDim() const {
   return ndim_;
}

const SDgeom::Vector * HyperPlane::getVector() const {
   return &vector_;
}

const SDgeom::Vector * HyperPlane::getPoint() const {
   return &point_;
}



}
