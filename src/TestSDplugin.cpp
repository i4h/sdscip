#define SCIP_DBG
#define SCIP_DEBUG
/*
 * TestSDplugin.cpp
 *
 *  Created on: 02/16/2016
 *      Author: Ingmar Vierhaus
 */


#include "TestSDplugin.hpp"

namespace sdscip
{

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


