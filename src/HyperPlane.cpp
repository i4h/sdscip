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

/**@file    HyperPlane.cpp
 * @brief   Hyperplane class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#include "HyperPlane.h"

namespace sdscip {

HyperPlane::HyperPlane() :
   ndim_(0)
{ }

HyperPlane::HyperPlane(int _ndim) :
   ndim_(_ndim)
   ,vector_(sdscip::Vector(_ndim))
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

const sdscip::Vector * HyperPlane::getVector() const {
   return &vector_;
}

const sdscip::Vector * HyperPlane::getPoint() const {
   return &point_;
}



}
