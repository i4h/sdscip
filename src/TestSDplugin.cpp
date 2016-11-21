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

/**@file    TestSDplugin.cpp
 * @brief   Base class for tests of SCIP plugins used by SD-SCIP
 * @author  Ingmar Vierhaus
 *
 */


#include "TestSDplugin.h"

namespace sdscip {

TestSDplugin::TestSDplugin(SCIP* scip) :
   SDSCIPtest(scip)
{
   SCIPcreate(&subscip_);
   SCIPcreateProbBasic(subscip_, "TestSDplugin memory container");
}

TestSDplugin::~TestSDplugin()
{
   // TODO Auto-generated destructor stub
   SCIPfreeProb(subscip_);
   SCIPfree(&subscip_);
}

int TestSDplugin::getRandInt(int min, int max)
{
   return rand() % (max - min + 1) + min;
}

int TestSDplugin::getRandInt(double min, double max)
{
   int intmin = std::floor(min);
   int intmax = std::ceil(max);
   return getRandInt(intmin, intmax);
}


double TestSDplugin::getRandDouble(double min, double max)
{
   return (double) rand() / RAND_MAX * (max - min) + min;
}


}
