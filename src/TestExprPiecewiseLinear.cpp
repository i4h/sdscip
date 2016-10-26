//#define SCIP_DBG
//#define SCIP_DEBUG
/*
 * TestExprPiecewiseLinear.cpp
 *
 *  Created on: 02/16/2016
 *      Author: Ingmar Vierhaus
 */

#include "TestExprPiecewiseLinear.hpp"

namespace ctrl
{

std::string EstimatorTestData::toString(int boundidx)
{
   std::ostringstream oss;
   oss << "xvals:        " << SDgeom::Vector::vec2string(points.first,std::string()) << std::endl;
   oss << "yvals:        " << SDgeom::Vector::vec2string(points.second,std::string()) << std::endl;
   oss << "argbounds:    (" << std::to_string(argbounds[boundidx].first) << ", " << std::to_string(argbounds[boundidx].second) << ")" << std::endl;
   oss << "argval:       " << std::to_string(argvals[boundidx]) << std::endl;
   oss << "overestimate: " << ( overestimate ? std::string("true") : std::string("false"));

   return oss.str();
}

TestExprPiecewiseLinear::TestExprPiecewiseLinear(SCIP* scip) :
   TestSDplugin(scip)
{
}

TestExprPiecewiseLinear::~TestExprPiecewiseLinear()
{
   // TODO Auto-generated destructor stub
}


/* Creates a series of lookups, and estimations, then tests the validity of the estimation by sampling the considered interval */
void TestExprPiecewiseLinear::runEstimatorManualTests()
{
   addManualEstimatorTests();

   //std::vector<double> xVals = {0, 0.25, 0.5, 0.75, 1};
   //std::vector<double> yVals = {0, 0.15, 0.5, 0.85, 1};
   bool overestimate = true;
   for(auto data : testsData_)
   {
      SCIPdebugMessage("\n\n========================================================\n");
      SCIPdebugMessage("Running test %s\n", data.label.c_str());

      SCIP_EXPR* expr = createExprPiecewiseLinear(data);

      SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL);

      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int i = valsIt - data.argvals.begin();

         SCIPdebugMessage("Considering argval %f, argbounds [%f,%f]\n", *valsIt, data.argbounds[i].first, data.argbounds[i].second);

         EstimationData estimation = getEstimation(expr, *valsIt, data.argbounds[i], overestimate);

         bool valid = sampleEstimation(expr, 50, data.argbounds[i], estimation);
         assert(valid);
      }
   }
}

void TestExprPiecewiseLinear::runEstimatorNumericsTests()
{
   addNumericsEstimatorTests();
   runTests();
}

std::string TestExprPiecewiseLinear::estimationToString(EstimationData estimation)
{
   std::ostringstream oss;
   oss << "estimation: " << std::scientific <<  estimation.coefficient << "x + " << estimation.constant;
   return oss.str();
}

SCIP_Real TestExprPiecewiseLinear::evaluateEstimation(EstimationData estimation, SCIP_Real x)
{
   return estimation.constant + estimation.coefficient * x;
}


void TestExprPiecewiseLinear::runTests()
{
   for(auto it = testsData_.begin(); it != testsData_.end(); ++it)
   {
      auto data = *it;
      //SCIPdebugMessage("\n\n========================================================\n");
      SCIPdebugMessage("Running test %s\n", data.label.c_str());

      SCIP_EXPR* expr = createExprPiecewiseLinear(data);

      //SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL);

      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int i = valsIt - data.argvals.begin();

         SCIPdbgMsg("Considering argval %f, argbounds [%f,%f]\n", *valsIt, data.argbounds[i].first, data.argbounds[i].second);

         EstimationData estimation = getEstimation(expr, *valsIt, data.argbounds[i], data.overestimate);

         if (sampleEstimationAtKnots( SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr)), estimation, data.argbounds[i], nErrors_))
            //if( sampleEstimation(expr, 50, data.argbounds[i], estimation))
         {
            nSuccess_++;
         }
         else
         {
            SCIPdebugMessage("test failed, printing test data:\n%s \n", data.toString(i).c_str());
            //SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL);
         }

         ++nTests_;
         break;
      }
      //break;
   }
}

