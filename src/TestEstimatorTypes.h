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
