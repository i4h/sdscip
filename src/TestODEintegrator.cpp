#define SCIP_DBG
#define SCIP_DEBUG
/*
 * TestODEintegrator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "TestODEintegrator.h"
#include "PointRateEvaluator.h"


namespace ctrl
{

TestODEintegrator::TestODEintegrator(SCIP* scip) :
   scip_(scip)
   ,nSuccess_(0)
   ,nErrors_(0)
{
   SCIPcreate(&subscip_);
   SCIPcreateProbBasic(subscip_, "TestODEintegrator memory container");
}

TestODEintegrator::~TestODEintegrator()
{
   // TODO Auto-generated destructor stub
   SCIPfreeProb(subscip_);
   SCIPfree(&subscip_);
}

int TestODEintegrator::getNsuccess()
{
   return nSuccess_;
}

int TestODEintegrator::getNerrors()
{
   return nErrors_;
}

void TestODEintegrator::runAll()
{
   SCIPdbgMsg("running all\n");

   runConstRateEvaluatorTest();
   runSimTests();
   runSBtests();

   SCIPdebugMessage("Finished running all, %i success, %i errors\n",nSuccess_, nErrors_);
}

void TestODEintegrator::runSimTests()
{
   SCIPdbgMsg("running SimTests\n");
   runConstRateEvaluatorTest();
   runPredatorPreySimTest();
   runPredatorPreySimIntermediateStepsTest();
   SCIPdebugMessage("Finished running SimTests, %i success, %i errors\n",nSuccess_, nErrors_);
}

void TestODEintegrator::runSBtests()
{
   SCIPdbgMsg("running SBtests\n");
   runPredatorPreySBsimTest();
   runPredatorPreySBcontrolTest();
   runPredatorPreySBglobalBoundsTest();
   runPredatorPreySBboundsTest();
   SCIPdebugMessage("Finished running SBtests, %i success, %i errors\n",nSuccess_, nErrors_);
}

std::vector<SCIP_EXPR*> TestODEintegrator::getXdotPredatorPrey()
{

   int nStates = 2;
   int nControls = 1;

   SCIP_Real a = 1;
   SCIP_Real b = 1;
   SCIP_Real c = 1;
   SCIP_Real d = 1;

   /* Values and variables representing one point in time */
   std::vector<SCIP_VAR*> x(nStates);
   std::vector<SCIP_EXPR*> exprX(nStates);
   std::vector<SCIP_EXPR*> xDot(nStates);
   std::vector<SCIP_VAR*> z(nControls);
   std::vector<SCIP_EXPR*> exprZ(nControls);

   SCIPdbgMsg("creating vars and expressions for state vars\n");
   for( int i = 0; i < nStates; ++i)
   {
      (SCIPcreateVarBasic(subscip_, &(x[i]), "", 0, 0, 0, SCIP_VARTYPE_CONTINUOUS));
      (SCIPexprCreate(SCIPblkmem(subscip_), &exprX[i], SCIP_EXPR_VARIDX, i) );
   }

   SCIPdbgMsg("creating vars and expressions for control vars\n");
   for( int i = 0; i < nControls; ++i)
   {
      (SCIPcreateVarBasic(subscip_, &(z[i]), "", 0, 0, 0, SCIP_VARTYPE_CONTINUOUS));
      (SCIPexprCreate(SCIPblkmem(subscip_), &exprZ[i], SCIP_EXPR_VARIDX, nStates + i) );
   }
   /* Building expression \dot x */
   {
      //eq_x(t+1) .. x(t+1) =e= x(t) + dt*(a*x(t) - b*y(t)*x(t) - z_c(t));
      SCIP_EXPR* term1;
      //( SCIPexprCreate(SCIPblkmem(subscip), &term1, SCIP_EXPR_LINEAR, 1, &(exprX[0]), &a));
      ( SCIPexprCreateLinear(SCIPblkmem(subscip_), &term1, 1, &(exprX[0]), &a, 0) );

      SCIP_EXPR* term2;
      SCIP_EXPR* quadTerm;
      ( SCIPexprCreate(SCIPblkmem(subscip_), &quadTerm, SCIP_EXPR_MUL, exprX[0], exprX[1]));
      SCIP_EXPR* exprB;
      ( SCIPexprCreate(SCIPblkmem(subscip_), &exprB, SCIP_EXPR_CONST, b));
      ( SCIPexprCreate(SCIPblkmem(subscip_), &term2, SCIP_EXPR_MUL, exprB, quadTerm));


      SCIP_EXPR* sum1;
      ( SCIPexprCreate(SCIPblkmem(subscip_), &sum1, SCIP_EXPR_MINUS, term1, term2));

      ( SCIPexprCreate(SCIPblkmem(subscip_), &(xDot[0]), SCIP_EXPR_MINUS, sum1, exprZ[0]));
   }
   {
      //eq_y(t+1) .. y(t+1) =e= y(t) + dt*(-d*y(t) + c*y(t)*x(t));
      SCIP_EXPR* term1;
      //( SCIPexprCreate(SCIPblkmem(subscip), &term1, SCIP_EXPR_LINEAR, 1, &(exprX[0]), &a));
      ( SCIPexprCreateLinear(SCIPblkmem(subscip_), &term1, 1, &(exprX[1]), &d, 0) );

      SCIP_EXPR* term2;
      SCIP_EXPR* quadTerm;
      ( SCIPexprCreate(SCIPblkmem(subscip_), &quadTerm, SCIP_EXPR_MUL, exprX[0], exprX[1]));
      SCIP_EXPR* exprC;
      ( SCIPexprCreate(SCIPblkmem(subscip_), &exprC, SCIP_EXPR_CONST, c));
      ( SCIPexprCreate(SCIPblkmem(subscip_), &term2, SCIP_EXPR_MUL, exprC, quadTerm));

      ( SCIPexprCreate(SCIPblkmem(subscip_), &(xDot[1]), SCIP_EXPR_MINUS, term2, term1) );
   }

