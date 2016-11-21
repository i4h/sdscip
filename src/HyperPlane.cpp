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

/**@file    HyperPlane.cpp
 * @brief   @todo
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
