/*
 * TestExprPiecewiseLinear.hpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
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
   /* Points defining the estimation */
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

class TestExprPiecewiseLinear : public TestSDplugin
{

public:

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
   SCIP_EXPR* createExprPiecewiseLinear(EstimatorTestData data);
   EstimationData getEstimation(SCIP_EXPR* pcwlin, SCIP_Real argvals, Bound argbounds, bool overestimate);
   bool sampleEstimation(SCIP_EXPR* pcwlin, int nPoints, Bound argbound, EstimationData estimation);
   static bool sampleEstimationAtKnots(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, Bound argbound, int &localErrors, SCIP_Real tolerance);
   std::vector<EstimatorTestData> testsData_;

   /* Testdata management */
   void addManualEstimatorTests();
   void addRandomEstimatorTests(int nTests, Bound xrange, Bound yrange, bool integerDataPoints, int nArgBounds);
   void addNumericsEstimatorTests();
   void printTests();
   void clearTests();
   void runTests();

   /* Tests */
   void runEstimatorManualTests();
   void runWorldLookup();
   void runEstimatorRandomTests();
   void runEstimatorNumericsTests();




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