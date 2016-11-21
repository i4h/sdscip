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

/**@file    TestEstimatorTypes.cpp
 * @brief   Test for safe estimator types
 * @author  Ingmar Vierhaus
 *
 */


#include "TestEstimatorTypes.h"

namespace sdscip
{

TestEstimatorTypes::TestEstimatorTypes(SCIP* scip) :
   TestExprPiecewiseLinear(scip)
{}

TestEstimatorTypes::~TestEstimatorTypes()
{ }

/** Identify this test */
std::ostream& TestEstimatorTypes::toString(std::ostream& strm) const {
  return strm << "TestEstimatorTypes";
}


/** Add tests of safe estimators E1 and E3 */
void TestEstimatorTypes::addE1E3tests()
{
   /* A numerically difficult case where lb is -inf. */
   if (true) {
      /* Underestimating from minus infinity to 4 and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available */
      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_minusinf");
      data.points = std::make_pair(
       std::vector<double>{0.0, 4.0}
      ,std::vector<double>{1.2, 0.0}
     );
      data.overestimate = false;
      data.x1 = -1e14;
      data.x2 = 4;
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
      /* |\ub x| - |lb x| = 4 - 1 = 3 =  3 so we dont know which estiamtor is tighter */

      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.label = std::string("safe_estimators_under_over_minus1`");
      typeTestsData_.push_back(data);
   }

   /* A numerically difficult case where ub is +inf. */
   if (true) {
      /* Underestimating from minus 4 to infinty and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available */

      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_over_plusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, 0.0}
      ,std::vector<double>{ 0.0, 1.2}
     );
      data.overestimate = false;
      data.x1 = -4;
      data.x2 = 1e14;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3, SAFE_ESTIMATOR_TYPE_1});

      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds.push_back(std::make_pair(-4, 1e14));
      typeTestsData_.push_back(data);

      /* |\ub x| - |lb x| = 5 - 1e14 \approx - 1e14 <= 3 so E1 should be tighter */


      /* Add some tests where lb moves orders of magnitude in negative direction */
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

      /* Add some tests where ub moves in negative direction */
      data.argbounds = BoundVec{ std::make_pair(-4, 1e4) };
      data.x2 = 1e4;
      data.label = std::string("safe_estimators_under_over_pluslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-4, 10) };
      data.x2 = 10;
      data.label = std::string("safe_estimators_under_over_plus10");
      typeTestsData_.push_back(data);

   }

}

/** Add tests of safe estimators E2 and E4 */
void TestEstimatorTypes::addE2E4tests()
{

   /* A numerically difficult case where lb is -inf. */
   if (true) {
      /* Underestimating from minus infinity to -2 and checking at -3
       * Points are on the inside, so only estimators 1 through 4 are available
       * since lb < 0, ub < 0 E2 is always the best estimator */

      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_under_under_minusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, -1.0}
      ,std::vector<double>{ 1.2,  0.0}
     );
      data.overestimate = false;
      data.x1 = -1e14;
      data.x2 = -1;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_2, SAFE_ESTIMATOR_TYPE_4});

      double base = 5.5;
      for (int exponent = 0; -1.0*std::pow(base,exponent) >= (-4 - 1e14) + 10; ++exponent) {
            data.argvals.push_back(-1.0*std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-1e14, -2));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_2);
      }
      typeTestsData_.push_back(data);

      /* "Reset" */
      data.argvals = ValVec({-3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_2});
      data.argbounds = BoundVec{ std::make_pair(-1e4, -2) };

      /* Add some tests where lb moves in positive direction */
      data.x1 = -1e4;
      data.label = std::string("safe_estimators_under_under_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-10, -2) };
      data.x1 = -10;
      data.label = std::string("safe_estimators_under_under_minus10");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-1, -2) };
      data.x1 = -2;
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_2});
      data.label = std::string("safe_estimators_under_under_minus1");
      typeTestsData_.push_back(data);
   }

   /* A numerically difficult case where ub is +inf. */
   if (true) {
      /* Underestimating from 2 to infinty and checking at 3
       * Points are on the inside, so only estimators 1 through 4 are available
       * since lb > 0, ub > 0,  E4 is always the best estimator */

      EstimatorTypeTestData data;
      data.label = std::string("safe_estimators_over_over_plusinf");
      data.points = std::make_pair(
       std::vector<double>{1.0, 4.0}
      ,std::vector<double>{0.0,  1.2}
     );
      data.overestimate = false;
      data.x1 = 1;
      data.x2 = 1e14;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_4, SAFE_ESTIMATOR_TYPE_2});

      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_4});
      data.argbounds.push_back(std::make_pair(2, 1e14));
      typeTestsData_.push_back(data);


      /* Add some tests where lb moves orders of magnitude in positive direction */
      double base = 5.5;
      for (int exponent = 0; std::pow(base,exponent) <= (1e14 - 5) - 10; ++exponent) {
            data.argvals.push_back(std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(2, 1e14));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_4);
      }
      typeTestsData_.push_back(data);

      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_4});
      data.argbounds = BoundVec{ std::make_pair(2, 1e14) };

      /* Add some tests where lb moves in negative direction */
      data.argbounds = BoundVec{ std::make_pair(1e4, 1e14) };
      data.x1 = 1e4;
      data.label = std::string("safe_estimators_over_over_pluslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair( 10, 1e14) };
      data.x1 = 10;
      data.label = std::string("safe_estimators_over_over_plus10");
      typeTestsData_.push_back(data);

   }

}

