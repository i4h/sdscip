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

/**@file    Orthant.h
 * @brief   Orthant class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#ifndef ORTHANT_H_
#define ORTHANT_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <iterator>

namespace sdscip {


class Orthant
{
public:
   typedef std::deque<bool>::iterator  HalfSpaceIterator ;
   typedef std::deque<bool>::const_iterator  ConstHalfSpaceIterator ;
   Orthant();
   Orthant(int _ndim);
   virtual ~Orthant();
   std::string toString();
   HalfSpaceIterator beginIt();
   HalfSpaceIterator endIt();
   ConstHalfSpaceIterator constBeginIt();
   ConstHalfSpaceIterator constEndIt();

   HalfSpaceIterator lastIt();
   static std::vector<Orthant> getAllOrthants(int ndim);
   bool setAll(bool val);
   bool addDimFront(bool val);
   bool toggleDimFront(bool val);
   bool getHalfSpace(int dim);
   int getDim();


private:
   int ndim_;
   std::deque<bool> halfSpaces_; //Defines the orthand (true = +, false = -)

};
}
#endif /* ORTHANT_H_ */
