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

/**@file    Point.cpp
 * @brief   Point class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#include "Point.h"

namespace sdscip {



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


/*Point::Point(sdscip::Vector vec) {
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
