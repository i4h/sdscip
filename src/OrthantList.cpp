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

/**@file    OrthantList.cpp
 * @brief   Class representing list of orthants
 * @author  Ingmar Vierhaus
 *
 */


#include "OrthantList.h"

namespace sdscip {
using namespace sdscip;

OrthantList::OrthantList()
{
}

OrthantList::OrthantList(int ndim) {
   makeOrthants(ndim);
}


OrthantList::~OrthantList()
{
}

std::vector<Orthant>::iterator OrthantList::beginIt() {
   return orthants_.begin();
}
std::vector<Orthant>::iterator OrthantList::endIt() {
   return orthants_.end();
}


std::string OrthantList::toString() {
   std::ostringstream o;
   o << "List of " << orthants_.size() << " Orthants:" << std::endl;
   for(std::vector<Orthant>::iterator it = orthants_.begin(); it != orthants_.end(); ++it)
   {
      o << it->toString() << std::endl;
   }
   return o.str();
}

void OrthantList::makeOrthants(int ndim) {

   if (ndim == 1) /* Recursion root */
   {
      orthants_.clear();
      orthants_.reserve(2);
      Orthant orthPos(1);
      Orthant orthNeg(1);
      orthNeg.setAll(false);
      orthants_.push_back(Orthant(1));
      orthants_.push_back(orthNeg);
      return;
   }
   else
   {
      this->makeOrthants(ndim-1);
      int lastDimSize = orthants_.size();

      orthants_.reserve(2*lastDimSize); // preallocate memory for this dimensions

      // Add dimension to orthants and set positive
      for(std::vector<Orthant>::iterator it = orthants_.begin(); it != orthants_.end(); ++it)
         it->addDimFront(true);

      // Duplicate orthants
      orthants_.insert( orthants_.end(), orthants_.begin(), orthants_.end() );

      // Toggle first dimension the second half (just copied entries)
      std::vector<Orthant>::iterator it = orthants_.begin();
      std::advance(it,lastDimSize);
      while (it != orthants_.end())
      {
         it->toggleDimFront(true);
         ++it;
      }

      return;
   }
}
}
