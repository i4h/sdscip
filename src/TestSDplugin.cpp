#define SCIP_DBG
#define SCIP_DEBUG
/*
 * TestSDplugin.cpp
 *
 *  Created on: 02/16/2016
 *      Author: Ingmar Vierhaus
 */


#include "TestSDplugin.hpp"

namespace ctrl
{

TestSDplugin::TestSDplugin(SCIP* scip) :
   scip_(scip)
   ,nSuccess_(0)
   ,nErrors_(0)
   ,nTests_(0)
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

int TestSDplugin::getNsuccess()
{
   return nSuccess_;
}

int TestSDplugin::getNerrors()
{
   return nErrors_;
}

int TestSDplugin::getNtests()
{
   return nTests_;
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


