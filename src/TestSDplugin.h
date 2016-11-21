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

/**@file    TestSDplugin.h
 * @brief   Base class for tests of SCIP plugins used by SD-SCIP
 * @author  Ingmar Vierhaus
 *
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
