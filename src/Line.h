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

/**@file    Line.h
 * @brief   Line class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SD_GEOM_LINE_H_
#define SD_GEOM_LINE_H_

#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
#include <iterator>

#include "Vector.h"
#include "Vector.h"
#include "HyperPlane.h"

namespace sdscip {

class Vector;
class HyperPlane;


class Line
{

public:
   typedef sdscip::Vector::Components::iterator ComponentIterator ;
   Line();
   Line(int _ndim);
   Line(sdscip::Vector a, sdscip::Vector b);
   virtual ~Line();

   /* Shortcut constructors Used for testing */

   std::string toString();
   sdscip::Vector intersection(const sdscip::HyperPlane *plane);
   /*
   Vector::Components::iterator aBeginIt();
   Vector::Components::iterator aEndIt();
   Vector::Components::iterator aLastIt();
   */
   int getDim();

private:
   int ndim_;
   Vector a_;
   Vector b_;
};

}

#endif /* SD_GEOM_LINE_H_ */
