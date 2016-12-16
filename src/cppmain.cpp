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
 * @brief  main file for SD-SCIP, based on SCIP's TSP-Example
 * @author Ingmar Vierhaus
 *
 */

#define SCIP_DBG

#include <iostream>

/* include SCIP components */
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"
#include "scip/scipdefplugins.h"
#include "scip/debug.h"

/* include SD-SCIP components */
#include "reader_osilc.h"
#include "ProbDataSD.h"

#include "PropOBRA.h"
#include "HeurSimODE.h"
#include "BranchControlFirst.h"
#include "PropODE.h"

#include "ReaderVOP.h"
#include "PresolConsGraph.h"
#include "Statistics.h"
#include "SDSCIPgitHash.h"

using namespace scip;
using namespace std;


/** prints a version information line to a file stream via the message handler system
 *
 *  @note If the message handler is set to a NULL pointer nothing will be printed
 *  @note Based on SCIPprintVersion
 */
void SDSCIPprintVersion(
   SCIP*                 scip,               /**< SCIP data structure */
   FILE*                 file                /**< output file (or NULL for standard output) */
   )
{
   assert( scip != NULL );

   SCIPmessageFPrintInfo(scip->messagehdlr, file, "SDSCIP version 0.9.0");

   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [precision: %d byte]", (int)sizeof(SCIP_Real));

#ifndef BMS_NOBLOCKMEM
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [memory: block]");
#else
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [memory: standard]");
#endif
#ifndef NDEBUG
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [mode: debug]");
#else
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [mode: optimized]");
#endif
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, " [GitHash: %s]", SDSCIPgitHash::getHash().c_str());
   SCIPmessageFPrintInfo(scip->messagehdlr, NULL, ", Using: \n");
}


/** creates and runs a SCIP instance with default and SD-SCIP plugins */
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

   //SCIP_CALL ( SCIPincludeDialogSDinit ( scip ) );
   //SCIP_CALL ( SCIPincludeDialogSDprintStructure( scip ) );
   //SCIP_CALL ( SCIPincludeDialogSDensureValidStructure( scip ) );
   //SCIP_CALL ( SCIPincludeDialogSDrefreshStructure( scip ) );
   //SCIP_CALL ( SCIPincludeDialogSDdoSomething( scip ) );
   //SCIP_CALL ( SCIPincludeDialogSDdisable( scip ) );
   SCIP_CALL ( SCIPincludeDialogSD ( scip ) );

   /* include default SCIP plugins */
   SCIP_CALL( SCIPincludeDefaultPlugins(scip) );


   /* we explicitly enable the use of a debug solution for this main SCIP instance */
   SCIPenableDebugSol(scip);

   //SCIP_CALL( SCIPincludeDefaultPlugins(scip) );


   SCIP_CALL( SCIPincludeObjProp(scip, new sdscip::PropOBRA(scip), TRUE) );
   SCIP_CALL( SCIPincludeObjHeur(scip, new sdscip::HeurSimODE(scip), TRUE) );
   SCIP_CALL( SCIPincludeObjBranchrule(scip, new sdscip::BranchruleControlFirst(scip), TRUE) );
   SCIP_CALL( SCIPincludeObjProp(scip, new sdscip::PropODE(scip), TRUE) );
   SCIP_CALL( SCIPincludeObjReader(scip, new sdo::ReaderVOP(scip), TRUE) );

   SCIP_CALL( SCIPaddParamsSD(scip));

   SDSCIPprintVersion(scip, NULL);


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


/** main method starting SD-SCIP */
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
