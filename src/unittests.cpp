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
#include "TestGeom.h"
#include "TestODEintegrator.h"
#include "TestSBrateEvaluator.h"
#include "TestBoundMap.h"
#include "TestExprPiecewiseLinear.hpp"
#include "TestEstimatorTypes.hpp"

using namespace scip;
using namespace std;


/** run unit tests for sd-scip */
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

   {
   sdscip::TestGeom test(scip);
   test.runAll();
   std::cout << "Finished tests of SDgeom class" << std::endl;
   }

   /*{
   SCIPdebugMessage("testing sb rate evaluator:\n");
   sdscip::TestSBrateEvaluator test;
   test.runBoundTests();


   SCIPdebugMessage("finished tests, %i success, %i errors:\n", test.getNsuccess(), test.getNerrors());
   }*/


/*Test ODEintegrator */
/*
   SCIPdebugMessage("testing ode integrator:\n");
   sdscip::TestODEintegrator test(scip);
   //test.runSimTests();
   //test.runSBtests();
   //test.runPredatorPreySBsimTest();
   test.runAll();

   SCIPdebugMessage("finished tests, %i success, %i errors:\n", test.getNsuccess(), test.getNerrors());
   assert(false);
*/

/* Test BoundMap operations */
/*   sdscip::TestBoundMap test;
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

   sdscip::TestEstimatorTypes test(scip);
   //test.runEstimatorManualTests();
   //test.runEstimatorRandomTests();
   SCIPdebugMessage("Testing class-1 estimators :\n");
   test.runAll();

   SCIPdebugMessage("finished %i tests, %i success, %i errors:\n", test.getNtests(), test.getNsuccess(), test.getNerrors());
   assert(false);
}


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