void TestExprPiecewiseLinear::runEstimatorRandomTests()
{
   int ntests = 1e5;
   int argvalspertest = 10;

   addRandomEstimatorTests(ntests, std::make_pair(-100.0, 100.0), std::make_pair(-100.0, 100.0), false, argvalspertest);
   runTests();
}

bool TestExprPiecewiseLinear::sampleEstimationAtKnots(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, Bound argbound, int &nerrors)
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
         SCIPdbgMsg("Verfiying at knot %i, x = %f\n",i,argval);
         SCIP_Real funcval = *it;

         SCIP_Real estimationval = estimation.constant + estimation.coefficient * argval;

         if (   (estimation.overestimate && funcval > estimationval + 1e-12)
            || (!estimation.overestimate && funcval + 1e-12 < estimationval  )
         )
         {
            SCIPdebugMessage("!!!!! Estimation cuts off function at %f, \n(funcval = %f, estimationval = %f, delta = %e)\n", argval, funcval, estimationval, funcval - estimationval);

            invalidPoints.push_back(argval);
            ++nerrors;
         }
         ++checkedknots;
      }
   }

   /* Check at argbounds */
   SCIPdbgMsg("Verifying estimation at lower argbound, x = %e\n", argbound.first);
   if (!verifyEstimation(pcwlin, estimation, argbound.first))
   {
      ++nerrors;
      invalidPoints.push_back(argbound.first);
   }
   ++checkedknots;
   SCIPdbgMsg("Verifying estimation at upper argbound, x = %e\n",argbound.second);

   if (!verifyEstimation(pcwlin, estimation, argbound.second))
   {
      ++nerrors;
      invalidPoints.push_back(argbound.second);
   }
   ++checkedknots;

   /* Evaluate found problems  */
   if (nerrors == olderrors)
   {
      SCIPdebugMessage("Estimation is valid at %i sampled knots\n", checkedknots);
      return true;
   }
   else
   {
      SCIPdebugMessage("Estimation is invalid at %i of %i sampled knots: %s\n", nerrors, checkedknots, SDgeom::Vector::vec2string(invalidPoints, std::string("")).c_str());
      return false;
   }
}


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

void TestExprPiecewiseLinear::removeCoincidingPoints(ValVec &xvals, ValVec &yvals)
{
   double mindist = 1e-3;
   SCIPdbgMsg("removing coinciding points from:\n");
   SCIPdbgMsg("xvec: %s\n",SDgeom::Vector::vec2string(xvals, std::string()).c_str());
   SCIPdbgMsg("yvec: %s\n",SDgeom::Vector::vec2string(yvals, std::string()).c_str());
   double lastx = xvals[0];
   for( auto it = xvals.begin() + 1; it != xvals.end(); /*++it*/)
   {
      int i = it - xvals.begin();
      SCIPdbgMsg("i = %i, last x was %f, current x is %f, delta = %e\n", i, lastx, *it, *it - lastx);
      if (*it - lastx <= mindist)
      {
         SCIPdbgMsg("erasing point (%f, %f)\n", *it, yvals[i]);
         it = xvals.erase(it);
         yvals.erase (yvals.begin()+i);
         i = it - xvals.begin();
         SCIPdbgMsg("done, i = %i, current point  is (%f, %f), delta with lastx = %f is %e\n", i, *it, yvals[i], lastx, *it - lastx);
      }
      else
      {
         ++it;
         lastx = *it;
      }
   }
}

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

void TestExprPiecewiseLinear::addManualEstimatorTests()
{
   /* A problem lookup from world2_from70 */
   if( true )
   {
      EstimatorTestData data;
      data.label = std::string("concave_two_lines");
      data.points = std::make_pair(
          std::vector<double>{0,0.25,0.5,0.75,1}
         ,std::vector<double>{0,0.15,0.5,0.85,1}
      );

      data.argbounds = BoundVec{
                   std::make_pair(-4.9835643974591581e-01,8.5808151653009113e-01)
      };
      data.argvals = ValVec{8.5808151653009102e-01};

      testsData_.emplace_back(data);
   }


   /* Simple concave function with two lines */
   if( true )
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

      testsData_.emplace_back(data);
   }
}