#ifdef SCIP_DBG
   SCIPdbgMsg("done creating expressions for xDot\n");
   for (int i = 0; i < nStates; ++i)
   {
      SCIPinfoMessage(subscip_, NULL,"x_%i: ",i);
      SCIPexprPrint(xDot[i], SCIPgetMessagehdlr(subscip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(subscip_, NULL,"\n");
   }
#endif
   return xDot;
}

std::vector<std::string> TestODEintegrator::getTestDiscretizations()
{

   std::vector<std::string> discretizations;
   if (true)
      discretizations.push_back(std::string("euler"));
   else
   {
      discretizations.push_back(std::string("rk2"));
      discretizations.push_back(std::string("heun"));
      discretizations.push_back(std::string("rk4"));
   }
   return discretizations;
}


void TestODEintegrator::runConstRateEvaluatorTest()
{
   SCIPdbgMsg("Testing ConstRateEvaluator\n");

   int nIntermediateSteps(1);
   SCIP_Real dt(0.1);
   std::vector<std::string> discretizations = getTestDiscretizations();

   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;

      for (int nStates = 1; nStates < 4; ++nStates)
      {
         SCIPdbgMsg("===================================\n");
         SCIPdbgMsg("===================================\n");
         SCIPdbgMsg("performing test in %i dimensions\n",nStates);
         PointODEintegrator integrator(scip_, discretization, dt, nIntermediateSteps, nStates, 0, 0, PointRateEvaluator::RATE_EVALUATOR_CONST);
         //SCIPdbgMsg("%s\n",integrator.toString().c_str());
         std::vector<SCIP_Real> x(nStates);

         /* Perform a single euler step using the integrator */
         std::vector<SCIP_Real> states(nStates, 0);
         integrator.setInitial(0, states);
         for (int i = 0; i < 10; ++i)
         {
            //SCIPdbgMsg("performing step\n");
            integrator.step();
            //SCIPdbgMsg("%s\n",integrator.statesToString().c_str());
            //SCIPdbgMsg("t = %f\n",integrator.getT());
            //SCIPdbgMsg("x[0] = %f\n",integrator.getState(0));
         }

         int myErrors = 0;
         for (int i = 0; i < nStates; ++i)
         {
            SCIP_Real expected = (i+1) * 1.0;
            if( !SCIPisEQ(scip_, integrator.getState(i),expected))
            {
               SCIPdebugMessage("error testing %s, nStates = %i, component %i is %f, should be %f\n", discretization.c_str(), nStates, i, integrator.getState(i), expected);
               myErrors++;
            }
            nErrors_ += (myErrors != 0);
            nSuccess_ += (myErrors == 0);
         }
      }
   }
}



