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

/**@file    Vector.h
 * @brief   Vector Class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */

#ifndef SD_GEOM_VECTOR_H_
#define SD_GEOM_VECTOR_H_

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include <iostream>
#include "Point.h"


namespace sdscip {


class Vector : public Point {

public:
   typedef std::vector<double>  Components ;
   typedef std::vector<double>::iterator ComponentIterator ;
   Vector();
   Vector(int _ndim);
   Vector(std::vector<double>);
   /* Shortcut constructors Used for testing */
   Vector(double x1, double x2);
   Vector(double x1, double x2, double x3);
   static std::string vec2string(std::vector<double> vec, std::string message);
   static void printVec(std::vector<double> vec, std::string message);

   virtual ~Vector();

   Vector& operator+=(Vector const& lhs);
   Vector& operator*=(double scalar);
   Vector& operator-=(Vector const& rhs);

   double length();


/*
   std::string toString();
   void addDim(double);
   Components::iterator beginIt();
   Components::iterator endIt();
   Components::iterator lastIt();
   int getDim();
   void setComponent(int dim, double value);

private:
   int ndim_;
   Components components_;
   */
};

Vector operator+( Vector lhs, Vector const & rhs );
Vector operator*( Vector lhs, double rhs );
Vector operator*( double rhs , Vector lhs);
/* Scalar product */
double operator*( Vector rhs , Vector lhs);
Vector operator-( Vector lhs, Vector const & rhs );
}

#endif /* SD_GEOM_VECTOR_H_ */
