#define SCIP_DEBUG
#define SCIP_DBG
//{##header##}

/**@file   cppmain.cpp
 * @brief  main file for SD-SCIP
 * @author Ingmar Vierhaus
 *
 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include <iostream>
#include <vector>


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
#include "BaseTest.h"
#include "TestGeom.h"
#include "TestODEintegrator.h"
#include "TestSBrateEvaluator.h"
#include "TestBoundMap.h"
#include "TestExprPiecewiseLinear.hpp"
#include "TestEstimatorTypes.hpp"
#include "TestStatistics.h"

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

   /* Create the test classes */
   std::vector<I4H::BaseTest*> tests;

   //tests.emplace_back( new sdscip::TestGeom(scip));
   //tests.emplace_back( new sdscip::TestSBrateEvaluator(scip));

   //tests.emplace_back( new sdscip::TestODEintegrator(scip));

   //tests.emplace_back( new sdscip::TestBoundMap(scip));

   //tests.emplace_back( new I4H::TestStatistics);




   for (auto it : tests)
   {
      std::cout << "=========================================" << std::endl;
      std::cout << "Running all tests in class " << *it << std::endl;
      it->runAll();
      std::cout << " ----------------------------------------" << std::endl;
      std::cout << " " << it->summaryString() << std::endl;
      std::cout << "=========================================" << std::endl;
      std::cout << std::endl;
      delete it;
   }


/*Test ExprPiecewiseLinear */
if (true)
{

   sdscip::TestEstimatorTypes test(scip);
   //test.runEstimatorManualTests();
   //test.runEstimatorRandomTests();
   SCIPdebugMessage("Testing class-1 estimators :\n");
   test.runAll();

   //assert(false);

   SCIPdebugMessage("finished %i tests, %i success, %i errors:\n", test.nExecutedTests_, test.nSuccess_, test.nError_);
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
