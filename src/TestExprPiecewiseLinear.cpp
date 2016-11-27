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

/**@file    TestExprPiecewiseLinear.cpp
 * @brief   Test for ExprPiecewiseLinear
 * @author  Ingmar Vierhaus
 *
 */


#include "TestExprPiecewiseLinear.h"

namespace sdscip
{

TestExprPiecewiseLinear::TestExprPiecewiseLinear(SCIP* scip) :
    TestSDplugin(scip)
   ,tolerance_(1e-9)
   ,zeroTolerance_(1e-14)

{ }

TestExprPiecewiseLinear::~TestExprPiecewiseLinear()
{ }


std::ostream& TestExprPiecewiseLinear::toString(std::ostream& strm) const {
  return strm << "TestExprPiecewiseLinear";
}

/***********************************************
 *  Helper methods
 ***********************************************/

/** check an estimation against a spline by sampling nPoints in argbounds */
bool TestExprPiecewiseLinear::sampleEstimation(SCIP_EXPR* expr, int nPoints, Bound argbound, EstimationData estimation)
{

   auto pcwlin = SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr));
   SCIP_Real stepsize = (argbound.second - argbound.first) / (double) nPoints;
   if (stepsize < 1e-6)
      stepsize = 1; /* Sampling only once */

   int localErrors = 0;
   SCIP_Real invalidPoint = 0;
   for (SCIP_Real argval = argbound.first; argval <= argbound.second; argval += stepsize)
   {
      if (!verifyEstimation(pcwlin, estimation, argval, tolerance_))
      {
         if (localErrors == 0)
            invalidPoint = argval;
         ++localErrors;
      }
   }

   /* Evaluate found problems  */
   if (localErrors == 0)
   {
      ++nSuccess_;
      SCIPdbgMsg("Estimation is valid at %i sampled points \n", nPoints);
      return true;
   }
   else
   {
      nError_ += localErrors;
      SCIPdebugMessage("Estimation is invalid at %i of %i sampled points first invalid point is x=%f\n", localErrors, nPoints, invalidPoint);
      return false;
   }
}

/** Verify an estimation by comparging it to spline at argval */
bool TestExprPiecewiseLinear::verifyEstimation(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval, SCIP_Real tolerance)
{

   /* Evalute estimate*/
   SCIP_Real estimationval = estimation.constant + estimation.coefficient * argval;
   /* Evalute lookup */
   SCIP_Real funcval = (*pcwlin)(argval);

   SCIPdbgMsg("verifying (argval = %f, funcval = %1.16e, estimationval = %1.16e, delta = %e)\n", argval, funcval, estimationval, funcval - estimationval);

   if (   (estimation.overestimate && funcval > estimationval + tolerance)
      || (!estimation.overestimate && funcval + tolerance < estimationval  )
   )
   {
      SCIPdebugMessage("!!!!! Estimation cuts off function at %e\n", argval);
      SCIPdebugMessage("failed:  (argval = %1.16e, funcval = %1.16e, estimationval = %1.16e, delta = %e)\n", argval, funcval, estimationval, funcval - estimationval);
      //SCIPdebugMessage("(funcval = %f, estimationval = %f, delta = %e)\n", funcval, estimationval, funcval - estimationval);
      assert(false);
      return false;
   }
   else
   {
      SCIPdbgMsg("Estimation is valid at %f\n", argval);
      return true;
   }

}

/** Return difference between estimation and spline function values at argval */
double TestExprPiecewiseLinear::compareEstimationSpline(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval)
{
   /* Evalute estimate*/
   SCIP_Real estimationval = estimation.constant + estimation.coefficient * argval;
   /* Evalute lookup */
   //@todo: Evaluate properly
   spline::BSplineCurve<1, SCIP_Real>::interval_t interval = pcwlin->findInterval( argval );
   SCIP_Real funcval = pcwlin->evaluate<0>(argval, interval);
   return funcval - estimationval;
}

