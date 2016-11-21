/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 2012-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*    Copyright (C) 2016      Helmut-Schmidt University Hamburg              */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Lesser General Public License        */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.*/
/*                                                                           */
/*                                                                           */
/* Based on SCIP - Solving Constraint Integer Programs                       */
/* Copyright (C) 2002-2016 Zuse Institute Berlin                             */
/* SCIP is distributed under the terms of the SCIP Academic Licence,         */
/* see file COPYING in the SCIP distribution.                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    TestSBrateEvaluator.cpp
 * @brief   Test class for Scott, Barton rate evaluator
 * @author  Ingmar Vierhaus
 *
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
      ++nExecutedTests_;
   }
}

void TestSBrateEvaluator::runAll()
{
   runBoundTests();
}



}
