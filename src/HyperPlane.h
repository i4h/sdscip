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

/**@file    HyperPlane.h
 * @brief   Hyperplane class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#ifndef HYPERPLANE_H_
#define HYPERPLANE_H_

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include "Vector.h"



namespace sdscip {


class Vector;

class HyperPlane
{



public:
   typedef Vector::Components::iterator ComponentIterator;
   HyperPlane();
   HyperPlane(int _ndim);
   HyperPlane(sdscip::Vector);
   HyperPlane(Vector _vector, Vector _point);
   virtual ~HyperPlane();
   std::string toString() const;
   void addDim(double);
   int getDim() const;
   const sdscip::Vector * getVector() const;
   const sdscip::Vector * getPoint() const;
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
