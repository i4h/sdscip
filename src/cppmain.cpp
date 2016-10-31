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
#include "reader_osilc.h"
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

   /* include default SCIP plugins */
   SCIP_CALL( SCIPincludeDefaultPlugins(scip) );


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
