//#define SCIP_DBG
#define SCIP_DEBUG
/*
 * TestEstimatorTypes.cpp
 *
 *  Created on: 02/16/2016
 *      Author: Ingmar Vierhaus
 */

#include "TestEstimatorTypes.hpp"

namespace ctrl
{

TestEstimatorTypes::TestEstimatorTypes(SCIP* scip) :
   TestExprPiecewiseLinear(scip)
{
}

TestEstimatorTypes::~TestEstimatorTypes()
{
   // TODO Auto-generated destructor stub
}

void TestEstimatorTypes::addE1E3Tests()
{
   /* A numerically difficult case where lb is -inf. */
   if (true ) {
      /* Problem with rounding errors: underestimating from minus infinity to 4 and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available */
      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_minusinf");
      data.points = std::make_pair(
       std::vector<double>{0.0, 4.0}
      ,std::vector<double>{1.2, 0.0}
     );
      data.overestimate = false;
      data.x1 = -1e14;
      data.y1 = 1.2;
      data.x2 = 4;
      data.y2 = 0;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3, SAFE_ESTIMATOR_TYPE_1});
      /* |\ub x| - |lb x| = 5 - 1e14 \approx - 1e14 <= 3 so E1 should be tighter */

      double base = 5.5;
      for (int exponent = 0; -1.0*std::pow(base,exponent) >= (5 - 1e14) + 10; ++exponent) {
            data.argvals.push_back(-1.0*std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-1e14, 5));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_1);
      }
      typeTestsData_.push_back(data);


      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_1});
      data.argbounds = BoundVec{ std::make_pair(-1e4, 5) };

      /* Add some tests where lb moves in positive direction */
      data.x1 = -1e4;
      data.label = std::string("safe_estimators_under_over_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-10, 5) };
      data.x1 = -10;
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-1, 5) };
      data.x1 = -1;
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);
   }

   /* A numerically difficult case where ub is +inf. */
   if (true) {
      /* Problem with rounding errors: underestimating from minus 4 to infinty and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available */

      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_plusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, 0.0}
      ,std::vector<double>{0.0,  1.2}
     );
      data.overestimate = false;
      data.x1 = -4;
      data.y1 = 0;
      data.x2 = 1e14;
      data.y2 = 1.2;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3, SAFE_ESTIMATOR_TYPE_1});

      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds.push_back(std::make_pair(-4, 1e14));
      typeTestsData_.push_back(data);

      /* |\ub x| - |lb x| = 5 - 1e14 \approx - 1e14 <= 3 so E1 should be tighter */


      /* Add some tests where lb moves orders of magnitude in positive direction */
      double base = 5.5;
      for (int exponent = 0; std::pow(base,exponent) <= (1e14 - 5) - 10; ++exponent) {
            data.argvals.push_back(std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-4, 1e14));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_3);
      }
      typeTestsData_.push_back(data);

      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds = BoundVec{ std::make_pair(-4, 1e14) };

      /* Add some tests where lb moves in positive direction */
      data.argbounds = BoundVec{ std::make_pair(-4, 1e4) };
      data.x1 = 1e4;
      data.label = std::string("safe_estimators_under_over_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-4, 10) };
      data.x1 = 10;
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);

   }

}

void TestEstimatorTypes::addE2E4Tests()
{
   /* A numerically difficult case where lb is -inf. */
   if (true ) {
      /* Problem with rounding errors: underestimating from minus infinity to -4 and checking at -3
       * Points are on the inside, so only estimators 1 through 4 are available */
      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_minusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, -1.0}
      ,std::vector<double>{ 1.2,  0.0}
     );
      data.overestimate = false;
      data.x1 = -1e14;
      data.y1 = 1.2;
      data.x2 = -1;
      data.y2 = 0;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_2, SAFE_ESTIMATOR_TYPE_4});
      /* |\ub x| - |lb x| = 5 - 1e14 \approx - 1e14 <= 3 so E1 should be tighter */

      double base = 5.5;
      for (int exponent = 0; -1.0*std::pow(base,exponent) >= (5 - 1e14) + 10; ++exponent) {
            data.argvals.push_back(-1.0*std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-1e14, 5));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_1);
      }
      typeTestsData_.push_back(data);


      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_1});
      data.argbounds = BoundVec{ std::make_pair(-1e4, 5) };

      /* Add some tests where lb moves in positive direction */
      data.x1 = -1e4;
      data.label = std::string("safe_estimators_under_over_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-10, 5) };
      data.x1 = -10;
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-1, 5) };
      data.x1 = -1;
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);
   }

   /* A numerically difficult case where ub is +inf. */
   if (true) {
      /* Problem with rounding errors: underestimating from minus 4 to infinty and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available */

      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_plusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, 0.0}
      ,std::vector<double>{0.0,  1.2}
     );
      data.overestimate = false;
      data.x1 = -4;
      data.y1 = 0;
      data.x2 = 1e14;
      data.y2 = 1.2;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3, SAFE_ESTIMATOR_TYPE_1});

      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds.push_back(std::make_pair(-4, 1e14));
      typeTestsData_.push_back(data);

      /* |\ub x| - |lb x| = 5 - 1e14 \approx - 1e14 <= 3 so E1 should be tighter */


      /* Add some tests where lb moves orders of magnitude in positive direction */
      double base = 5.5;
      for (int exponent = 0; std::pow(base,exponent) <= (1e14 - 5) - 10; ++exponent) {
            data.argvals.push_back(std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-4, 1e14));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_3);
      }
      typeTestsData_.push_back(data);

      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds = BoundVec{ std::make_pair(-4, 1e14) };

      /* Add some tests where lb moves in positive direction */
      data.argbounds = BoundVec{ std::make_pair(-4, 1e4) };
      data.x1 = 1e4;
      data.label = std::string("safe_estimators_under_over_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-4, 10) };
      data.x1 = 10;
      data.label = std::string("safe_estimators_under_over_minus10");
      typeTestsData_.push_back(data);

   }

}

