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

/**@file    TestEstimatorTypes.h
 * @brief   Test for safe estimator types
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TestEstimatorTypes_HPP_
#define TestEstimatorTypes_HPP_


#include "TestExprPiecewiseLinear.h"
#include "ProbDataSD.h"
#include "ExprPiecewiseLinear.h"
#include "Vector.h"
#include <boost/make_shared.hpp>
#include <spline/BSplineCurve.hpp>
#include <sdo/ExpressionGraph.hpp>
#include "BoundMapHelpers.cpp"
#include "TestSDplugin.h"
#include "Vector.h"

namespace sdscip
{

class EstimatorTypeTestData : public EstimatorTestData
{
public:
   EstimatorTypeTestData() :
        EstimatorTestData()
       ,e5valid(false)
       ,e6valid(false)
   {}

   std::vector<SAFE_ESTIMATOR> validTypes; /* Which of the estimator types are expected to be valid in this test */
   std::vector<SAFE_ESTIMATOR> bestTypes; /* Which of the estimator types is expected to be selected for each argval */

   /* This test does not include the determination of x1, x2.
    * y1, y2 are determined by evaluating the the spline function at x1,x2 */
   double x1;
   double x2;

   bool e5valid;
   bool e6valid;
};


class TestEstimatorTypes : public TestExprPiecewiseLinear
{

public:
   TestEstimatorTypes(SCIP* scip);
   ~TestEstimatorTypes();
   std::ostream& toString(std::ostream& strm) const;
   void addE1E3tests();
   void addE2E4tests();
   void addE5E6tests();

   void runClass1EstimatorTypesTests();

   std::map<SAFE_ESTIMATOR, double>::const_iterator findSmallestErrorIt(std::map<SAFE_ESTIMATOR, double> errsAtX);

   std::vector<EstimatorTypeTestData> typeTestsData_;

   void runTests();
   void runAll();

private:
};

}

#endif /* TestEstimatorTypes_HPP_ */
