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

/**@file    TestBoundMap.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "TestBoundMap.h"

namespace sdscip
{

using BoundMap = SDproblemStructureInterface::BoundMap;
using BoundKey = SDproblemStructureInterface::BoundKey;

TestBoundMap::TestBoundMap(SCIP* _scip) :
   SDSCIPtest(_scip)
{
   runAll();
}

TestBoundMap::~TestBoundMap()
{
}

std::ostream& TestBoundMap::toString(std::ostream& strm) const {
  return strm << "TestBoundMap";
}


int TestBoundMap::getNsuccess()
{
   return nSuccess_;
}

int TestBoundMap::getNerror()
{
   return nError_;
}

void TestBoundMap::runAll()
{
   SCIPdbgMsg("running all\n");
   testOperations();

   SCIPdebugMessage("Finished running all, %i success, %i errors\n",nSuccess_, nError_);
}

/* Tests some oeprations on boundmap */
void TestBoundMap::testOperations()
{
/*
 * Combinations to check:
 *  (0 No bound known
 *  (1) map1 bound , no map2 bound
 *  (2) map2 bound, no map1 bound
 *  (3) map1 bound, better map2 bound
 *  (4) map2 bound, better map1 bound
 *
 */
   const std::vector<SCIP_Real> goodBound = {-9.0 , 8.0};
   const std::vector<SCIP_Real> betterBound = {-4.0 , 5.0};

   BoundMap map1;
   BoundMap map2;

   for (int i = 0; i < 2; ++i)
   {
      SCIP_BOUNDTYPE type = (SCIP_BOUNDTYPE) i;
      map1[BoundKey(2, type)] = goodBound[i];
      map2[BoundKey(3, type)] = goodBound[i];
      map1[BoundKey(4, type)] = goodBound[i];
      map2[BoundKey(4, type)] = betterBound[i];

      map2[BoundKey(5, type)] = goodBound[i];
      map1[BoundKey(5, type)] = betterBound[i];
   }
   BoundMap mapUnion = getUnion(map1, map2);

   /* Evaluate */
   for (int i = 0; i < 2; ++i)
   {
      SCIP_BOUNDTYPE type = (SCIP_BOUNDTYPE) i;

      /* Make sure there are no entries in 1,2,3 */
      for (int j = 0; j < 3; ++j)
      {
         auto it1 = mapUnion.find(BoundKey(j,type));
         test(it1 == mapUnion.end());
      }

      /* Make sure 4,5 contain the wider bounds */
      test(mapUnion[BoundKey(4,type)] == goodBound[i]);
      test(mapUnion[BoundKey(5,type)] == goodBound[i]);
   }

   BoundMap mapIntersection = getIntersection(map1, map2);
   //printf("Created union:\n");
   //printBoundMap(mapIntersection);
   /* Evaluate */
   for (int i = 0; i < 2; ++i)
   {
      SCIP_BOUNDTYPE type = (SCIP_BOUNDTYPE) i;
      test(mapIntersection[BoundKey(2,type)] == goodBound[i]);
      test(mapIntersection[BoundKey(3,type)] == goodBound[i]);
      test(mapIntersection[BoundKey(4,type)] == betterBound[i]);
      test(mapIntersection[BoundKey(5,type)] == betterBound[i]);
   }
   ++nExecutedTests_;
}

}
