#define SCIP_DEBUG
//{##header##}

/**@file   cppmain.cpp
 * @brief  main file for SD-SCIP
 * @author Ingmar Vierhaus
 *
 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include <iostream>

/* include SCIP components */
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"


/* include SD-SCIP components */
#include "ProbDataSD.h"
#include "PropOBRA.h"
#include "HeurSimODE.h"
#include "BranchControlFirst.h"
#include "PropODE.h"
#include "ReaderVOP.h"
#include "PresolConsGraph.h"
#include "Statistics.hpp"
#include "scip/scipdefplugins.h"
#include "scip/debug.h"

/* Include unit-testing classes */
#include "TestODEintegrator.h"
#include "TestSBrateEvaluator.h"
#include "TestBoundMap.h"
#include "TestExprPiecewiseLinear.hpp"
#include "TestEstimatorTypes.hpp"

using namespace scip;
using namespace std;


/** creates and runs a SCIP instance with default and TSP plugins */
static
SCIP_RETCODE runSCIP(
   int                        argc,          /**< number of arguments from the shell */
   char**                     argv           /**< array of shell arguments */
   )
{
   SCIP* scip = NULL;


   /*********
    * Setup *
    *********/

   /* initialize SCIP */
   SCIP_CALL ( SCIPcreate ( &scip ) );

   SCIP_CALL ( SCIPincludeDialogSDinit ( scip ) );
   SCIP_CALL ( SCIPincludeDialogSDprintStructure( scip ) );
   SCIP_CALL ( SCIPincludeDialogSDensureValidStructure( scip ) );
   SCIP_CALL ( SCIPincludeDialogSDrefreshStructure( scip ) );
   SCIP_CALL ( SCIPincludeDialogSDdoSomething( scip ) );
   SCIP_CALL ( SCIPincludeDialogSDdisable( scip ) );
   SCIP_CALL ( SCIPincludeDialogWriteTransprobSD ( scip ) );

   SCIP_CALL ( SCIPincludeConshdlrNonlinear ( scip ) ); /* nonlinear must be before linear, quadratic, abspower, and and due to constraint upgrading */
   SCIP_CALL ( SCIPincludeConshdlrQuadratic ( scip ) ); /* quadratic must be before linear due to constraint upgrading */
   SCIP_CALL ( SCIPincludeConshdlrLinear ( scip ) ); /* linear must be before its specializations due to constraint upgrading */

   /* include default SCIP plugins that dont disturb as at the moment*/
   SCIP_NLPI* nlpi;

   SCIP_CALL( SCIPincludeConshdlrAbspower(scip) ); /* absolute power needs to be after quadratic and nonlinear due to constraint upgrading */
   SCIP_CALL( SCIPincludeConshdlrAnd(scip) );
   SCIP_CALL( SCIPincludeConshdlrBivariate(scip) ); /* bivariate needs to be after quadratic and nonlinear due to constraint upgrading */
   SCIP_CALL( SCIPincludeConshdlrBounddisjunction(scip) );
   SCIP_CALL( SCIPincludeConshdlrConjunction(scip) );
   SCIP_CALL( SCIPincludeConshdlrCountsols(scip) );
   SCIP_CALL( SCIPincludeConshdlrCumulative(scip) );
   SCIP_CALL( SCIPincludeConshdlrDisjunction(scip) );
   SCIP_CALL( SCIPincludeConshdlrIndicator(scip) );
   SCIP_CALL( SCIPincludeConshdlrIntegral(scip) );
   SCIP_CALL( SCIPincludeConshdlrKnapsack(scip) );
   SCIP_CALL( SCIPincludeConshdlrLinking(scip) );
   SCIP_CALL( SCIPincludeConshdlrLogicor(scip) );
   SCIP_CALL( SCIPincludeConshdlrOr(scip) );
   SCIP_CALL( SCIPincludeConshdlrOrbitope(scip) );
   SCIP_CALL( SCIPincludeConshdlrPseudoboolean(scip) );
   SCIP_CALL( SCIPincludeConshdlrSetppc(scip) );
   SCIP_CALL( SCIPincludeConshdlrSOC(scip) ); /* SOC needs to be after quadratic due to constraint upgrading */
   SCIP_CALL( SCIPincludeConshdlrSOS1(scip) );
   SCIP_CALL( SCIPincludeConshdlrSOS2(scip) );
   SCIP_CALL( SCIPincludeConshdlrSuperindicator(scip) );
   SCIP_CALL( SCIPincludeConshdlrVarbound(scip) );
   SCIP_CALL( SCIPincludeConshdlrXor(scip) );
   SCIP_CALL( SCIPincludeReaderBnd(scip) );
   SCIP_CALL( SCIPincludeReaderCcg(scip) );
   SCIP_CALL( SCIPincludeReaderCip(scip) );
   SCIP_CALL( SCIPincludeReaderCnf(scip) );
   SCIP_CALL( SCIPincludeReaderDiff(scip) );
   SCIP_CALL( SCIPincludeReaderFix(scip) );
   SCIP_CALL( SCIPincludeReaderFzn(scip) );
   SCIP_CALL( SCIPincludeReaderGms(scip) );
   SCIP_CALL( SCIPincludeReaderLp(scip) );
   SCIP_CALL( SCIPincludeReaderMps(scip) );
   SCIP_CALL( SCIPincludeReaderOpb(scip) );
   SCIP_CALL( SCIPincludeReaderOsil(scip) );
   SCIP_CALL( SCIPincludeReaderPip(scip) );
   SCIP_CALL( SCIPincludeReaderPpm(scip) );
   SCIP_CALL( SCIPincludeReaderPbm(scip) );
   SCIP_CALL( SCIPincludeReaderRlp(scip) );
   SCIP_CALL( SCIPincludeReaderSol(scip) );
   SCIP_CALL( SCIPincludeReaderWbo(scip) );
   SCIP_CALL( SCIPincludeReaderZpl(scip) );
   SCIP_CALL( SCIPincludePresolBoundshift(scip) );
   SCIP_CALL( SCIPincludePresolComponents(scip) );
   SCIP_CALL( SCIPincludePresolConvertinttobin(scip) );
   SCIP_CALL( SCIPincludePresolDomcol(scip) );
   SCIP_CALL( SCIPincludePresolImplfree(scip) );
   SCIP_CALL( SCIPincludePresolDualagg(scip) );
   SCIP_CALL( SCIPincludePresolDualinfer(scip) );
   SCIP_CALL( SCIPincludePresolGateextraction(scip) );
   SCIP_CALL( SCIPincludePresolImplics(scip) );
   SCIP_CALL( SCIPincludePresolInttobinary(scip) );
   SCIP_CALL( SCIPincludePresolRedvub(scip) );
   SCIP_CALL( SCIPincludePresolTrivial(scip) );
   SCIP_CALL( SCIPincludePresolTworowbnd(scip) );
   SCIP_CALL( SCIPincludePresolStuffing(scip) );
   SCIP_CALL( SCIPincludeNodeselBfs(scip) );
   SCIP_CALL( SCIPincludeNodeselBreadthfirst(scip) );
   SCIP_CALL( SCIPincludeNodeselDfs(scip) );
   SCIP_CALL( SCIPincludeNodeselEstimate(scip) );
   SCIP_CALL( SCIPincludeNodeselHybridestim(scip) );
   SCIP_CALL( SCIPincludeNodeselRestartdfs(scip) );
   SCIP_CALL( SCIPincludeNodeselUct(scip) );
   SCIP_CALL( SCIPincludeBranchruleAllfullstrong(scip) );
   SCIP_CALL( SCIPincludeBranchruleCloud(scip) );
   SCIP_CALL( SCIPincludeBranchruleDistribution(scip) );
   SCIP_CALL( SCIPincludeBranchruleFullstrong(scip) );
   SCIP_CALL( SCIPincludeBranchruleInference(scip) );
   SCIP_CALL( SCIPincludeBranchruleLeastinf(scip) );
   SCIP_CALL( SCIPincludeBranchruleMostinf(scip) );
   SCIP_CALL( SCIPincludeBranchruleMultAggr(scip) );
   SCIP_CALL( SCIPincludeBranchruleNodereopt(scip) );
   SCIP_CALL( SCIPincludeBranchrulePscost(scip) );
   SCIP_CALL( SCIPincludeBranchruleRandom(scip) );
   SCIP_CALL( SCIPincludeBranchruleRelpscost(scip) );
   SCIP_CALL( SCIPincludeComprLargestrepr(scip) );
   SCIP_CALL( SCIPincludeComprWeakcompr(scip) );
   SCIP_CALL( SCIPincludeHeurActconsdiving(scip) );
   SCIP_CALL( SCIPincludeHeurBound(scip) );
   SCIP_CALL( SCIPincludeHeurClique(scip) );
   SCIP_CALL( SCIPincludeHeurCoefdiving(scip) );
   SCIP_CALL( SCIPincludeHeurCrossover(scip) );
   SCIP_CALL( SCIPincludeHeurDins(scip) );
   SCIP_CALL( SCIPincludeHeurDistributiondiving(scip) );
   SCIP_CALL( SCIPincludeHeurDualval(scip) );
   SCIP_CALL( SCIPincludeHeurFeaspump(scip) );
   SCIP_CALL( SCIPincludeHeurFixandinfer(scip) );
   SCIP_CALL( SCIPincludeHeurFracdiving(scip) );
   SCIP_CALL( SCIPincludeHeurGuideddiving(scip) );
   SCIP_CALL( SCIPincludeHeurZeroobj(scip) );
   SCIP_CALL( SCIPincludeHeurIndicator(scip) );
   SCIP_CALL( SCIPincludeHeurIntdiving(scip) );
   SCIP_CALL( SCIPincludeHeurIntshifting(scip) );
   SCIP_CALL( SCIPincludeHeurLinesearchdiving(scip) );
   SCIP_CALL( SCIPincludeHeurLocalbranching(scip) );
   SCIP_CALL( SCIPincludeHeurNlpdiving(scip) );
   SCIP_CALL( SCIPincludeHeurMutation(scip) );
   SCIP_CALL( SCIPincludeHeurObjpscostdiving(scip) );
   SCIP_CALL( SCIPincludeHeurOctane(scip) );
   SCIP_CALL( SCIPincludeHeurOfins(scip) );
   SCIP_CALL( SCIPincludeHeurOneopt(scip) );
   SCIP_CALL( SCIPincludeHeurProximity(scip) );
   SCIP_CALL( SCIPincludeHeurPscostdiving(scip) );
   SCIP_CALL( SCIPincludeHeurRandrounding(scip) );
   SCIP_CALL( SCIPincludeHeurRens(scip) );
   SCIP_CALL( SCIPincludeHeurReoptsols(scip) );
   SCIP_CALL( SCIPincludeHeurRins(scip) );
   SCIP_CALL( SCIPincludeHeurRootsoldiving(scip) );
   SCIP_CALL( SCIPincludeHeurRounding(scip) );
   SCIP_CALL( SCIPincludeHeurShiftandpropagate(scip) );
   SCIP_CALL( SCIPincludeHeurShifting(scip) );
   SCIP_CALL( SCIPincludeHeurSimplerounding(scip) );
   SCIP_CALL( SCIPincludeHeurSubNlp(scip) );
   SCIP_CALL( SCIPincludeHeurTrivial(scip) );
   SCIP_CALL( SCIPincludeHeurTrivialnegation(scip) );
   SCIP_CALL( SCIPincludeHeurTrySol(scip) );
   SCIP_CALL( SCIPincludeHeurTwoopt(scip) );
   SCIP_CALL( SCIPincludeHeurUndercover(scip) );
   SCIP_CALL( SCIPincludeHeurVbounds(scip) );
   SCIP_CALL( SCIPincludeHeurVeclendiving(scip) );
   SCIP_CALL( SCIPincludeHeurZirounding(scip) );
   SCIP_CALL( SCIPincludePropDualfix(scip) );
   SCIP_CALL( SCIPincludePropGenvbounds(scip) );
   SCIP_CALL( SCIPincludePropObbt(scip) );
   SCIP_CALL( SCIPincludePropProbing(scip) );
   SCIP_CALL( SCIPincludePropPseudoobj(scip) );
   SCIP_CALL( SCIPincludePropRedcost(scip) );
   SCIP_CALL( SCIPincludePropRootredcost(scip) );
   SCIP_CALL( SCIPincludePropVbounds(scip) );
   SCIP_CALL( SCIPincludeSepaCGMIP(scip) );
   SCIP_CALL( SCIPincludeSepaClique(scip) );
   SCIP_CALL( SCIPincludeSepaClosecuts(scip) );
   SCIP_CALL( SCIPincludeSepaCmir(scip) );
   SCIP_CALL( SCIPincludeSepaEccuts(scip) );
   SCIP_CALL( SCIPincludeSepaDisjunctive(scip) );
   SCIP_CALL( SCIPincludeSepaFlowcover(scip) );
   SCIP_CALL( SCIPincludeSepaGomory(scip) );
   SCIP_CALL( SCIPincludeSepaImpliedbounds(scip) );
   SCIP_CALL( SCIPincludeSepaIntobj(scip) );
   SCIP_CALL( SCIPincludeSepaMcf(scip) );
   SCIP_CALL( SCIPincludeSepaOddcycle(scip) );
   SCIP_CALL( SCIPincludeSepaRapidlearning(scip) );
   SCIP_CALL( SCIPincludeSepaStrongcg(scip) );
   SCIP_CALL( SCIPincludeSepaZerohalf(scip) );
   SCIP_CALL( SCIPincludeDispDefault(scip) );
   //SCIP_CALL( SCIPincludeEventHdlrSofttimelimit(scip) );

   /* include NLPI's, if available */
   SCIP_CALL( SCIPcreateNlpSolverIpopt(SCIPblkmem(scip), &nlpi) );
   if( nlpi != NULL )
   {
      SCIP_CALL( SCIPincludeNlpi(scip, nlpi) );
      SCIP_CALL( SCIPincludeExternalCodeInformation(scip, SCIPgetSolverNameIpopt(), SCIPgetSolverDescIpopt()) );
   }

   SCIP_CALL( SCIPdebugIncludeProp(scip) ); /*lint !e506 !e774*/


   /* we explicitly enable the use of a debug solution for this main SCIP instance */
   SCIPenableDebugSol(scip);

   //SCIP_CALL( SCIPincludeDefaultPlugins(scip) );

/*
   SDgeom::TestGeom test(scip);
   //test.runAll();
   test.runCurrent();
   std::cout << "Finished tests" << std::endl;
   assert(false);
*/

/*
   SCIPdebugMessage("testing sb rate evaluator:\n");
   ctrl::TestSBrateEvaluator test;
   test.runBoundTests();

   SCIPdebugMessage("finished tests, %i success, %i errors:\n", test.getNsuccess(), test.getNerrors());
   assert(false);
*/

/*Test ODEintegrator */
/*
   SCIPdebugMessage("testing ode integrator:\n");
   ctrl::TestODEintegrator test(scip);
   //test.runSimTests();
   //test.runSBtests();
   //test.runPredatorPreySBsimTest();
   test.runAll();

   SCIPdebugMessage("finished tests, %i success, %i errors:\n", test.getNsuccess(), test.getNerrors());
   assert(false);
*/

/* Test BoundMap operations */
/*   ctrl::TestBoundMap test;
   assert(false); */


/* Test Statistics class */
/*
   I4H::Statistics stats;

   double val(0);
   for (int i = 0; i < 10001; i++)
   {
      stats.addVal(val);
      val += 0.0001;
   }
   SCIPdebugMessage("mean is %f\n", stats.mean());
   SCIPdebugMessage("max is %f\n", stats.max());
   SCIPdebugMessage("min is %f\n", stats.min());
   SCIPdebugMessage("number of values is %i\n", stats.nVals());
   assert(false);
*/

/*Test ExprPiecewiseLinear */
if (false)
{

   ctrl::TestEstimatorTypes test(scip);
   //test.runEstimatorManualTests();
   //test.runEstimatorRandomTests();
   SCIPdebugMessage("Testing class-1 estimators :\n");
   test.runAll();

   SCIPdebugMessage("finished %i tests, %i success, %i errors:\n", test.getNtests(), test.getNsuccess(), test.getNerrors());
   assert(false);
}



   /* include TSP specific plugins */
/*   SCIP_CALL( SCIPincludeObjReader(scip, new ReaderTSP(scip), TRUE) ); */
/*   SCIP_CALL( SCIPincludeObjPresol(scip, new PresolConsGraph(scip), TRUE) );*/
   SCIPdebugMessage("now including PropOBRA\n");
   SCIP_CALL( SCIPincludeObjProp(scip, new ctrl::PropOBRA(scip), TRUE) );
/*   SCIP_CALL( SCIPincludeObjConshdlr(scip, new ConshdlrSubtour(scip), TRUE) );
   SCIP_CALL( SCIPincludeObjEventhdlr(scip, new EventhdlrNewSol(scip), TRUE) ); */

   printf("including SimODE heuristic\n");
   SCIP_CALL( SCIPincludeObjHeur(scip, new ctrl::HeurSimODE(scip), TRUE) );

   printf("including ControlFirst branching rule\n");
   SCIP_CALL( SCIPincludeObjBranchrule(scip, new ctrl::BranchruleControlFirst(scip), TRUE) );

   //printf("including PropCtrlOBBT Propagator\n");
   //SCIP_CALL( SCIPincludeObjProp(scip, new ctrl::PropCtrlOBBT(scip), TRUE) );

   //printf("including PropProbingObjTest Propagator\n");
   //SCIP_CALL( SCIPincludeObjProp(scip, new ctrl::PropProbingObjTest(scip), TRUE) );


   //printf("including prop_obobt Propagator\n");
   //SCIP_CALL( SCIPincludePropObobt(scip) );


   printf("including PropODE Propagator\n");
   SCIP_CALL( SCIPincludeObjProp(scip, new ctrl::PropODE(scip), TRUE) );

   printf ( "including ReaderVOP\n" );
   SCIP_CALL( SCIPincludeObjReader(scip, new sdo::ReaderVOP(scip), TRUE) );

   //printf("including reader_osilc\n");
   //SCIP_CALL( SCIPincludeReaderOsilC(scip) );

   SCIP_CALL( SCIPaddParamsSD(scip));

   /**********************************
    * Process command line arguments *
    **********************************/


    SCIP_CALL( SCIPprocessShellArguments(scip, argc, argv, "sdscip.set") );

   /********************
    * Deinitialization *
    ********************/

   SCIP_CALL( SCIPfree(&scip) );

   BMScheckEmptyMemory();

   return SCIP_OKAY;
}

/** main method starting TSP code */
int main(
   int                        argc,          /**< number of arguments from the shell */
   char**                     argv           /**< array of shell arguments */
   )
{
   SCIP_RETCODE retcode;

   retcode = runSCIP(argc, argv);
   if( retcode != SCIP_OKAY )
   {
      SCIPprintError(retcode);
      return -1;
   }

   return 0;
}
