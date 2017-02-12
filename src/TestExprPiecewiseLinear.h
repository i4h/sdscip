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

/**@file    TestExprPiecewiseLinear.h
 * @brief   Test for ExprPiecewiseLinear
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TestExprPiecewiseLinear_H_
#define TestExprPiecewiseLinear_H_


#include "ProbDataSD.h"
#include "ExprPiecewiseLinear.h"
#include "Vector.h"
#include <boost/make_shared.hpp>
#include <spline/BSplineCurve.hpp>
#include <sdo/ExpressionGraph.hpp>
#include "BoundMapHelpers.cpp"
#include "TestSDplugin.h"
#include "Vector.h"
#include <sstream>

namespace sdscip
{

struct EstimationData
{
   SCIP_Real coefficient;
   SCIP_Real constant;
   bool overestimate;
};

/* Data needed for one single estimator sampling test */
class EstimatorTestData
{
public:
   /* Points defining the lookup */
   std::pair<std::vector<SCIP_Real>, std::vector<SCIP_Real> > points;

   /* Vector of bounds in which estimation should be tested */
   std::vector<std::pair<SCIP_Real, SCIP_Real> > argbounds;

   /* Point within argbound where estimation should be as tight as possible */
   std::vector<SCIP_Real > argvals;

   /* Label of this test */
   std::string label;

   /* Is this a test of over- or underesimators? */
   bool overestimate;

   /* Output test data to summarize failed tests */
   std::string toString(int boundidx);
};

/* Data needed for one single interval evaluator test */
class IntervalEvaluatorTestData
{
public:
   /* Points defining the lookup */
   std::pair<std::vector<SCIP_Real>, std::vector<SCIP_Real> > points;

   /* Vector if intervals that should be evaluated */
   std::vector<std::pair<SCIP_Real, SCIP_Real> > argbounds;

   /* Label of this test */
   std::string label;

   /* Output test data to summarize failed tests */
   std::string toString(int boundidx);
};

class TestExprPiecewiseLinear : public TestSDplugin
{

public:

   /* Pair of vectors of x- and y-values of points (defines a lookup) */
   using PointsPair = std::pair<std::vector<SCIP_Real>, std::vector<SCIP_Real> >;

   using Bound = std::pair<SCIP_Real, SCIP_Real>;
   using BoundVec = std::vector<std::pair<SCIP_Real, SCIP_Real> >;
   using ValVec = std::vector<SCIP_Real >;

   TestExprPiecewiseLinear(SCIP* scip);
   virtual ~TestExprPiecewiseLinear();

   /* Helpers */
   std::ostream& toString(std::ostream& strm) const;
   SCIP_Real evaluateEstimation(EstimationData estimation, SCIP_Real x);
   std::string estimationToString(EstimationData estimation);
   static bool verifyEstimation(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval, SCIP_Real tolerance);
   double compareEstimationSpline(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval);
   void removeCoincidingPoints(ValVec &xvals, ValVec &yvals);
   SCIP_EXPR* createExprPiecewiseLinear(ValVec xPoints, ValVec yPoints, std::string identifier);
   SCIP_EXPR* createExprPiecewiseLinearFromIntervalEvaluatorTest(IntervalEvaluatorTestData data);
   SCIP_EXPR* createExprPiecewiseLinearFromEstimatorTest(EstimatorTestData data);
   EstimationData getEstimation(SCIP_EXPR* pcwlin, SCIP_Real argvals, Bound argbounds, bool overestimate);
   Bound getIntervalEvaluation(SCIP_EXPR* pcwlin, Bound argbound);
   bool sampleEstimation(SCIP_EXPR* pcwlin, int nPoints, Bound argbound, EstimationData estimation);
   static bool sampleEstimationAtKnots(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, Bound argbound, int &localErrors, SCIP_Real tolerance);
   static bool isIntervalEvaluationValidAtPoint(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, SCIP_Real point, Bound bound, SCIP_Real tolerance);
   static bool isValueInBound(Bound bound, SCIP_Real value, SCIP_Real tolerance);
   static bool sampleIntervalEvaluationAtKnots(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, Bound interval, Bound argbound, int &localErrors, SCIP_Real tolerance);
   std::vector<EstimatorTestData> estimatorTestsData_;
   std::vector<IntervalEvaluatorTestData> intervalEvaluatorTestsData_;


   /* Testdata management */
   void addManualEstimatorTests();
   PointsPair rollPoints(Bound xrange, Bound yrange, int nPoints, bool integerDataPoints );
   void addRandomEstimatorTests(int nTests, Bound xrange, Bound yrange, bool integerDataPoints, int nArgBounds);
   void addNumericsEstimatorTests();
   void printEstimatorTests();
   void printIntervalEvaluatorTests();
   void clearTests();
   void executeEstimatorTests();
   void executeIntervalEvaluatorTests();

   void addManualIntervalEvaluateTests();

   /* Tests */
   void runEstimatorManualTests();
   void runWorldLookup();
   void runDNRULookup();
   void runWorldLookupFeastol();
   void runEstimatorRandomTests();
   void runEstimatorNumericsTests();

   void runIntervalEvaluatorManualTests();



   /* Run all tests */
   void runAll();

   /* Tolerance for floating point comparisons */
   const double tolerance_;

   /* (Low) Tolerance when comparing tightness of estimators */
   const double zeroTolerance_;

private:


};

}

#endif /* TestExprPiecewiseLinear_H_ */
