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

/**@file    Statistics.cpp
 * @brief   @todo
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