/** Compute the estimation and return it */
EstimationData TestExprPiecewiseLinear::getEstimation(SCIP_EXPR* pcwlin, SCIP_Real argvals, Bound argbound, bool overestimate)
{

   SCIP_RETCODE retcode;
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = argbound.first;
   argbounds.sup = argbound.second;

   retcode = SCIPexprEstimateUser(pcwlin, SCIPinfinity(scip_), &argvals, &argbounds, overestimate, &coeffs, &constant, &success);
   assert(retcode == SCIP_OKAY);

   SCIPdbgMsg("Got estimation: %f*x + %f\n", coeffs, constant);

   EstimationData estimationData;
   estimationData.coefficient = coeffs;
   estimationData.constant = constant;
   estimationData.overestimate = overestimate;


   //SCIP_CALL( estimateSafe(overestimate, argbound.first, argbound.second, argvals, argvals[0], x1, x2, y1, y2, estimator, coeffs, constant) );

   return estimationData;
}

/** Return a string listing the test data for argbounds(boundidx) */
std::string EstimatorTestData::toString(int boundidx)
{
   std::ostringstream oss;
   oss << "Test " << label << std::endl;
   oss << "xvals:        " << sdscip::Vector::vec2string(points.first,std::string()) << std::endl;
   oss << "yvals:        " << sdscip::Vector::vec2string(points.second,std::string()) << std::endl;
   oss << "argbounds:    (" << std::to_string(argbounds[boundidx].first) << ", " << std::to_string(argbounds[boundidx].second) << ")" << std::endl;
   oss << "argval:       " << std::to_string(argvals[boundidx]) << std::endl;
   oss << "overestimate: " << ( overestimate ? std::string("true") : std::string("false"));

   return oss.str();
}

/** Create a std::string describing the estimation */
std::string TestExprPiecewiseLinear::estimationToString(EstimationData estimation)
{
   std::ostringstream oss;
   oss << (estimation.overestimate ? "over" : "under") << "estimation: " << std::scientific <<  estimation.coefficient << "x + " << estimation.constant;
   return oss.str();
}

/** Evaluate estimation at x */
SCIP_Real TestExprPiecewiseLinear::evaluateEstimation(EstimationData estimation, SCIP_Real x)
{
   return estimation.constant + estimation.coefficient * x;
}

/** Check the given over- or underestimation at all knots of the spline */
bool TestExprPiecewiseLinear::sampleEstimationAtKnots(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, Bound argbound, int &nerrors, SCIP_Real tolerance)
{
   int olderrors = nerrors;
   int checkedknots = 0;
   std::vector<SCIP_Real> invalidPoints;
   /* Iterate knots and check if knot is in interval */
   auto coeffs = pcwlin->getCoefficients();

   /* Check at knots within the interval */
   for (auto it = coeffs.begin(); it < coeffs.end(); ++it)
   {
      int i = it - coeffs.begin();
      SCIP_Real argval = pcwlin->getKnot(i);

      /* If this knot is inside of considered interval */
      if (argval >= argbound.first && argval <= argbound.second)
      {
         if (!verifyEstimation(pcwlin, estimation, argval, tolerance))
         {
            ++nerrors;
            invalidPoints.push_back(argval);
         }
         ++checkedknots;
      }
   }

   /* Check at argbounds */
   SCIPdbgMsg("Verifying estimation at lower argbound, x = %e\n", argbound.first);
   if (!verifyEstimation(pcwlin, estimation, argbound.first, tolerance))
   {
      ++nerrors;
      invalidPoints.push_back(argbound.first);
   }
   ++checkedknots;
   SCIPdbgMsg("3 y(x2) =  %e\n", (*pcwlin)(1e14));

   SCIPdbgMsg("Verifying estimation at upper argbound, x = %e\n",argbound.second);

   if (!verifyEstimation(pcwlin, estimation, argbound.second, tolerance))
   {
      ++nerrors;
      invalidPoints.push_back(argbound.second);
   }
   ++checkedknots;

   /* Evaluate found problems  */
   if (nerrors == olderrors)
   {
      SCIPdbgMsg("Estimation is valid at %i sampled knots\n", checkedknots);
      return true;
   }
   else
   {
      SCIPdebugMessage("Estimation is invalid at %i of %i sampled knots: %s\n", nerrors, checkedknots, sdscip::Vector::vec2string(invalidPoints, std::string("")).c_str());
      return false;
   }
}

/** Check the vector of xVals for coinciding points and remove one of two coinciding
 *  points from xvals and yvals
  */
