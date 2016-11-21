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

/**@file    Vector.cpp
 * @brief   Vector Class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#include "Vector.h"
#include <math.h>

namespace sdscip {

Vector::Vector() :
   Point()
{ }

Vector::Vector(int _ndim) :
   Point(_ndim)
{
}

Vector::Vector(std::vector<double> components) :
   Point(components)
{}

Vector::Vector(double x1, double x2) :
   Point(x1,x2)
{}

Vector::Vector(double x1, double x2, double x3) :
   Point(x1,x2,x3)
{}

std::string Vector::vec2string(std::vector<double> vec, std::string message)
{
   sdscip::Vector temp(vec);
   return message + temp.toString();
}

void Vector::printVec(std::vector<double> vec, std::string message)
{
   sdscip::Vector temp(vec);
   printf("%s = %s\n",message.c_str(), temp.toString().c_str());
}

Vector::~Vector()
{
   // TODO Auto-generated destructor stub
}

double Vector::length() {
   double length(0);
   for (Components::const_iterator it = this->constBeginIt(); it != this->constEndIt(); ++it) {
      length += (*it)*(*it);
   }
   length = sqrt(length);
   return length;
}


Vector& Vector::operator+=(Vector const& rhs) {
   assert(this->getDim() == rhs.getDim());

   for (
      std::pair<Vector::ComponentIterator, Vector::Components::const_iterator> it(this->beginIt(), rhs.constBeginIt());
      it.first != this->endIt() && it.second != rhs.constEndIt();
      ++it.first, ++it.second
   )
   {
      *(it.first) += *(it.second);
   }

   return *this;
}

Vector& Vector::operator-=(Vector const& rhs) {
   assert(this->getDim() == rhs.getDim());
   for (
      std::pair<Vector::ComponentIterator, Vector::Components::const_iterator> it(this->beginIt(), rhs.constBeginIt());
      it.first != this->endIt() && it.second != rhs.constEndIt();
      ++it.first, ++it.second
   )
   {
      *(it.first) -= *(it.second);
   }
   return *this;
}


Vector& Vector::operator*=(double scalar) {

   for (Vector::ComponentIterator it(this->beginIt()); it != this->endIt(); ++it)
   {
      *it *= scalar;
   }
   return *this;
}

Vector operator+( Vector lhs, Vector const & rhs ) {
   return lhs+=rhs;
}

Vector operator-( Vector lhs, Vector const & rhs ) {
   return lhs-=rhs;
}

Vector operator*( Vector lhs, double rhs ) {
   return lhs*=rhs;
}
Vector operator*( double lhs, Vector rhs) {
   return rhs*lhs;
}

double operator*( Vector lhs, Vector rhs) {
   assert(rhs.getDim() == rhs.getDim());
   double result(0);
   for (
      std::pair<Vector::ComponentIterator, Vector::Components::iterator> it(lhs.beginIt(), rhs.beginIt());
      it.first != lhs.endIt() && it.second != rhs.endIt();
      ++it.first, ++it.second
   )
   {
      result += *(it.first) * *(it.second);
   }
   return result;
}




}