void TestODEintegrator::runPredatorPreySimTest()
{
   SCIPdbgMsg("Testing SimRateEvaluator\n");

   /* Preliminaries */
   int nControls(1);
   int nStates(2);
   int nAlgebraic(0);

   std::vector<std::string> discretizations = getTestDiscretizations();

   /* Define expected states at t=10 */
   std::map<std::string, std::vector<SCIP_Real> > expected;
   expected[std::string("euler")] = std::vector<SCIP_Real>({3.0184038896, 0.8491271047});
   expected[std::string("rk2")] = std::vector<SCIP_Real>({1.804516169580897,1.716766283019321});
   expected[std::string("rk3")] = std::vector<SCIP_Real>({1.809220737292751, 1.701127207025758});
   expected[std::string("heun")] = std::vector<SCIP_Real>({1.809052450595596, 1.701331008445153});
   expected[std::string("rk4")] = std::vector<SCIP_Real>({1.809579258454664,1.701056739966050});

   /* Get xDot for predator prey as first test model */
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();
   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing sim test for predator prey with %s scheme\n",discretization.c_str());

      int nSteps = 100;
      /* Initialize and configure ODEintegrator */
      PointODEintegrator integrator(scip_, discretization, 0.1, 1, nStates, nAlgebraic, nControls, PointRateEvaluator::RATE_EVALUATOR_SIM);
      integrator.setXdots(xDotPP);
      std::vector<SCIP_Real> x(nStates,0.5);
      std::vector<SCIP_Real> z(nControls,0);
      SCIP_Real t(0);
      integrator.setInitial(t, x, z);

      for (int i = 0; i < nSteps; ++i)
      {
         //SCIPdbgMsg("performing step\n");
         integrator.step();
         //SCIPdbgMsg("%s\n",integrator.statesToString().c_str());
         //SCIPdbgMsg("t = %f\n",integrator.getT());
         //SCIPdbgMsg("x[0] = %f\n",integrator.getState(0));
      }
      SCIPdbgMsg("%s\n",integrator.statesToString().c_str());

      /* Evaluate */
      {
         int myErrors(0);
         for (int i = 0; i < 2; ++i)
         {
            std::vector<SCIP_Real> expectedNow = expected[discretization];
            if (!SCIPisEQ(scip_,integrator.getState(i), expectedNow[i]))
            {
               SCIPdebugMessage("error testing %s, nStates = %i, component %i is %f, should be %f\n", discretization.c_str(), nStates, i, integrator.getState(i), expectedNow[i]);
               myErrors++;
            }
         }
         if (myErrors == 0)
            ++nSuccess_;
         else
            nErrors_ += myErrors;
      }
   }
   SCIPdbgMsg("Finished Testing SimRateEvaluator\n");
}