void TestExprPiecewiseLinear::removeCoincidingPoints(ValVec &xvals, ValVec &yvals)
{
   double mindist = 1e-3;
   //SCIPdbgMsg("removing coinciding points from:\n");
   //SCIPdbgMsg("xvec: %s\n",sdscip::Vector::vec2string(xvals, std::string()).c_str());
   //SCIPdbgMsg("yvec: %s\n",sdscip::Vector::vec2string(yvals, std::string()).c_str());
   double lastx = xvals[0];
   for( auto it = xvals.begin() + 1; it != xvals.end(); /*++it*/)
   {
      int i = it - xvals.begin();
      if (*it - lastx <= mindist)
      {
         it = xvals.erase(it);
         yvals.erase (yvals.begin()+i);
         i = it - xvals.begin();
      }
      else
      {
         ++it;
         lastx = *it;
      }
   }
}

/** Print the tests currently in the testData */
void TestExprPiecewiseLinear::printTests()
{
   SCIPinfoMessage(scip_, NULL,  "Printing Tests in Testdata\n");

   for(auto it = testsData_.begin(); it != testsData_.end(); ++it)
   {
      auto data = *it;
      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int i = valsIt - data.argvals.begin();
         SCIPinfoMessage(scip_, NULL,  "%s\n", it->toString(i).c_str());
      }
   }
}

/** Delete all tests from the test data */
void TestExprPiecewiseLinear::clearTests()
{
   testsData_.clear();
}

/** Run tests currently in the testData */
void TestExprPiecewiseLinear::runTests()
{
   for(auto it = testsData_.begin(); it != testsData_.end(); ++it)
   {
      auto data = *it;
      //SCIPdebugMessage("\n\n========================================================\n");
      SCIPdebugMessage("Running test %s\n", data.label.c_str());

      SCIP_EXPR* expr = createExprPiecewiseLinear(data);

      SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );

      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int i = valsIt - data.argvals.begin();
         SCIPdbgMsg("Considering argval %f, argbounds [%f,%f]\n", *valsIt, data.argbounds[i].first, data.argbounds[i].second);

         EstimationData estimation = getEstimation(expr, *valsIt, data.argbounds[i], data.overestimate);

         SCIPdbgMsg("got estimation %s\n", estimationToString(estimation).c_str());

         bool sampleValid = sampleEstimation(expr, 50, data.argbounds[i], estimation);
         bool knotsValid = sampleEstimationAtKnots( SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr)), estimation, data.argbounds[i], nError_, tolerance_);

         if( sampleValid && knotsValid )
            nSuccess_++;
         else
         {
            SCIPdebugMessage("test failed, printing test data:\n%s \n", data.toString(i).c_str());
            SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL);
         }
         ++nExecutedTests_;
      }
      SCIPexprFreeDeep(SCIPblkmem(subscip_), &expr);
   }
   clearTests();
}

/** Create an Expression Piecewise Linear in blockmem of subscip_
 *  SCIPexprFreeDeep must be called to free memory
 */
