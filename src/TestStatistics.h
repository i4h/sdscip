/*
 * TestBoundMap.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef I4H_TESTSTATISTICS_H_
#define I4H_TESTSTATISTICS_H_

#include "Statistics.h"
#include "BaseTest.h"


namespace I4H
{

class TestStatistics : public BaseTest
{
public:
   TestStatistics();
   virtual ~TestStatistics();

   int getNsuccess();
   int getNerror();

   void runAll();

   void testMean();


   std::ostream& toString(std::ostream& strm) const;


private:
};

}

#endif /* I4H_TESTSTATISTICS_H_ */