void TestODEintegrator::runPredatorPreySimIntermediateStepsTest()
{
   SCIPdbgMsg("Testing Intermediate Steps with PredatorPreySim\n");

   /* Preliminaries */
   int myErrors(0);
   int mySuccesses(0);
   int nControls(1);
   int nStates(2);
   int nAlgebraic(0);
   std::vector<std::string> discretizations = getTestDiscretizations();
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();

   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;
      std::vector<int> intermediateSteps = {2, 5, 10, 50 };
      //const std::vector<int> intermediateSteps = {2 };
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing intermediate steps test for predator prey with %s scheme\n",discretization.c_str());

      int nTotalSteps = 1000;
      SCIP_Real dt(0.01);
      /* Initialize and configure master ODEintegrator */
      PointODEintegrator masterIntegrator(scip_, discretization, dt, 1, nStates, nAlgebraic, nControls, PointRateEvaluator::RATE_EVALUATOR_SIM);
      masterIntegrator.setXdots(xDotPP);
      std::vector<SCIP_Real> x(nStates,0.5);
      std::vector<SCIP_Real> z(nControls,0);
      SCIP_Real t(0);
      masterIntegrator.setInitial(t, x, z);

      /* Initialize and configure slave ODEintegrators */
      std::vector<PointODEintegrator> slaveIntegrators;
      std::vector<int> slaveIntegratorCounts(intermediateSteps.size(),0);

      for (auto &is : intermediateSteps)
      {
         SCIPdbgMsg("creating integrator making %i intermediate steps\n", is);
         slaveIntegrators.push_back(PointODEintegrator(scip_, discretization, dt*is, is, nStates, nAlgebraic, nControls, PointRateEvaluator::RATE_EVALUATOR_SIM));
         slaveIntegrators.back().setXdots(xDotPP);
         slaveIntegrators.back().setInitial(t, x, z);
      }

      for (int i = 0; i < nTotalSteps; ++i)
      {
         masterIntegrator.step();
         for (int j = 0; j < (int) intermediateSteps.size(); ++j)
         {
            /* Find out if its time for a step for this slave */
            if (++slaveIntegratorCounts[j] == intermediateSteps[j])
            {
               slaveIntegratorCounts[j] = 0;
               slaveIntegrators[j].step();
               /* States of this slaveIntegrator should be equal to master integrator */
               for (int k = 0; k < nStates; ++k)
               {
                  if (SCIPisEQ(scip_, slaveIntegrators[j].getState(k), masterIntegrator.getState(k)))
                     ++mySuccesses;
                  else
                  {
                     ++myErrors;
                     SCIPdebugMessage("error testing slaveIntegrator with %s scheme using %i intermediate Steps, component %i is %f, should be %f\n", discretization.c_str(), intermediateSteps[j], k, slaveIntegrators[j].getState(k), masterIntegrator.getState(k));
                  }
               }
            }
         }
      }
      SCIPdbgMsg("x_master(%f) = %s\n",masterIntegrator.getT(), masterIntegrator.statesToString().c_str());
   }
   nErrors_ += myErrors;
   nSuccess_ += mySuccesses;
   printf("Finished Testing Intermediate steps\n");
}