SCIP_EXPR* TestExprPiecewiseLinear::createExprPiecewiseLinear(EstimatorTestData data)
{
   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(data.points.first, data.points.second);

   retcode = SCIPexprCreate(SCIPblkmem(subscip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   std::string identifier(data.label);
   identifier.resize(10);

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   assert(retcode == SCIP_OKAY);

   return expr;

}

/***********************************************
 *  Methods adding tests to testdata
 ***********************************************/

/** generate random tests and add to testdata */
void TestExprPiecewiseLinear::addRandomEstimatorTests(int nTests, Bound xrange, Bound yrange, bool integerDataPoints, int nArgBounds)
{
   srand (1);
   int maxnpoints = 10;
   double xwidth = xrange.second - xrange.second;
   double ywidth = yrange.second - yrange.second;

   for (int i = 0; i < nTests; ++i)
   {
      //SCIPdbgMsg("\n\n========================================================\n");
      //SCIPdbgMsg("generating test random_%i\n",i);
      EstimatorTestData odata;
      int npoints = getRandInt(1, maxnpoints);
      //SCIPdbgMsg("Generating lookup with %i points\n", npoints);

      /* Generate xvals, yvals */
      std::vector<double> xvals;
      std::vector<double> yvals;
      for (int j = 0; j < npoints; ++j)
      {
         if (integerDataPoints)
         {
            xvals.push_back((double) getRandInt(xrange.first, xrange.second));
            yvals.push_back((double) getRandInt(yrange.first, yrange.second));
         }
         else
         {
            xvals.push_back(getRandDouble(xrange.first, xrange.second));
            yvals.push_back(getRandDouble(yrange.first, yrange.second));
         }
      }

      std::sort(xvals.begin(), xvals.end());

      removeCoincidingPoints(xvals, yvals);

      std::string out;
      for( auto x : xvals )
      {
         out = out + std::string(", ") + std::to_string(x);
      }
      //SCIPdbgMsg("xvals: %s\n", out.c_str());
      out = std::string();
      for( auto y : yvals )
      {
         out = out + std::string(", ") + std::to_string(y);
      }
      //SCIPdbgMsg("yvals: %s\n", out.c_str());

      /* Only continue of two or more points left */
      if (xvals.size() <= 1)
         continue;

      odata.points = std::make_pair( xvals, yvals );

      /* Generate argbounds */

      ywidth = 2*ywidth;
      for (int j = 0; j < nArgBounds; ++j) {
         double a = 0;
         double b = 0;
         while(std::abs(a-b) <= 1)
         {
            a = getRandInt(xrange.first - 0.5*xwidth, xrange.second+ 0.5*xwidth );
            b = getRandInt(xrange.first - 0.5*xwidth, xrange.second + 0.5*xwidth );
         }

         odata.argbounds.emplace_back(std::make_pair(std::min(a,b), std::max(a,b)));
         odata.argvals.emplace_back(getRandDouble(std::min(a,b), std::max(a,b)));
      }
      for( auto it = odata.argbounds.begin(); it != odata.argbounds.end(); ++it)
      {
         //int k = it - odata.argbounds.begin();
         //SCIPdbgMsg("argval: %f, argbounds (%f,%f)\n", data.argvals[k], it->first, it->second );
      }
      EstimatorTestData udata = odata;
      odata.overestimate = true;
      odata.label = std::string("random_over_") + std::to_string(i);
      udata.overestimate = false;
      udata.label = std::string("random_under_") + std::to_string(i);
      testsData_.emplace_back(odata);
      testsData_.emplace_back(udata);
   }
}

/** Add numerics tests to the testdata */
void TestExprPiecewiseLinear::addNumericsEstimatorTests()
{
   /* Problem with rounding errors: underestimating from minus infinity to 4 */
   {
      EstimatorTestData data;
      data.label = std::string("numerics_under_minus_inf");
      data.points = std::make_pair(
          std::vector<double>{0  , 4.0}
         ,std::vector<double>{1.2, 0.0}
      );

      data.argbounds = BoundVec{
                   std::make_pair(-1e14, 5)
      };
      data.argvals = ValVec{3};
      data.overestimate = false;

      testsData_.emplace_back(data);
   }
}

/** Add some manually designed estimator tests to the EstimatorTestData */
void TestExprPiecewiseLinear::addManualEstimatorTests()
{
   /* A problem lookup from world2_from70 */
   if( true )
   {
      EstimatorTestData data;
      data.label = std::string("world2_from70_overest");
      data.points = std::make_pair(
          std::vector<double>{0,0.25,0.5,0.75,1}
         ,std::vector<double>{0,0.15,0.5,0.85,1}
      );

      data.argbounds = BoundVec{
                   std::make_pair(-4.9835643974591581e-01,8.5808151653009113e-01)
      };
      data.argvals = ValVec{8.5808151653009102e-01};
      data.overestimate = true;

      testsData_.push_back(data);

      data.overestimate = false;
      data.label = std::string("world2_from70_underest");
      testsData_.emplace_back(data);
   }


   /* Simple concave function with two lines */
   if( false )
   {
      EstimatorTestData data;
      data.label = std::string("concave_two_lines");
      data.points = std::make_pair(
          std::vector<double>{0, 1}
         ,std::vector<double>{0, 2}
      );

      data.argbounds = BoundVec{
                   /*std::make_pair(0, 2)
                  ,*/std::make_pair(-1, 2)
                  /*,std::make_pair(-2, 2)
                  ,std::make_pair(-2, 2.5) */
      };
      data.argvals = ValVec{0};
      data.overestimate = false;


      testsData_.emplace_back(data);
   }
}

/***********************************************
 *  Methods running tests
 ***********************************************/

/** Add the manual tests to the testdata and then check estimators by
 *  sampling points in the interval
 *  */
void TestExprPiecewiseLinear::runEstimatorManualTests()
{
   addManualEstimatorTests();
   runTests();
}

/** add and run the numerics tests */
void TestExprPiecewiseLinear::runEstimatorNumericsTests()
{
   addNumericsEstimatorTests();
   runTests();
}

/** add and run tests generated using random numbers */
void TestExprPiecewiseLinear::runEstimatorRandomTests()
{
   int ntests = 1e5;
   int argvalspertest = 10;

   addRandomEstimatorTests(ntests, std::make_pair(-100.0, 100.0), std::make_pair(-100.0, 100.0), false, argvalspertest);
   runTests();
}

/* Check the lookup from world2 model */
void TestExprPiecewiseLinear::runWorldLookup()
{
   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;
   SCIP_VAR* arg;
   bool overestimate = true;

   std::vector<double> xvals = {0, 0.25, 0.5, 0.75, 1};
   std::vector<double> yvals = {0, 0.15, 0.5, 0.85, 1};

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(xvals, yvals);

   SCIPcreateVarBasic(subscip_, &arg, "argument", -SCIPinfinity(scip_), SCIPinfinity(scip_), 0, SCIP_VARTYPE_CONTINUOUS);
   retcode = SCIPexprCreate(SCIPblkmem(subscip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   char identifier[7] = "lookup";

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );
   assert(retcode == SCIP_OKAY);
   SCIP_Real argvals;
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = -4.9835643974591581e-01;
   argbounds.sup = 8.5808151653009113e-01;
   argvals = 8.5808151653009102e-01;


   retcode = SCIPexprEstimateUser(expr, SCIPinfinity(scip_), &argvals, &argbounds, overestimate, &coeffs, &constant, &success);
   test(retcode == SCIP_OKAY);

   EstimationData estimation;
   estimation.coefficient = coeffs;
   estimation.constant = constant;
   estimation.overestimate = overestimate;
   int nerrors(0);
   sampleEstimationAtKnots(SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr)), estimation, std::make_pair(SCIPintervalGetInf( argbounds ), SCIPintervalGetSup( argbounds )), nerrors, 0.0);

   ++nExecutedTests_;
   nError_ += nerrors;

   SCIPexprFreeDeep(SCIPblkmem(subscip_), &expr);
   SCIPreleaseVar(subscip_, &arg);

}

/* Check the lookup from world2 model */
void TestExprPiecewiseLinear::runEvalWorldLookup()
{
   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;
   SCIP_VAR* arg;
   bool overestimate = true;

   std::vector<double> xvals = {0, 1, 2, 3, 4} ;

   std::vector<double> yvals = {0, 1, 1.8, 2.4, 2.7};

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(xvals, yvals);

   SCIPcreateVarBasic(subscip_, &arg, "argument", -SCIPinfinity(scip_), SCIPinfinity(scip_), 0, SCIP_VARTYPE_CONTINUOUS);
   retcode = SCIPexprCreate(SCIPblkmem(subscip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   char identifier[7] = "lookup";

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );
   assert(retcode == SCIP_OKAY);
   SCIP_Real argvals;
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = -1e100;
   argbounds.sup = 1e100;
   SCIP_Interval val;

   retcode = SCIPexprEvalInt(expr, SCIPinfinity(scip_), &argbounds, NULL, &val);
   SCIPdbgMsg("Evaluated lookup in [%e,%e], returned [%f, %f]\n", argbounds.inf, argbounds.sup, val.inf, val.sup);
   assert(retcode == SCIP_OKAY);

   testEqual(val.inf, 0 );
   testEqual(val.sup, 2.7 );


   ++nExecutedTests_;
   SCIPexprFreeDeep(SCIPblkmem(subscip_), &expr);
   SCIPreleaseVar(subscip_, &arg);
}

/** Method running all tests of this class */
void TestExprPiecewiseLinear::runAll()
{
   runWorldLookup();
   runEstimatorManualTests();
   runEstimatorNumericsTests();
   runEstimatorRandomTests();
}

}
