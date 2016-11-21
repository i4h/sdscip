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

/**@file    Statistics.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef I4H_STATISTICS_H_
#define I4H_STATISTICS_H_

#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include <iomanip>


namespace I4H {

class Statistics
{

public:
   typedef std::vector<double>  Components ;
   Statistics();
   virtual ~Statistics();
   void clear();
   void addVal(double val);
   double mean();
   double max();
   double min();
   int nVals();

private:
   std::vector<double> values_;
   double max_;
   double min_;
   double sum_;
};

}

#endif /* I4H_STATISTICS_H_ */
