//#define SCIP_DBG
//#define SCIP_DEBUG
/*
 * TestSBratEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "TestSBrateEvaluator.h"

namespace sdscip
{

TestSBrateEvaluator::TestSBrateEvaluator(SCIP* scip) :
   SDSCIPtest(scip)
{ }

TestSBrateEvaluator::~TestSBrateEvaluator()
{
}

std::ostream& TestSBrateEvaluator::toString(std::ostream& strm) const {
  return strm << "TestSBrateEvaluator";
}


int TestSBrateEvaluator::getNsuccess()
{
   return nSuccess_;
}

int TestSBrateEvaluator::getNerrors()
{
   return nError_;
}



/*
 * Combinations to check:
 *  (0 No bound known
 *  (1) Global bound known, no local bound known
 *  (2) Local bound known, no global bound known
 *  (3) Local bound known, better global bound known
 *  (4) Local bound known, worse global bound known
 */
void TestSBrateEvaluator::runBoundTests()
{
   SCIPdbgMsg("running BoundTests\n");
   const std::vector<SCIP_Real> goodBound = {-9.0 , 8.0};
   const std::vector<SCIP_Real> betterBound = {-4.0 , 3.0};

   for( int boundType = SCIP_BOUNDTYPE_LOWER; boundType <= SCIP_BOUNDTYPE_UPPER; ++boundType)
   {

      SBrateEvaluator rateEvaluator(3, 0, 0, scip_);
      /* Set global bounds */
      rateEvaluator.addGlobalStateBound(1, (SCIP_BOUNDTYPE) boundType, goodBound[boundType]);
      rateEvaluator.addGlobalStateBound(3, (SCIP_BOUNDTYPE) boundType, betterBound[boundType]);
      rateEvaluator.addGlobalStateBound(4, (SCIP_BOUNDTYPE) boundType, goodBound[boundType]);

      /* Create stateBounds map */
      SBrateEvaluator::BoundMap stateBounds;
      stateBounds[SBrateEvaluator::BoundKey(2, (SCIP_BOUNDTYPE) boundType)] = goodBound[boundType];
      stateBounds[SBrateEvaluator::BoundKey(3, (SCIP_BOUNDTYPE) boundType)] = goodBound[boundType];
      stateBounds[SBrateEvaluator::BoundKey(4, (SCIP_BOUNDTYPE) boundType)] = betterBound[boundType];

      /* Get tightest Bounds */
      SBrateEvaluator::BoundMap tightestBounds = rateEvaluator.getTightestEnclosure(stateBounds);

      /* Check */
      /* dim 0 should be emtpy*/
      int myErrors = 0;
      auto it = tightestBounds.find(SBrateEvaluator::BoundKey(0, (SCIP_BOUNDTYPE) boundType));
      if( it != tightestBounds.end())
         ++myErrors;

      /*dim 1 and 2 should be good bounds */
      if( tightestBounds[SBrateEvaluator::BoundKey(1, (SCIP_BOUNDTYPE) boundType)] != goodBound[boundType])
      {
         ++myErrors;
      }
      if( tightestBounds[SBrateEvaluator::BoundKey(2, (SCIP_BOUNDTYPE) boundType)] != goodBound[boundType])
      {
         ++myErrors;
      }


      /* dim 3  and 4 should be betterBound */
      if( tightestBounds[SBrateEvaluator::BoundKey(3, (SCIP_BOUNDTYPE) boundType)] != betterBound[boundType])
      {
         ++myErrors;

      }
      if( tightestBounds[SBrateEvaluator::BoundKey(4, (SCIP_BOUNDTYPE) boundType)] != betterBound[boundType])
      {
         ++myErrors;
      }

      if( myErrors == 0)
         ++nSuccess_;
      else
         nError_ += myErrors;
   }
}

void TestSBrateEvaluator::runAll()
{
   runBoundTests();
}



}
