/*
 * Point.cpp
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#include "Point.h"

namespace SDgeom {



Point::Point() :
   ndim_(0)
{ }

Point::Point(int _ndim) :
   ndim_(_ndim)
{
   for (int i = 0; i < ndim_; ++i)
      components_.push_back(0);
}

Point::Point(std::vector<double> components)
{
   components_ = components;
   ndim_ = components.size();
}

Point::Point(double x1, double x2) {
   ndim_ = 2;
   components_.push_back(x1);
   components_.push_back(x2);
}

Point::Point(double x1, double x2, double x3) {
   ndim_ = 3;
   components_.push_back(x1);
   components_.push_back(x2);
   components_.push_back(x3);
}


/*Point::Point(SDgeom::Vector vec) {
   for (Vector::Components::iterator it = vec.beginIt(); it != vec.endIt(); ++it) {
      addDim(*it);
   }
}*/

Point::~Point()
{
   // TODO Auto-generated destructor stub
}

std::string Point::toString() const {
   std::ostringstream o;
   o << ndim_ << "-dim Vector: (";
   for (Components::const_iterator it = this->constBeginIt(); it != this->constEndIt(); ++it) {
      o << std::setprecision(5) << *it;
      if (it != this->constLastIt())
         o << ", ";
   }
   o << ')';
   return o.str();
}

Point::Components::iterator Point::beginIt() {
   return components_.begin();
}
Point::Components::iterator Point::endIt() {
   return components_.end();
}
Point::Components::iterator Point::lastIt() {
   Components::iterator it(components_.end());
   --it;
   return it;
}

Point::Components::const_iterator Point::constBeginIt() const{
   return components_.begin();
}
Point::Components::const_iterator Point::constEndIt() const{
   return components_.end();
}
Point::Components::const_iterator Point::constLastIt() const {
   Components::const_iterator it(components_.end());
   --it;
   return it;
}



void Point::addDim(double value) {
   components_.push_back(value);
   ++ndim_;
}

void Point::setComponent(int dim, double value) {
   assert(dim + 1 <= ndim_);
   components_[dim] = value;
}

double Point::getComponent(int dim) const {
   assert(dim + 1 <= ndim_);
   return components_[dim];
}


int Point::getDim() const {
   return ndim_;
}


}
