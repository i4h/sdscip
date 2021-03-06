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

/**@file    Line.cpp
 * @brief   Line class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#include "Line.h"

namespace sdscip {

Line::Line() :
   ndim_(0)
   ,a_(0)
   ,b_(0)
{ }

Line::Line(int _ndim) :
   ndim_(_ndim)
   ,a_(_ndim)
   ,b_(_ndim)
{ }

Line::Line(sdscip::Vector _a, sdscip::Vector _b) :
   a_(_a)
   ,b_(_b)
{
   ndim_ = a_.getDim();

}



Line::~Line()
{
   // TODO Auto-generated destructor stub
}

std::string Line::toString() {
   std::ostringstream o;
   o << ndim_ << "-dim Line, a: " << a_.toString() << ", b: " << b_.toString();
   return o.str();
}

/*
 * We parametrize the line as x = a + \alpha(a-b), insert into the
 * equation of the hyperplane n(x-p) = 0 (with normal vector n and contained point p),
 * and solve for alpha:
 * \alpha = frac{n(p-a)}{n(b-a)}
 * The hyperplane cuts the line if \alpha \in [0,1]
 */
sdscip::Vector Line::intersection(const sdscip::HyperPlane *plane) {
   assert(ndim_ == plane->getDim());

   double enumerator(*(plane->getVector()) * (*(plane->getPoint()) - a_));
   double denominator(*(plane->getVector()) * (b_ - a_));

   if (denominator < 1e-9 && denominator > -1e-9) {
      /* Denominator is ~ 0 -> line and plane are parallel */
      return sdscip::Vector(0);
   }

   double alpha(enumerator / denominator);

   /*
   std::cout << "alpha is " << alpha << std::endl;
   std::cout << "enum is " << enumerator<< std::endl;
   std::cout << "denom is " << denominator << std::endl;
   */

   if (alpha < 0 || alpha > 1)
      return sdscip::Vector(0);
   else
   {
      sdscip::Vector result(a_ + alpha*(b_-a_));
      //std::cout << "result is " << result.toString() << std::endl;
      return result;
   }
}

/*Line::Components::iterator Line::beginIt() {
   return components_.begin();
}
Line::Components::iterator Line::endIt() {
   return components_.end();
}
Line::Components::iterator Line::lastIt() {
   Components::iterator it(components_.end());
   --it;
   return it;
}
*/

int Line::getDim() {
   return ndim_;
}


}
