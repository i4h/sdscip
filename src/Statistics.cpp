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

/**@file    Statistics.cpp
 * @brief   Basic statistics class
 * @author  Ingmar Vierhaus
 *
 */


#include "Statistics.h"

namespace I4H {

Statistics::Statistics() :
     max_(0)
    ,min_(0)
    ,sum_(0)
{ }

Statistics::~Statistics()
{ }

void Statistics::clear()
{
   values_.clear();
   min_ = 0;
   max_ = 0;
   sum_ = 0;
}

void Statistics::addVal(double val)
{
   sum_ += val;
   if (values_.size() == 0)
   {
      min_ = val;
      max_ = val;
   }
   else
   {
      if (min_ > val)
         min_ = val;
      if (max_ < val)
         max_ = val;
   }

   values_.push_back(val);
}

double Statistics::mean()
{
   if (values_.size() == 0)
      return 0;
   return sum_ / (double) values_.size();
}
double Statistics::max()
{
   return max_;
}
double Statistics::min()
{
   return min_;
}

int Statistics::nVals()
{
   return values_.size();
}




}