/** Add tests of safe estimators E5 and E6 */
void TestEstimatorTypes::addE5E6tests()
{

   /* A numerically difficult case where lb is -inf. */
   if (true) {
      /* Underestimating from minus infinity to -2 and checking at -3
       * Right point is on ub, so E5 is available
       * we expect to always select E5 */

      EstimatorTypeTestData data;
      data.label = std::string("e5_safe_estimators_under_under_minusinf");
      data.points = std::make_pair(
       std::vector<double>{-4.0, -1.0}
      ,std::vector<double>{ 1.2,  0.0}
     );
      data.overestimate = false;
      data.x1 = -1e14;
      data.x2 = -2;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_2, SAFE_ESTIMATOR_TYPE_4, SAFE_ESTIMATOR_TYPE_5});
      data.e5valid = true;;

      double base = 5.5;
      for (int exponent = 0; -1.0*std::pow(base,exponent) >= (-4 - 1e14) + 10; ++exponent) {
            data.argvals.push_back(-1.0*std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(-1e14, -2));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_5);
      }
      typeTestsData_.push_back(data);

      /* "Reset" */
      data.argvals = ValVec({-3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_5});
      data.argbounds = BoundVec{ std::make_pair(-1e4, -2) };

      /* Add some tests where lb moves in positive direction */
      data.x1 = -1e4;
      data.label = std::string("e5_safe_estimators_under_under_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-10, -2) };
      data.x1 = -10;
      data.label = std::string("e5_safe_estimators_under_under_minus10");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(-3, -2) };
      data.x1 = -3;
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_5});
      data.label = std::string("e5_safe_estimators_under_under_minus1");
      typeTestsData_.push_back(data);

   }

   /* A numerically difficult case where ub is +inf. */
   if (true) {
      /* Underestimating from 2 to infinty and checking at 3
       * Left point is on lb, so E6 is available
       * we expect to always select E6 */

      EstimatorTypeTestData data;
      data.label = std::string("e6_safe_estimators_over_over_plusinf");
      data.points = std::make_pair(
       std::vector<double>{1.0, 4.0}
      ,std::vector<double>{0.0,  1.2}
     );
      data.overestimate = false;
      data.x1 = 1;
      data.x2 = 1e14;
      data.validTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_4, SAFE_ESTIMATOR_TYPE_2, SAFE_ESTIMATOR_TYPE_6});
      data.e6valid = true;

      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_6});
      data.argbounds.push_back(std::make_pair(2, 1e14));
      typeTestsData_.push_back(data);


      /* Add some tests where lb moves orders of magnitude in positive direction */
      double base = 5.5;
      for (int exponent = 0; std::pow(base,exponent) <= (1e14 - 5) - 10; ++exponent) {
            data.argvals.push_back(std::pow(base,exponent ));
            data.argbounds.push_back(std::make_pair(2, 1e14));
            data.bestTypes.push_back(SAFE_ESTIMATOR_TYPE_6);
      }
      typeTestsData_.push_back(data);

      return;


      /* "Reset" */
      data.argvals = ValVec({3.0});
      data.bestTypes = std::vector<SAFE_ESTIMATOR>({SAFE_ESTIMATOR_TYPE_3});
      data.argbounds = BoundVec{ std::make_pair(2, 1e14) };

      /* Add some tests where lb moves in positive direction */
      data.argbounds = BoundVec{ std::make_pair(2, 1e4) };
      data.x1 = 1e4;
      data.label = std::string("e6_safe_estimators_over_over_minuslarge");
      typeTestsData_.push_back(data);

      data.argbounds = BoundVec{ std::make_pair(2, 10) };
      data.x1 = 10;
      data.label = std::string("e6_safe_estimators_over_over_minus10");
      typeTestsData_.push_back(data);

   }

}

