#define SCIP_DBG
#define SCIP_DEBUG
/*
 * TestSBratEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "TestBoundMap.h"

namespace sdscip
{

using BoundMap = SDproblemStructureInterface::BoundMap;
using BoundKey = SDproblemStructureInterface::BoundKey;

TestBoundMap::TestBoundMap() :
   nSuccess_(0)
   ,nErrors_(0)
{
   runAll();
}

TestBoundMap::~TestBoundMap()
{
}

int TestBoundMap::getNsuccess()
{
   return nSuccess_;
}

int TestBoundMap::getNerrors()
{
   return nErrors_;
}

void TestBoundMap::runAll()
{
   SCIPdbgMsg("running all\n");
   testOperations();

   SCIPdebugMessage("Finished running all, %i success, %i errors\n",nSuccess_, nErrors_);
}

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
   printf("map1:");
   printBoundMap(map1);
   printf("map2:");
   printBoundMap(map2);
   BoundMap mapUnion = getUnion(map1, map2);
   printf("Created union:\n");
   printBoundMap(mapUnion);
   /* Evaluate */
   for (int i = 0; i < 2; ++i)
   {
      SCIP_BOUNDTYPE type = (SCIP_BOUNDTYPE) i;

      /* Make sure there are no entries in 1,2,3 */
      for (int j = 0; j < 3; ++j)
      {
         auto it1 = mapUnion.find(BoundKey(j,type));
         assert(it1 == mapUnion.end());
      }

      /* Make sure 4,5 contain the wider bounds */
      assert(mapUnion[BoundKey(4,type)] == goodBound[i]);
      assert(mapUnion[BoundKey(5,type)] == goodBound[i]);
   }

   BoundMap mapIntersection = getIntersection(map1, map2);
   printf("Created union:\n");
   printBoundMap(mapIntersection);
   /* Evaluate */
   for (int i = 0; i < 2; ++i)
   {
      SCIP_BOUNDTYPE type = (SCIP_BOUNDTYPE) i;
      assert(mapIntersection[BoundKey(2,type)] == goodBound[i]);
      assert(mapIntersection[BoundKey(3,type)] == goodBound[i]);
      assert(mapIntersection[BoundKey(4,type)] == betterBound[i]);
      assert(mapIntersection[BoundKey(5,type)] == betterBound[i]);
   }
}





/*
 * Combinations to check:
 *  (0 No bound known
 *  (1) Global bound known, no local bound known
 *  (2) Local bound known, no global bound known
 *  (3) Local bound known, better global bound known
 *  (4) Local bound known, worse global bound known
 */
#if 0
void TestBoundMap::runBoundTests()
{
   SCIPdbgMsg("running BoundTests\n");
   const std::vector<SCIP_Real> goodBound = {-9.0 , 8.0};
   const std::vector<SCIP_Real> betterBound = {-4.0 , 3.0};

   for( int boundType = SCIP_BOUNDTYPE_LOWER; boundType <= SCIP_BOUNDTYPE_UPPER; ++boundType)
   {

      BoundMap rateEvaluator(3);
      /* Set global bounds */
      rateEvaluator.addGlobalStateBound(1, (SCIP_BOUNDTYPE) boundType, goodBound[boundType]);
      rateEvaluator.addGlobalStateBound(3, (SCIP_BOUNDTYPE) boundType, betterBound[boundType]);
      rateEvaluator.addGlobalStateBound(4, (SCIP_BOUNDTYPE) boundType, goodBound[boundType]);

      /* Create stateBounds map */
      BoundMap::BoundMap stateBounds;
      stateBounds[BoundMap::BoundKey(2, (SCIP_BOUNDTYPE) boundType)] = goodBound[boundType];
      stateBounds[BoundMap::BoundKey(3, (SCIP_BOUNDTYPE) boundType)] = goodBound[boundType];
      stateBounds[BoundMap::BoundKey(4, (SCIP_BOUNDTYPE) boundType)] = betterBound[boundType];

      /* Get tightest Bounds */
      BoundMap::BoundMap tightestBounds = rateEvaluator.getTightestEnclosure(stateBounds);

      /* Check */
      /* dim 0 should be emtpy*/
      int myErrors = 0;
      auto it = tightestBounds.find(BoundMap::BoundKey(0, (SCIP_BOUNDTYPE) boundType));
      if( it != tightestBounds.end())
         ++myErrors;

      /*dim 1 and 2 should be good bounds */
      if( tightestBounds[BoundMap::BoundKey(1, (SCIP_BOUNDTYPE) boundType)] != goodBound[boundType])
      {
         ++myErrors;
      }
      if( tightestBounds[BoundMap::BoundKey(2, (SCIP_BOUNDTYPE) boundType)] != goodBound[boundType])
      {
         ++myErrors;
      }


      /* dim 3  and 4 should be betterBound */
      if( tightestBounds[BoundMap::BoundKey(3, (SCIP_BOUNDTYPE) boundType)] != betterBound[boundType])
      {
         ++myErrors;

      }
      if( tightestBounds[BoundMap::BoundKey(4, (SCIP_BOUNDTYPE) boundType)] != betterBound[boundType])
      {
         ++myErrors;
      }

      if( myErrors == 0)
         ++nSuccess_;
      else
         nErrors_ += myErrors;
   }

}
#endif


}
