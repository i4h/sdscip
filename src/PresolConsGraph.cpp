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

//#include
/**@file   PresolConsGraph.cpp
 * @brief  Creates a Graph that represents the structure of Constraints and Variables of the NLP-Problem
 * @author Ingmar Vierhaus <vierhaus@zib.de>
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include <assert.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <map>

#include<lemon/list_graph.h>
#include<lemon/math.h>

#include<iostream>
#include<fstream>



#include "PresolConsGraph.h"

#include "scip/struct_var.h"


#include "NLPGraph.h"

/*
 * Data structures
 */

/* TODO: fill in the necessary presolver data */

/** presolver data */
/*struct SCIP_PresolData
{
}; */


/*
 * Local methods
 */

/* put your local methods here, and declare them static */


/*
 * Callback methods of presolver
 */

/* TODO: Implement all necessary presolver methods. The methods with an #if 0 ... #else #define ... are optional */


/** execution method of presolver */
SCIP_DECL_PRESOLEXEC(PresolConsGraph::scip_exec)
{  /*lint --e{715}*/

   SCIP_CONSHDLR** conshdlrs;

   int nconshdlrs;
   int i,v;


   //   SCIP_CONSDATA* consdata;

   nconshdlrs = SCIPgetNConshdlrs(scip);
   conshdlrs = SCIPgetConshdlrs(scip);
   assert(nconshdlrs == 0 || conshdlrs != NULL);
   assert(SCIPisTransformed(scip));

   // Create an NLP graph
   NLPGraph g;

   /* Build graph: loop through all () constraint handlers */
   for( i = 0; i < nconshdlrs; ++i )
   {
      int nconss;
      int c;

      SCIP_CONS** conss;
      SCIP_Bool success;

      assert(conshdlrs[i] != NULL);

      SCIPdebugMessage("adding Constraints in %s constraint handler to Graph\n",SCIPconshdlrGetName(conshdlrs[i]));

      nconss = SCIPconshdlrGetNActiveConss(conshdlrs[i]);
      conss = SCIPconshdlrGetConss(conshdlrs[i]);

      assert(nconss == 0 || conss != NULL);

      if( nconss > 0 )
         SCIPdebugMessage("Adding %d %s constraints\n", nconss, SCIPconshdlrGetName(conshdlrs[i]));

        /*Allocate Arrays that will define the ordering process */
/*        int* consNamesCounter = NULL;
        SCIP_ALLOC( BMSallocMemoryArray(&consNamesCounter, nconss) ); */

        /* iterating over constraints to determine the order that corresponds to control problem structure FROM VARIABLE NAMES */
      for( c = 0; c < nconss; ++c )
      {
         int nConsVars;
         SCIP_VAR** consvars;


         NLPGraph::ConsNode cNode;
         cNode = g.addCons(std::string(SCIPconsGetName(conss[c])),conss[c]);

         //Getting this constraints variable number and variables
         SCIP_CALL( SCIPgetConsNVars(scip, conss[c], &nConsVars, &success) );
         assert(success);
         SCIP_CALL( SCIPallocBufferArray(scip, &consvars, nConsVars) );
         SCIP_CALL( SCIPgetConsVars(scip, conss[c], consvars, nConsVars, &success) );
         assert(success);

         //consdata = SCIPconsGetData(conss[c]);
         //SCIPdbgMsg ("considering %s\n",SCIPconsGetName(conss[c]) );

         /*Iterate over variables of this constraint */
         for( v = 0; v < nConsVars; v++ )
         {
            //Add edge and if necessary variable to Graph
            NLPGraph::VarNode vNode;
            vNode = g.showVar(consvars[v]);
            g.addEdge(cNode,vNode);
         }
         SCIPfreeBufferArray(scip, &consvars);
      }
   }

   SCIPdbgMsg("done building tree, calculating 1stlevelorders\n");

   g.calcConsOrders();
   //SCIPdbg( g.printNodes(); )

   g.calcPropagationSequence();

   g.writeGraph(std::string("testOut.dot"));


   return SCIP_OKAY;
}

