/*
 * Statistics.h

 *
 *  Created on: 2015/06/15
 *      Author: Ingmar Vierhaus
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
