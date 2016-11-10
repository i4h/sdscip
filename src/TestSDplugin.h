/*
 * TestSDplugin.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef TestSDplugin_H_
#define TestSDplugin_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"
#include "SDSCIPtest.h"

namespace sdscip
{

class TestSDplugin : public SDSCIPtest
{
public:
   TestSDplugin(SCIP* scip);
   virtual ~TestSDplugin();

   //int getNsuccess();
   //int getNerrors();
   //int getNtests();

   /* Helpers */
   int getRandInt(int min, int max);
   int getRandInt(double min, double max);
   double getRandDouble(double min, double max);

protected:
   SCIP* subscip_; /* Private scip to hold memory for testing expressions */
   //int nSuccess_;
   //int nErrors_;
   //int nTests_;
};

}

#endif /* TestSDplugin_H_ */