void TestODEintegrator::runPredatorPreySBsimTest()
{
   SCIPdbgMsg("running PredatorPreySBtest \n");
   int myErrors(0);
   int mySuccesses(0);
   /* Preliminaries */
   int nControls(1);
   int nStates(2);
   int nAlgebraic(0);
   int nIntermediateSteps(1);
   SCIP_Real dt(0.01);
   int nSteps = std::round(10 / dt);
   std::vector<std::string> discretizations = getTestDiscretizations();

   /* Get xDot for predator prey as first test model */
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();
   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      SCIP_Bool isPoint = true;
      std::string discretization = *it;
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing SB test for predator prey with %s scheme\n",discretization.c_str());

      SCIP_Real t0(0);
      /* Initialize and configure Interval ODEintegrator */
      IntervalODEintegrator integrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      integrator.setXdots(xDotPP);
      std::vector<SCIP_Interval> x_i;
      for( int i = 0; i < nStates; ++i)
      {
         SCIP_Interval x_i_i;
         x_i_i.inf = 0.5;
         x_i_i.sup = 0.5;
         x_i.push_back(x_i_i);
      }
      std::vector<SCIP_Interval> z_i(nControls);
      for( int i = 0; i < nControls; ++i)
      {
         SCIP_Interval z_i_i;
         z_i_i.inf = 0.0;
         z_i_i.sup = 0.0;
         z_i.push_back(z_i_i);
      }
      integrator.setInitial(t0, x_i, z_i);

      /* Initialize and configure simulation ODEintegrator */
      PointODEintegrator pointIntegrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls, PointRateEvaluator::RATE_EVALUATOR_SIM);
      pointIntegrator.setXdots(xDotPP);
      std::vector<SCIP_Real> x(nStates,0.5);
      std::vector<SCIP_Real> z(nControls,0);
      pointIntegrator.setInitial(t0, x, z);

      for (int i = 0; i < nSteps; ++i)
      {
         integrator.step();
         pointIntegrator.step();

         for (int k = 0; k < nStates; ++k)
         {
            SCIP_Interval state = integrator.getState(k);
            if (isPoint && !SCIPisEQ(scip_, state.inf, state.sup))
            {
               SCIPdebugMessage("warning testing IntervalIntegrator with %s scheme, x(t=%f,%i) = [%e, %e] is not a point (diff = %e)\n", discretization.c_str(), integrator.getT(), k, state.inf, state.sup, state.sup - state.inf);
               isPoint = false;
            }

            if (SCIPisLT(scip_, state.sup, pointIntegrator.getState(k)))
            {
               ++myErrors;
               SCIPdebugMessage("error testing intervalIntegrator with %s scheme, point state x(t=%f,%i)=%f is above interval state [%f, %f] by %e\n",
                  discretization.c_str(), integrator.getT(), k, pointIntegrator.getState(k), state.inf, state.sup, state.sup - pointIntegrator.getState(k));
            }
            else if (SCIPisGT(scip_,state.inf,pointIntegrator.getState(k)))
            {
               ++myErrors;
               SCIPdebugMessage("error testing intervalIntegrator with %s scheme, point state x(t=%f,%i)=%f is below interval state [%f, %f] by %e\n",
                  discretization.c_str(), integrator.getT(), k, pointIntegrator.getState(k), state.inf, state.sup, pointIntegrator.getState(k) - state.inf );
            }
            else
               ++mySuccesses;
         }
      }
      SCIPdbgMsg("intervalIntegrator: %s\n",integrator.statesToString().c_str());
      SCIPdbgMsg("pointIntegrator: %s\n",pointIntegrator.statesToString().c_str());
   }
   nErrors_ += myErrors;
   nSuccess_ += mySuccesses;
   SCIPdbgMsg("Finished PredatorPreySBtest\n");
}

void TestODEintegrator::runPredatorPreySBcontrolTest()
{
   SCIPdbgMsg("running PredatorPreySBcontrolTest \n");
   int myErrors(0);
   int mySuccesses(0);
   /* Preliminaries */
   int nControls(1);
   int nStates(2);
   int nAlgebraic(0);
   int nIntermediateSteps(1);
   SCIP_Real dt(0.1);
   int nSteps = std::round(4 / dt);
   std::vector<std::string> discretizations = getTestDiscretizations();

   /* Get xDot for predator prey as first test model */
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();
   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing SB test for predator prey with %s scheme\n",discretization.c_str());

      SCIP_Real t0(0);
      /* Initialize and configure Interval ODEintegrator */
      IntervalODEintegrator integrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      integrator.setXdots(xDotPP);
      std::vector<SCIP_Interval> x_i;
      for( int i = 0; i < nStates; ++i)
      {
         SCIP_Interval x_i_i;
         x_i_i.inf = 0.5;
         x_i_i.sup = 0.5;
         x_i.push_back(x_i_i);
      }
      std::vector<SCIP_Interval> z_i;
      for( int i = 0; i < nControls; ++i)
      {
         SCIP_Interval z_i_i;
         z_i_i.inf = 0.0;
         z_i_i.sup = 0.1;
         z_i.push_back(z_i_i);
      }
      SCIPdbgMsg("z_i[0] = [%f,%f]\n",z_i[0].inf,z_i[0].sup);
      integrator.setInitial(t0, x_i, z_i);

      /* Initialize and configure simulation ODEintegrator */
      PointODEintegrator pointIntegrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls, PointRateEvaluator::RATE_EVALUATOR_SIM);
      pointIntegrator.setXdots(xDotPP);
      std::vector<SCIP_Real> x(nStates,0.5);
      std::vector<SCIP_Real> z(nControls,0);
      pointIntegrator.setInitial(t0, x, z);

      for (int i = 0; i < nSteps; ++i)
      {
         integrator.step();
         pointIntegrator.step();

         for (int k = 0; k < nStates; ++k)
         {
            SCIP_Interval state = integrator.getState(k);
            if (state.sup < pointIntegrator.getState(k) || state.inf > pointIntegrator.getState(k))
            {
               ++myErrors;
               SCIPdebugMessage("error testing intervalIntegrator with %s scheme, point state x(t=%f,%i) = %f is outside of interval state [%f, %f]\n",
                  discretization.c_str(), integrator.getT(), k, pointIntegrator.getState(k), state.inf, state.sup);
            }
            else
               ++mySuccesses;
         }
      }
      SCIPdbgMsg("pointIntegrator: %s\n",pointIntegrator.statesToString().c_str());
      SCIPdbgMsg("intervalIntegrator: %s\n",integrator.statesToString().c_str());
   }
   nErrors_ += myErrors;
   nSuccess_ += mySuccesses;
   SCIPdbgMsg("Finished PredatorPreySBcontrolTest\n");
}