void TestEstimatorTypes::runTests()
{
   for(auto it = typeTestsData_.begin(); it != typeTestsData_.end(); ++it)
   {
      EstimatorTypeTestData data = *it;
      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int oldErrors = nErrors_;
         SCIPdebugMessage("\n");
         SCIPdebugMessage("======= Testing %s with argval: %e =========\n",data.label.c_str(), *valsIt);
         int i = valsIt - data.argvals.begin();
         std::map<SAFE_ESTIMATOR, double> errsAtX;
         /* Get all valid esimators and validate. Check hat the selected one is the tightest */
         /* for (int j = 1; j <= 4; j++) */
         /* Get all estimators that are expected to be valid */
         for (SAFE_ESTIMATOR type : data.validTypes)
         {
            //auto type = SAFE_ESTIMATOR_TYPE_1;
            //SAFE_ESTIMATOR type = (SAFE_ESTIMATOR) j;
            //SCIPdebugMessage("============================================\n");
            //SCIPdebugMessage("Checking out Estimator E_%i ----------------------\n", type);
            EstimationData estimation;
            estimation.overestimate = data.overestimate;
            SCIP_RETCODE retcode;

            /* Create estimation (defining points selected by hand) */
            retcode = estimateSafe(
               data.overestimate, data.argbounds[i].first, data.argbounds[i].second, data.argvals[i],
               data.x1, data.x2,
               data.y1, data.y2,
               (SAFE_ESTIMATOR) type,
               &estimation.coefficient,
               &estimation.constant
            );
            assert(retcode == SCIP_OKAY);

            /* Print estimation and values at defining points */
            SCIPdbgMsg("estimation: %s\n",estimationToString(estimation).c_str());
            SCIPdbgMsg("(e(x1), e(x2)) = (%e, %e)\n", evaluateEstimation(estimation, data.argbounds[i].first), evaluateEstimation(estimation, data.argbounds[i].second));

            /* Get picewise linear for verification of estimation */
            SCIP_EXPR* expr = createExprPiecewiseLinear(data);
            SCIPdbgMsg("Points:\n");
            SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );
            SCIPdbg( SCIPinfoMessage(scip_, NULL, "\n") );
            auto pcwlin = SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr));

            /* Sample at points */
            int localOldErrors = nErrors_;
            sampleEstimationAtKnots(pcwlin, estimation, data.argbounds[i], nErrors_);

            /* Check tightness at argounbd */
            errsAtX[type]  = std::abs(compareEstimationSpline(pcwlin, estimation, data.argvals[i]));

            //SCIPdebugMessage("found %i errors, checked %i knots \n", nErrors_);
            if (nErrors_ != localOldErrors)
            {
               SCIPdebugMessage("Estimator %i is INVALID but should be valid\n", type);
               assert(false);
            }
            //if (nErrors_)
         } /* Close loop over estimator types */

         /* Find tightest estimator */
         SAFE_ESTIMATOR selectedEstimator = selectEstimator(data.overestimate, data.argbounds[0].first, data.argbounds[0].second, data.argvals[0], data.x1, data.x2, false, false );
         auto tightestEstimatorIt = findSmallestErrorIt(errsAtX);

         SCIPdebugMessage("Tightest estimator is type %i with delta = %e, selected is %i\n", tightestEstimatorIt->first, tightestEstimatorIt->second, selectedEstimator);
         if (data.bestTypes[i] != selectedEstimator)
         {
            nErrors_++;
            SCIPdebugMessage("ERROR: Estimator %i was selected, but expected to select %i\n", selectedEstimator, data.bestTypes[i]);
         }

         if (tightestEstimatorIt->first != selectedEstimator)
         {
            double diffWithTightest = ( errsAtX.find(selectedEstimator) == errsAtX.end() ? 1e20 : (errsAtX[selectedEstimator] - tightestEstimatorIt->second) );
            SCIPdebugMessage("WARNING: Estimator %i was selected, but tightest estimator was %i (by %e)\n", selectedEstimator, tightestEstimatorIt->first, diffWithTightest);
         }

         if (oldErrors == nErrors_)
            nSuccess_ ++;
         nTests_++;
      }  /* Close loop over sets of argbounds/argval */
   }
}

std::map<SAFE_ESTIMATOR, double>::const_iterator TestEstimatorTypes::findSmallestErrorIt(std::map<SAFE_ESTIMATOR, double> errsAtX)
{
      return std::min_element(errsAtX.begin(), errsAtX.end(),
         [](const std::pair<SAFE_ESTIMATOR, double>& p1, const std::pair<SAFE_ESTIMATOR, double>& p2) {
         return p1.second < p2.second; });
}


void TestEstimatorTypes::runAll()
{
   SCIPdbgMsg("running all\n");
   addE1E3Tests();
   runTests();
}


}