/** Execute the tests defined in typeTestsData_ vector */
void TestEstimatorTypes::runTests()
{
   for(auto it = typeTestsData_.begin(); it != typeTestsData_.end(); ++it)
   {
      EstimatorTypeTestData data = *it;
      for( auto valsIt = data.argvals.begin(); valsIt != data.argvals.end(); ++valsIt)
      {
         int oldErrors = nError_;
         SCIPdebugMessage("======= Testing %s with argval: %e =========\n",data.label.c_str(), *valsIt);
         int i = valsIt - data.argvals.begin();
         SCIPdbg( std::cout << data.toString(i) );
         std::map<SAFE_ESTIMATOR, double> errsAtX;

         /* Get all estimators that are expected to be valid */
         for (SAFE_ESTIMATOR type : data.validTypes)
         {
            EstimationData estimation;
            estimation.overestimate = data.overestimate;
            SCIP_RETCODE retcode;

            /* Get piecewise linear for y-values and verification of estimation */
            SCIP_EXPR* expr = createExprPiecewiseLinear(data);
            SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );
            auto pcwlin = SCIPexprPiecewiseLinearGetSpline(SCIPexprGetUserData(expr));

            SCIPdbgMsg("evaluating at x1: f( %f) = %f\n", data.x1, (*pcwlin)(data.x1));
            SCIPdbgMsg("evaluating at x2: f( %f) = %f\n", data.x2, (*pcwlin)(data.x2));


            /* Create estimation (defining points selected by hand) */
            retcode = estimateSafe(
               data.overestimate, data.argbounds[i].first, data.argbounds[i].second, data.argvals[i],
               data.x1, data.x2,
               (*pcwlin)(data.x1),
               (*pcwlin)(data.x2),
               (SAFE_ESTIMATOR) type,
               &estimation.coefficient,
               &estimation.constant
            );
            assert(retcode == SCIP_OKAY);

            SCIPdbgMsg("Got estimation %s\n", estimationToString(estimation).c_str());

            /* Sample at points */
            int localOldErrors = nError_;
            sampleEstimationAtKnots(pcwlin, estimation, data.argbounds[i], nError_, tolerance_);

            /* Check tightness at argounbd */
            errsAtX[type]  = std::abs(compareEstimationSpline(pcwlin, estimation, data.argvals[i]));

            if (nError_ != localOldErrors)
            {
               SCIPwarningMessage(scip_, "Estimator %i is INVALID but should be valid\n", type);
            }
            SCIPexprFreeDeep(SCIPblkmem(subscip_), &expr);

         } /* Close loop over estimator types */

         /* Find tightest estimator */
         SAFE_ESTIMATOR selectedEstimator = selectEstimator(data.overestimate, data.argbounds[0].first, data.argbounds[0].second, data.argvals[0], data.x1, data.x2, data.e5valid, data.e6valid );
         auto tightestEstimatorIt = findSmallestErrorIt(errsAtX);

         SCIPdebugMessage("Tightest estimator is type %i with delta = %e, selected is %i\n", tightestEstimatorIt->first, tightestEstimatorIt->second, selectedEstimator);
         if (data.bestTypes[i] != selectedEstimator)
         {
            nError_++;
            SCIPwarningMessage(scip_,"ERROR: Estimator %i was selected, but expected to select %i\n", selectedEstimator, data.bestTypes[i]);
         }

         if (tightestEstimatorIt->first != selectedEstimator)
         {
            double diffWithTightest = ( errsAtX.find(selectedEstimator) == errsAtX.end() ? 1e20 : (errsAtX[selectedEstimator] - tightestEstimatorIt->second) );
            /* If the difference between estimators is ~0 dont complain */
            if (std::abs(diffWithTightest) >= zeroTolerance_)
            {
               nError_++;
               SCIPwarningMessage(scip_,"WARNING: Estimator %i was selected, but tightest estimator was %i (by %e)\n", selectedEstimator, tightestEstimatorIt->first, diffWithTightest);
            }
         }

         if (oldErrors == nError_)
            nSuccess_ ++;
         nExecutedTests_++;
      }  /* Close loop over sets of argbounds/argval */
   }
}

/** Find the estimator with the smalles errAtX in the map */
std::map<SAFE_ESTIMATOR, double>::const_iterator TestEstimatorTypes::findSmallestErrorIt(std::map<SAFE_ESTIMATOR, double> errsAtX)
{
      return std::min_element(errsAtX.begin(), errsAtX.end(),
         [](const std::pair<SAFE_ESTIMATOR, double>& p1, const std::pair<SAFE_ESTIMATOR, double>& p2) {
         return p1.second < p2.second; });
}

/** Run all tests */
void TestEstimatorTypes::runAll()
{
   addE1E3tests();

   addE2E4tests();

   addE5E6tests();

   runTests();
}


}