void TestODEintegrator::runPredatorPreySBglobalBoundsTest()
{
   SCIPdbgMsg("running PredatorPreySBglobalBoundsTest \n");
   int myErrors(0);
   int mySuccesses(0);
   /* Preliminaries */
   int nControls(1);
   int nAlgebraic(0);
   int nStates(2);
   int nIntermediateSteps(1);
   SCIP_Real dt(0.1);
   int nSteps = std::round(4 / dt);
   std::vector<std::string> discretizations = getTestDiscretizations();

   /* Get xDot for predator prey as first test model */
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();
   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing SB test for predator prey with %s scheme\n",discretization.c_str());

      SCIP_Real t0(0);
      /* Initialize and configure Interval ODEintegrators */
      IntervalODEintegrator boundedIntegrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      boundedIntegrator.setXdots(xDotPP);
      IntervalODEintegrator integrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      integrator.setXdots(xDotPP);

      std::vector<SCIP_Interval> x_i;
      for( int i = 0; i < nStates; ++i)
      {
         SCIP_Interval x_i_i;
         x_i_i.inf = 0.5;
         x_i_i.sup = 0.5;
         x_i.push_back(x_i_i);
      }
      std::vector<SCIP_Interval> z_i;
      for( int i = 0; i < nControls; ++i)
      {
         SCIP_Interval z_i_i;
         z_i_i.inf = 0.0;
         z_i_i.sup = 0.1;
         z_i.push_back(z_i_i);
      }
      SCIPdbgMsg("z_i[0] = [%f,%f]\n",z_i[0].inf,z_i[0].sup);
      integrator.setInitial(t0, x_i, z_i);
      boundedIntegrator.setInitial(t0, x_i, z_i);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(0, SCIP_BOUNDTYPE_LOWER, 0.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(1, SCIP_BOUNDTYPE_LOWER, 0.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(0, SCIP_BOUNDTYPE_UPPER, 3.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(1, SCIP_BOUNDTYPE_UPPER, 3.0);

      for (int i = 0; i < nSteps; ++i)
      {
         SCIPdbgMsg("stepping integrator\n");
         integrator.step();
         SCIPdbgMsg("stepping bounded integrator\n");
         boundedIntegrator.step();

         for (int k = 0; k < nStates; ++k)
         {
            SCIP_Interval state = integrator.getState(k);
            SCIP_Interval boundedState = boundedIntegrator.getState(k);
            if (boundedState.sup > state.sup || boundedState.inf < state.inf)
            {
               ++myErrors;
               SCIPdebugMessage("error testing intervalIntegrator with %s scheme, bounded state is worse than unbounded state\n",
                  discretization.c_str());
            }
            else
               ++mySuccesses;
         }
      }
      SCIPdbgMsg("boundedIntegrator: %s\n",boundedIntegrator.statesToString().c_str());
      SCIPdbgMsg("intervalIntegrator: %s\n",integrator.statesToString().c_str());
   }
   nErrors_ += myErrors;
   nSuccess_ += mySuccesses;
   SCIPdbgMsg("Finished PredatorPreySBglobalBoundsTest\n");
}

void TestODEintegrator::runPredatorPreySBboundsTest()
{
   SCIPdbgMsg("running PredatorPreySBboundsTest \n");
   int myErrors(0);
   int mySuccesses(0);
   /* Preliminaries */
   int nControls(1);
   int nAlgebraic(0);
   int nStates(2);
   int nIntermediateSteps(1);
   SCIP_Real dt(0.1);
   int nSteps = std::round(4 / dt);
   std::vector<std::string> discretizations = getTestDiscretizations();

   /* Get xDot for predator prey as first test model */
   std::vector<SCIP_EXPR*> xDotPP = getXdotPredatorPrey();
   for( auto it = discretizations.begin(); it != discretizations.end(); ++it)
   {
      std::string discretization = *it;
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("Performing SB test for predator prey with %s scheme\n",discretization.c_str());

      SCIP_Real t0(0);
      /* Initialize and configure Interval ODEintegrators */
      IntervalODEintegrator boundedIntegrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      boundedIntegrator.setXdots(xDotPP);
      IntervalODEintegrator integrator(scip_, discretization, dt, nIntermediateSteps, nStates, nAlgebraic, nControls);
      integrator.setXdots(xDotPP);

      std::vector<SCIP_Interval> x_i;
      for( int i = 0; i < nStates; ++i)
      {
         SCIP_Interval x_i_i;
         x_i_i.inf = 0.5;
         x_i_i.sup = 0.5;
         x_i.push_back(x_i_i);
      }
      std::vector<SCIP_Interval> z_i;
      for( int i = 0; i < nControls; ++i)
      {
         SCIP_Interval z_i_i;
         z_i_i.inf = 0.0;
         z_i_i.sup = 0.1;
         z_i.push_back(z_i_i);
      }
      SCIPdbgMsg("z_i[0] = [%f,%f]\n",z_i[0].inf,z_i[0].sup);
      integrator.setInitial(t0, x_i, z_i);
      boundedIntegrator.setInitial(t0, x_i, z_i);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(0, SCIP_BOUNDTYPE_LOWER, 0.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(1, SCIP_BOUNDTYPE_LOWER, 0.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(0, SCIP_BOUNDTYPE_UPPER, 3.0);
      boundedIntegrator.rateEvaluator()->addGlobalStateBound(1, SCIP_BOUNDTYPE_UPPER, 3.0);

      for (int i = 0; i < nSteps; ++i)
      {
         /* Create upper bound ub = 0.5 + t (will hit global bounds at t = 2.5) */
         SBrateEvaluator::BoundMap localBounds;
         for (int j = 0; j < 2; ++j)
            localBounds[SBrateEvaluator::BoundKey(j, SCIP_BOUNDTYPE_UPPER)] = i * dt + 0.5;

         SCIPdbgMsg("stepping integrator\n");
         integrator.step();
         SCIPdbgMsg("stepping bounded integrator\n");
         boundedIntegrator.step(localBounds);

         for (int k = 0; k < nStates; ++k)
         {
            SCIP_Interval state = integrator.getState(k);
            SCIP_Interval boundedState = boundedIntegrator.getState(k);
            if (boundedState.sup > state.sup || boundedState.inf < state.inf)
            {
               ++myErrors;
               SCIPdebugMessage("error testing intervalIntegrator with %s scheme, bounded state is worse than unbounded state\n",
                  discretization.c_str());
            }
            else
               ++mySuccesses;
         }
      }
      SCIPdbgMsg("boundedIntegrator: %s\n",boundedIntegrator.statesToString().c_str());
      SCIPdbgMsg("intervalIntegrator: %s\n",integrator.statesToString().c_str());
   }
   nErrors_ += myErrors;
   nSuccess_ += mySuccesses;
   SCIPdbgMsg("Finished PredatorPreySBboundsTest\n");
}

}
