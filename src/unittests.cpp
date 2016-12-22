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
#include "ReaderSDO.h"
#include "PresolConsGraph.h"
#include "Statistics.h"
#include "scip/scipdefplugins.h"
#include "scip/debug.h"

/* Include unit-testing classes */
#include "BaseTest.h"
#include "TestGeom.h"
#include "TestODEintegrator.h"
#include "TestSBrateEvaluator.h"
#include "TestBoundMap.h"
#include "TestExprPiecewiseLinear.h"
#include "TestEstimatorTypes.h"
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

   /* initialize SD-SCIP */
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
   SCIP_Bool testall = true;

   if (testall)
   {
      /* Create container for test classes */
      std::vector<I4H::BaseTest*> tests;

      /* Add test classes */
      tests.emplace_back( new sdscip::TestGeom(scip));
      tests.emplace_back( new sdscip::TestSBrateEvaluator(scip));
      tests.emplace_back( new sdscip::TestODEintegrator(scip));
      tests.emplace_back( new sdscip::TestBoundMap(scip));
      tests.emplace_back( new I4H::TestStatistics);
      tests.emplace_back( new sdscip::TestEstimatorTypes(scip));
      tests.emplace_back( new sdscip::TestExprPiecewiseLinear(scip));

      /* Run all tests of all test classes */
      for (auto it : tests)
      {
         std::cout << "==========================================================" << std::endl;
         std::cout << "Running all tests in class " << *it << std::endl;
         it->runAll();
         std::cout << it->summaryString() << std::endl;
         std::cout << "==========================================================" << std::endl;
         std::cout << std::endl;
         delete it;
      }
   }
   else
   {
      /* Set testall to false and use this code to run an an individual test */
      TestExprPiecewiseLinear* test = new sdscip::TestExprPiecewiseLinear(scip);
      test->runWorldLookupFeastol();
      //test->runWorldLookup();
      std::cout << test->summaryString() << std::endl;
      delete test;
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