EstimationData TestExprPiecewiseLinear::getEstimation(SCIP_EXPR* pcwlin, SCIP_Real argvals, Bound argbound, bool overestimate)
{
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = argbound.first;
   argbounds.sup = argbound.second;

   SCIPdbgMsg("Got estimation: %f*x + %f\n", coeffs, constant);

   EstimationData estimationData;
   estimationData.coefficient = coeffs;
   estimationData.constant = constant;
   estimationData.overestimate = overestimate;

   return estimationData;
}

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
      if (!verifyEstimation(pcwlin, estimation, argval))
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
      nErrors_ += localErrors;
      SCIPdebugMessage("Estimation is invalid at %i of %i sampled points first invalid point is x=%f\n", localErrors, nPoints, invalidPoint);
      return false;
   }
}

bool TestExprPiecewiseLinear::verifyEstimation(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval)
{
   double tolerance = 1e-9;
   /* Evalute estimate*/
   SCIP_Real estimationval = estimation.constant + estimation.coefficient * argval;
   /* Evalute lookup */
   spline::BSplineCurve<1, SCIP_Real>::interval_t interval = pcwlin->findInterval( argval );
   SCIP_Real funcval = pcwlin->evaluate<0>(argval, interval);

   if (   (estimation.overestimate && funcval > estimationval - tolerance)
      || (!estimation.overestimate && funcval + tolerance < estimationval  )
   )
   {
      SCIPdebugMessage("!!!!! Estimation cuts off function at %e\n", argval);
      SCIPdebugMessage("(funcval = %f, estimationval = %f, delta = %e)\n", funcval, estimationval, funcval - estimationval);
      return false;
   }
   else
   {
      SCIPdbgMsg("Estimation is valid at %f\n", argval);
      SCIPdbgMsg("(argval = %f, funcval = %f, estimationval = %f, delta = %e)\n", argval, funcval, estimationval, funcval - estimationval);
      return true;
   }

}

double TestExprPiecewiseLinear::compareEstimationSpline(boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > pcwlin, EstimationData estimation, double argval)
{
   /* Evalute estimate*/
   SCIP_Real estimationval = estimation.constant + estimation.coefficient * argval;
   /* Evalute lookup */
   spline::BSplineCurve<1, SCIP_Real>::interval_t interval = pcwlin->findInterval( argval );
   SCIP_Real funcval = pcwlin->evaluate<0>(argval, interval);
   return funcval - estimationval;
}


SCIP_EXPR* TestExprPiecewiseLinear::createExprPiecewiseLinear(EstimatorTestData data)
{
   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(data.points.first, data.points.second);

   retcode = SCIPexprCreate(SCIPblkmem(scip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   std::string identifier(data.label);
   identifier.resize(10);

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   assert(retcode == SCIP_OKAY);

   return expr;

}

void TestExprPiecewiseLinear::runWorldLookup() {


   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;
   SCIP_VAR* arg;

   std::vector<double> xvals = {0, 0.25, 0.5, 0.75, 1};
   std::vector<double> yvals = {0, 0.15, 0.5, 0.85, 1};

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(xvals, yvals);

   SCIPcreateVarBasic(subscip_, &arg, "argument", -SCIPinfinity(scip_), SCIPinfinity(scip_), 0, SCIP_VARTYPE_CONTINUOUS);
   retcode = SCIPexprCreate(SCIPblkmem(scip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   char identifier[7] = "lookup";

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL);
   assert(retcode == SCIP_OKAY);
   SCIP_Real argvals;
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = -4.9835643974591581e-01;
   argbounds.sup = 8.5808151653009113e-01;
   argvals = 8.5808151653009102e-01;


   retcode = SCIPexprEstimateUser(expr, SCIPinfinity(scip_), &argvals, &argbounds, TRUE, &coeffs, &constant, &success);

   //(SCIP_Real infinity, SCIP_USEREXPRDATA* data, int nargs, SCIP_Real* argvals, SCIP_INTERVAL* argbounds, SCIP_Bool overestimate, SCIP_Real* coeffs, SCIP_Real* constant, SCIP_Bool *success)



}

void TestExprPiecewiseLinear::runAll()
{
   SCIPdbgMsg("running all\n");
   runWorldLookup();
}


}
