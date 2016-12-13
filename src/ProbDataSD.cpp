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

/**@file   ProbDataSD.cpp
 * @brief  Problem data for SD-SCIP
 * @author Ingmar Vierhaus
 *
 * This class defines the Problem Data for System Dynamics Optimization problems. The problem structure is read
 * from the names of constraints and variables through regular expressions. The conventions are as follows:
 *
 * Constraints:
 * - should be named "eq_constraintname[_level][_type][_subtype](time)"
 *
 * Variables:
 *  - should be named either "t_varname[_level][_type](time[,auxiliaryindex][,auxiliaryindex][...])
 *  - .. or                  "t_varname_c(time[,auxiliaryindex][,auxiliaryindex][...])" in case of control variables
 *
 *
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include <vector>
#include <map>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "SDproblemStructureInterface.h"
#include "ProbDataSD.h"
#include "SDVarBasic.h"

#include "scip/pub_var.h"
#include "scip/pub_cons.h"
#include <scip/cons_linear.h>
#include <scip/cons_varbound.h>
#include <scip/cons_nonlinear.h>
#include <scip/cons_quadratic.h>


#include "scip/dialog_default.h"

#define DIALOG_NAME            "sdInit"
#define DIALOG_WRITE_NAME            "writeTransprobSD"
#define DIALOG_DESC            "Initialize an already read System Dynamics Optimization problem"
#define DIALOG_ISSUBMENU          FALSE 




/**@name Local methods
 *
 * @{
 */


bool SDisEquation(SCIP* scip, SCIP_CONS* cons)
{
   SCIP_Bool isEquation;
   SCIP_CONSHDLR* conshdlr;
   conshdlr = SCIPconsGetHdlr(cons);

   //TODO _SD: check if this method is really needed, if yes implement this in sdscip not in scip

   /*if (strcmp(SCIPconshdlrGetName(conshdlr),"nonlinear") == 0) {
      SCIP_CALL(SCIPconsIsEquationNonlinear(scip,cons,&isEquation));
   }
   else if (strcmp(SCIPconshdlrGetName(conshdlr),"linear") == 0)
   {
      SCIPconsIsEquationLinear(scip,cons,&isEquation);
   }
   else if (strcmp(SCIPconshdlrGetName(conshdlr),"varbound") == 0)
   {
      SCIPconsIsEquationVarbound(scip,cons,&isEquation);
   }
   else if (strcmp(SCIPconshdlrGetName(conshdlr),"quadratic") == 0)
   {
      SCIPconsIsEquationQuadratic(scip,cons,&isEquation);
   }
   else
   {*/
      SCIPdbgMsg("isEquation for constraint type %s not implemented",SCIPconshdlrGetName(conshdlr));
      assert(false);
   /*}*/
   return isEquation;
}

/** creates problem data */
static
SCIP_RETCODE probdataCreate(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_PROBDATA**       probdata            /**< pointer to problem data */
   )
{
   assert(scip != NULL);
   assert(probdata != NULL);

   SCIPdbgMsg("probdataCreate\n");

   /* allocate memory */
   SCIP_CALL( SCIPallocMemory(scip, probdata) );

   /* create problem structure using factory*/
   int probStructureVersion(0);
   SCIP_CALL( SCIPgetIntParam(scip,"sd/problemStructureVersion",&probStructureVersion));
   sdscip::SDproblemStructureFactory factory;

   (*probdata)->structure = factory.create(probStructureVersion, scip);
   SCIPdebugMessage("created probStructure, is reformulated = %s\n",( (*probdata)->structure->isReformulated() ? "true" : "false"));

   return SCIP_OKAY;
}

/** frees the memory of the given problem data */
static
SCIP_RETCODE probdataFree(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_PROBDATA**       probdata            /**< pointer to problem data */
   )
{

   assert(scip != NULL);
   assert(probdata != NULL);

   SCIPdebugMessage("freeing problem data\n");

   /* delete stl containers */
   delete (*probdata)->structure;

   /* free probdata */
   SCIPfreeMemory(scip, probdata);

   return SCIP_OKAY;
}

/**@} */

/**@name Callback methods of problem data
 *
 * @{
 */

/** frees user data of original problem (called when the original problem is freed) */
static
SCIP_DECL_PROBDELORIG(probdelorigSD)
{
   SCIPdebugMessage("free original problem data\n");

   SCIP_CALL( probdataFree(scip, probdata) );

   return SCIP_OKAY;
}

/** creates user data of transformed problem by transforming the original user problem data
 *  (called after problem was transformed) */
/*
static
SCIP_DECL_PROBTRANS(probtransSD)
{
*/
   /* create transform probdata */
/*
   SCIP_CALL( probdataCreate(scip, targetdata) );

   return SCIP_OKAY;
}
*/

/** frees user data of transformed problem (called when the transformed problem is freed) */
/*static
SCIP_DECL_PROBDELTRANS(probdeltransSD)
{
   SCIPdebugMessage("free transformed problem data\n");

   SCIP_CALL( probdataFree(scip, probdata) );

   return SCIP_OKAY;
}
*/
/** solving process initialization method of transformed data (called before the branch and bound process begins) */
static
SCIP_DECL_PROBINITSOL(probinitsolSD)
{
/*   SCIP_CALL( probdataCreate(scip, &probdata) );

   SCIPdbgMsg("created Probdata\n");


   SCIP_CALL( SCIPsetProbData(scip, probdata) );
   SCIPdbgMsg("Set probdata\n");

   SCIP_PROBDATA* probdata2;
   probdata2 = SCIPgetProbData(scip);

   assert(probdata2 != NULL);
*/

  return SCIP_OKAY;
}

/** solving process deinitialization method of transformed data (called before the branch and bound data is freed) */
/*
static
SCIP_DECL_PROBEXITSOL(probexitsolSD)
{
  return SCIP_OKAY;
}
*/
/**@} */


/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDinit)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIP_CALL(SDinit(scip));

   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}

/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDprintStructure)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIP_CALL(SDprintStructure(scip));

   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}

/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDensureValidStructure)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIP_CALL( SDensureValidStructure(scip) );

   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}



/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecWriteTransprobSD)
{  /*lint --e{715}*/
   SCIP_PROBDATA* probdata;
   probdata = SCIPgetProbData(scip);
   assert(probdata != NULL);


   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIPdebugMessage("WriteTransprobSD called from dialog\n");
   char* paramstr;
   SCIPgetStringParam(scip,"constraints/ctrlDifferential/outFile",&paramstr);
   int historicCons(0);
   SCIP_CALL( SCIPgetIntParam(scip,"constraints/ctrlDifferential/historicCons",&historicCons));

   std::ostringstream oss;
   oss << paramstr << "_" << historicCons << ".gms";
   SCIPdebugMessage("WRITING transformed problem to file %s\n",oss.str().c_str());
   SCIPwriteTransProblem(scip, oss.str().c_str(), std::string("gms").c_str(), false);
   SCIPdebugMessage("done writing\n");


   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}

/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDrefreshStructure)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SDrefreshStructure(scip);

   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}


/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDdoSomething)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIPdebugMessage("!!!!!!!!!doing Something!!!!!!!!!!!!!!!!\n");

   /* Lots of blank space for testing */
   //sdscip::SDproblemStructureInterface* structure(SDgetStructure(scip) );


   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}

/** execution method of dialog */
static
SCIP_DECL_DIALOGEXEC(dialogExecSDdisable)
{  /*lint --e{715}*/

   /* add your dialog to history of dialogs that have been executed */
   SCIP_CALL( SCIPdialoghdlrAddHistory(dialoghdlr, dialog, NULL, FALSE) );

   SCIPsetIntParam(scip, "heuristics/simODE/freq", -1);
   SCIPsetIntParam(scip, "propagating/propODE/freq", -1);
   SCIPsetIntParam(scip, "propagating/propODE/maxprerounds", 0);
   SCIPsetIntParam(scip, "propagating/obra/maxprerounds", 0);
   SCIPsetIntParam(scip, "propagating/obra/freq", -1);


   /* next dialog will be root dialog again */
   *nextdialog = SCIPdialoghdlrGetRoot(dialoghdlr);

   return SCIP_OKAY;
}

SCIP_RETCODE SDinit(SCIP* scip) {

   SCIP_PROBDATA* probdata;
   probdata = SCIPgetProbData(scip);

   if (probdata != NULL)
   {
      SCIPwarningMessage(scip, "Probdata already exists, sdInit called more than once, or different Problem Structure was initialized!\n");
      SCIP_CALL( SDensureValidStructure( scip) );
      return SCIP_OKAY;
   }

   SCIPdbgMsg("executing dialog SDinit\n");
   SCIP_CALL( probdataCreate(scip, &probdata) );
   SCIPdbgMsg("created Probdata\n");

   SCIP_CALL( SCIPsetProbData(scip, probdata) );
   SCIPdbgMsg("Set probdata\n");

   SCIP_CALL( SCIPsetProbDelorig(scip, probdelorigSD) );
   SCIP_CALL( SCIPsetProbInitsol(scip,probinitsolSD) );
   //TODO: _SD set remaining function pointers

   return SCIP_OKAY;
}

SCIP_RETCODE SDensureValidStructure(SCIP* scip) {

   if ( SDgetIsStructureValid(scip) )
   {
      SCIPdebugMessage("SDensureValidStructure: Structure is valid, exiting\n");
      return SCIP_OKAY;
   }
   SCIPdebugMessage("SDensureValidStructure: Structure is invalid, calling refreshStructure\n");
   SCIP_CALL( SDrefreshStructure(scip) );
   return SCIP_OKAY;
}

SCIP_RETCODE SDrefreshStructure(SCIP* scip) {

   SCIP_CALL( SDreadStructure(scip ) );
   return SCIP_OKAY;

}

/* This method ensures that the problem structure data that was created from parsing a cip file, or when reading
 * from a mdl file (via a vop file) satisfies the requirements for the plugins
 */
SCIP_RETCODE checkStructure(SCIP* scip)
{
   int errorCount(0);

   /* Check the order of the state variables in the getStateVars iteration is alphabetical */
   {
      SCIPdebugMessage("checking alphabetic order of state variables t\n");

      SCIP_PROBDATA *probdata = SCIPgetProbData(scip);
      assert(probdata != NULL);
      SDensureValidStructure(scip);;
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);
      unsigned int nStates(structure->getNStates());
      SCIPdebugMessage("nStates is %i\n",nStates);
      std::vector<std::string> stateVarNames(structure->getStateVarNames());
      if (!std::is_sorted(stateVarNames.begin(),stateVarNames.end()))
      {
         SCIPerrorMessage("ERROR: state var names are not sorted alphabetically %s\n");
         ++errorCount;
      }
   }

   /* Check the order of the state variables in the getStateVars iteration corresponds to the stateVarNames */
   {
      SCIPdebugMessage("checking order of state stateVarNames corresponds to scip stateVars t\n");

      SCIP_PROBDATA *probdata = SCIPgetProbData(scip);
      assert(probdata != NULL);
      SDensureValidStructure(scip);;
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);
      unsigned int nStates(structure->getNStates());
      SCIPdebugMessage("nStates is %i\n",nStates);
      std::vector<std::string> expectedBaseNames(structure->getStateVarNames());

      for (int currentTime = structure->startTimeIteration(); structure->timesLeft(); currentTime = structure->incrementTime())
      {
         {
            unsigned int varCounter = 0;
            for (structure->startStateVarIteration(); structure->stateVarsLeft();structure->incrementStateVar())
            {
               SCIP_VAR* var = structure->getCurrentStateVar();
               std::string basename(structure->getVarBasename(var));
               if( basename.compare(expectedBaseNames[varCounter]) != 0)
               {
                  SCIPerrorMessage("ERROR: at t = %i, expected state var %s at place %i, but found var %s\n",
                                    currentTime, expectedBaseNames[varCounter].c_str(), varCounter, SCIPvarGetName(var));
                  ++errorCount;
               }
               ++varCounter;
            }
            if (varCounter != nStates)
            {
               SCIPerrorMessage("ERROR: at t = %i, expected %i state vars found %i\n",
                  currentTime, nStates, varCounter + 1);
               ++errorCount;
            }
         }

      }
   }

   {
      SCIPdebugMessage("checking order of control variables t\n");
      SCIP_PROBDATA *probdata = SCIPgetProbData(scip);
      assert(probdata != NULL);
      SDensureValidStructure(scip);;
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);
      unsigned int nControls(structure->getNControls());
      std::vector<std::string> expectedBaseNames(structure->getControlVarNames());

      for (int currentTime = structure->startTimeIteration(); structure->timesLeft(); currentTime = structure->incrementTime())
      {
         unsigned int varCounter = 0;
         for (structure->startControlVarAtTIteration(); structure->controlVarsAtTLeft(); structure->incrementControlVarAtT())
         {
            SCIP_VAR* var = structure->getControlVarAtT();
            std::string basename(structure->getVarBasename(var));
            if( basename.compare(expectedBaseNames[varCounter]) != 0)
            {
               SCIPerrorMessage("ERROR: at t = %i, expected control var %s at place %i, but found var %s\n",
                  currentTime, expectedBaseNames[varCounter].c_str(), varCounter, SCIPvarGetName(var));
               ++errorCount;
            }
            else
               ++varCounter;
         }
         if (varCounter != nControls)
         {
            SCIPerrorMessage("ERROR: at t = %i, expected %i control vars found %i\n",
               currentTime, nControls, varCounter);
            ++errorCount;
         }
      }
   }

   {
      SCIPdebugMessage("making sure, state variables are returned as transformed variables\n");

      SCIP_PROBDATA *probdata = SCIPgetProbData(scip);
      assert(probdata != NULL);
      SDensureValidStructure(scip);;
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);

      for (structure->startTimeIteration(); structure->timesLeft(); structure->incrementTime())
      {
         for (structure->startStateVarIteration(); structure->stateVarsLeft();structure->incrementStateVar())
         {
            SCIP_VAR* var = structure->getCurrentStateVar();

            if (SCIPisTransformed(scip) && !SCIPvarIsTransformed(var))
            {
               SCIPerrorMessage("probstructure returned original var %s, but problem is transformed\n", SCIPvarGetName(var));
               ++errorCount;
            }
            if (!SCIPisTransformed(scip) && SCIPvarIsTransformed(var))
            {
               SCIPerrorMessage("probstructure returned transformed var %s, but problem is not transformed\n", SCIPvarGetName(var));
               ++errorCount;
            }

         }
      }
   }


   if (errorCount == 0)
   {
      SCIPinfoMessage(scip, NULL, "structure check successful, no errors\n");
   }
   else
   {
      SCIPinfoMessage(scip, NULL, "structure check failed, %i errors\n",errorCount);
   }

   return SCIP_OKAY;
}


SCIP_RETCODE SDprintStructureSummary(SCIP* scip) {

      char* discretization;
      SCIPgetStringParam(scip, "reading/vopreader/discretization", &discretization);

      SDensureValidStructure(scip);;
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);


      SCIPinfoMessage(scip, NULL, "\n=== Printing structure summary ===\n");
      SCIPinfoMessage(scip, NULL, "STATES:   %s (%i)\n",structure->getStateVarList().c_str(), structure->getNStates());
      SCIPinfoMessage(scip, NULL, "CONTROLS: %s (%i)\n",structure->getControlVarList().c_str(), structure->getNControls());
      SCIPinfoMessage(scip, NULL, "ALGEBRAIC: %s (%i)\n",structure->getAlgebraicVarList().c_str(), structure->getNAlgebraic());
      SCIPinfoMessage(scip, NULL, "TIME:     %f -> %f (%i Steps) \n",structure->getTinit(), structure->getTfinal(), structure->getLastTime());
      SCIPinfoMessage(scip, NULL, "SCHEME:   %s \n",discretization);
      for (int i = 0; i < (int) structure->getNStates(); ++i)
      {
         SCIP_EXPR** xDots = structure->getXdot();
         SCIPinfoMessage(scip, NULL, "xDot[%i]: ", i);
         SCIPexprPrint(xDots[i], SCIPgetMessagehdlr(scip), NULL, NULL, NULL, NULL);
         SCIPinfoMessage(scip, NULL, "\n");
      }
      for (int i = 0; i < (int) structure->getNStates(); ++i)
      {
         SCIP_EXPR** xDots = structure->getXdotAlgebraic();
         SCIPinfoMessage(scip, NULL, "xDotA[%i]: ", i);
         SCIPexprPrint(xDots[i], SCIPgetMessagehdlr(scip), NULL, NULL, NULL, NULL);
         SCIPinfoMessage(scip, NULL, "\n");
      }

      for (int i = 0; i < (int) structure->getNAlgebraic(); ++i)
      {
         SCIP_EXPR** algebraic = structure->getAlgebraicExpressions();
         SCIPinfoMessage(scip, NULL, "y[%i] (%s): ",i, structure->getAlgebraicVarNames()[i].c_str());
         SCIPexprPrint(algebraic[i], SCIPgetMessagehdlr(scip), NULL, NULL, NULL, NULL);
         SCIPinfoMessage(scip, NULL, "\n");
      }
      if( !structure->isXdotContinuous() )
      {
         SCIPinfoMessage(scip, NULL, "At least one of the state derivatives is not absolutely continuous\n");
      }
      sdscip::SDproblemStructureInterface::BoundMap boundMap = structure->getStrictBounds();
      if (boundMap.size() != 0)
      {
         SCIPinfoMessage(scip, NULL, "STRICT BOUNDS: \n",boundMap.size());
      }
      for( auto it = boundMap.begin(); it != boundMap.end(); ++it)
      {
         sdscip::SDproblemStructureInterface::BoundKey key = it->first;
         SCIP_Real bound = it->second;
         SCIPinfoMessage(scip, NULL, "Variable %s has strict %s bound: %e\n", structure->getVarName(key.first).c_str()
               , (key.second == SCIP_BOUNDTYPE_LOWER ? "lower" : "upper"), bound );

      }
      SCIPinfoMessage(scip, NULL, "=== End of structure summary ===\n");

   return SCIP_OKAY;
}

SCIP_RETCODE SDreadStructure(SCIP* scip) {

   SCIPdbgMsg("building fresh structure\n");

   SCIP_CONSHDLR** conshdlrs;
   SCIP_PROBDATA* probdata;

   std::map<int, std::multiset<int> > controlVarTimes; /* Keeps track of the constraint times in which control variables appear */
   std::map<int, SCIP_VAR* > controlVarPointers; /* Saves variable pointers and  and indices for control variables */

   int nconshdlrs;
   int i,v;
   bool reformulated(false);
   int sdVarIdTmp = 0;
   assert(scip != NULL);

   /* Get propdata */
   probdata = SCIPgetProbData(scip);
   assert(probdata != NULL);
   sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);

   SCIPdbgMsg("entered SDrefreshStructure, got probdata and structure\n");
   //SCIPprintTransProblem(scip,NULL,"cip",false);

   /* Empty everything */
   structure->clear();

   // Iterate over all constraints and look for time tags
   nconshdlrs = SCIPgetNConshdlrs(scip);
   conshdlrs = SCIPgetConshdlrs(scip);
   assert(nconshdlrs == 0 || conshdlrs != NULL);
   //TODO _SD: Check if there were changes during presolving and update structure
   //assert(SCIPisTransformed(scip));


/* loop through all () constraint handlers */
   for( i = 0; i < nconshdlrs && !reformulated; ++i )
   {
      int nconss;
      int c;
      SCIP_CONS** conss;
      SCIP_Bool success;
      assert(conshdlrs[i] != NULL);
      std::string conshdlrName(SCIPconshdlrGetName(conshdlrs[i]));

      SCIPdbgMsg("considering conshdlr %s\n",conshdlrName.c_str());

      assert ( SCIPconshdlrGetNConss(conshdlrs[i]) == 0
            || conshdlrName.compare(std::string("linear")) == 0
            || conshdlrName.compare(std::string("varbound")) == 0
            || conshdlrName.compare(std::string("quadratic")) == 0
            || conshdlrName.compare(std::string("abspower")) == 0
            || conshdlrName.compare(std::string("nonlinear")) == 0
            || conshdlrName.compare(std::string("SOS2")) == 0  );


      SCIPdbgMsg("conshdlr has %i cons\n",SCIPconshdlrGetNConss(conshdlrs[i]));
      SCIPdbgMsg("conshdlr has %i active cons\n",SCIPconshdlrGetNActiveConss(conshdlrs[i]));
         nconss = SCIPconshdlrGetNActiveConss(conshdlrs[i]);
         conss = SCIPconshdlrGetConss(conshdlrs[i]);

         assert(nconss == 0 || conss != NULL);

         SCIPdbgMsg("checking %d %s constraints\n",nconss,conshdlrName.c_str());

         /* iterating over constraints to determine the order that corresponds to control problem structure FROM VARIABLE NAMES */
         for( c = 0; c < nconss && !reformulated; ++c )
         {

            std::string consFullName(SCIPconsGetName(conss[c]));
            /* Check if this is a nlreform constraint */
            if (std::string("nlreform").compare(0,8,consFullName,0,8) == 0)
            {
              SCIPdebugMessage("found nlreform constraint %s, skipping this constraint refreshStructure\n", SCIPconsGetName(conss[c]));
              reformulated = true;
              continue;
            }

            int nConsVars;
            SCIP_CALL( SCIPgetConsNVars(scip, conss[c], &nConsVars, &success) );
            assert(success);
            if (nConsVars != 0) //Constraint without variables will not be treated
            {
               SCIP_VAR** consvars;

               boost::cmatch matches;
               SCIPdbgMsg("Considering constraint %s\n",consFullName.c_str());
               SCIPdbg( SCIP_CALL_ABORT( SCIPprintCons(scip, conss[c], NULL) ) );
               SCIPdbg( SCIPinfoMessage(scip, NULL, ";\n") );

               if (boost::regex_match(consFullName.c_str(), matches, structure->getConsRegex()))
               {
                  /* First step: Try to classify the constraint (explicit, implicit, multistep) */

                  /* Explanation: timeNVarsMap[key] = value:  the constraints contains >value< variables of time >key< */
                  IntIntMap timeNVarsMap;

                  std::string consName(matches[1].first,matches[1].second);
                  std::string consLevelString(matches[2].first,matches[2].second);
                  std::string consTypeString(matches[3].first,matches[3].second);
                  std::string consTimeString(matches[5].first,matches[5].second);
                  SCIPdbgMsg("consName is %s\n",consName.c_str());
                  SCIPdbgMsg("consTimeString is %s\n",consTimeString.c_str());
                  SCIPdbgMsg("consLevelString is %s\n",consLevelString.c_str());
                  SCIPdbgMsg("consTypeString is %s\n",consTypeString.c_str());


                  unsigned int consTime = atoi(consTimeString.c_str());
                  unsigned int consLevel = 0;
                  sdscip::SDproblemStructureInterface::SD_CONS_TYPE consType = sdscip::SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS;

                  if (consLevelString.compare(std::string("")) != 0)
                     consLevel = atoi(consLevelString.c_str());
                  if (consTypeString.compare(std::string("")) != 0)
                     consType= sdscip::SDproblemStructureInterface::SD_CONS_TYPE(atoi(consTypeString.c_str()));

                  SCIP_VAR* explicitVar;
                  SCIP_VAR* algebraicForwardVar = NULL;

                  SCIPcppDbgMsg("Matched expression, time is " << consTimeString << std::endl);
                  SCIPcppDbgMsg("Type is " << consType << std::endl);


                  //Getting this constraints variable number and variables
                  SCIP_CALL( SCIPallocBufferArray(scip, &consvars, nConsVars) );
                  SCIP_CALL( SCIPgetConsVars(scip, conss[c], consvars, nConsVars, &success) );

                  int nVarsAtLatestTime = 0;
                  unsigned int latestTime = 0;
                  // Iterate over variables to build varTimeMap
                  for( v = 0; v < nConsVars; v++ )
                  {
                     std::string varFullName(SCIPvarGetName(consvars[v]));

                     if (std::string("nlreform").compare(0,8,varFullName,0,8) == 0)
                     {
                       SCIPdebugMessage("found nlreform variable %s, ignoring\n", SCIPvarGetName(consvars[v]));
                       reformulated = true;
                       structure->setIsReformulated(true);
                       //assert(false);
                       //SCIPfreeBufferArray(scip, &consvars);
                       continue;
                       //return SCIP_OKAY;
                     }

                     assert(boost::regex_match(consFullName.c_str(), matches, structure->getConsRegex())); //This equation can not (yet) contain time-independent variables

                     SCIPdbgMsg("--------considering variable %s\n",varFullName.c_str());

                     if (boost::regex_match(varFullName.c_str(), matches, structure->getVarRegex() ))
                     {
                        sdscip::SDproblemStructureInterface::SD_VAR_TYPE  type = sdscip::SDproblemStructureInterface::ALGEBRAIC;
                        std::string varName(matches[1].first,matches[1].second);
                        std::string varTimeString(matches[5].first,matches[5].second);
                        std::string varControlString(matches[2].first,matches[2].second);
                        std::string varLevelString(matches[3].first,matches[3].second);
                        std::string varTypeString(matches[4].first,matches[4].second);
                        /*
                        SCIPdbgMsg("varName is %s\n",varName.c_str());
                        SCIPdbgMsg("varTimeString is %s\n",varTimeString.c_str());
                        SCIPdbgMsg("varControlString is %s\n",varControlString.c_str());
                        SCIPdbgMsg("varLevelString is %s\n",varLevelString.c_str());
                        SCIPdbgMsg("varTypeString is %s\n",varTypeString.c_str());
                         */
                        SCIPdbgMsg("matched varname\n");
                        unsigned int varTime = atoi(varTimeString.c_str());
                        if (varControlString.compare("c")== 0)
                        {
                           /* TODO _SD: The way control variables are saved in variable types is confusing
                            * need a redo of variableTypes anyway...
                            */
                           SCIPdebugMessage("found control variable %s\n",SCIPvarGetName(consvars[v]));
                           type = sdscip::SDproblemStructureInterface::CONTROL; //control variable
                        }
                        else
                        {
                           if (timeNVarsMap.count(varTime))
                              timeNVarsMap[varTime]++;
                           else
                              timeNVarsMap[varTime] = 1;

                           //Save the number of variables at the latest (highest) time for later
                           if (varTime >= latestTime) {
                              nVarsAtLatestTime = timeNVarsMap[varTime];
                              latestTime = varTime;
                              SCIPdbgMsg("new nVarsAtLatestTime is %i at time %i\n",nVarsAtLatestTime,varTime);
                           }
                           //We will need the pointer to the only (!) time-forward variable if the constraint is explicit
                           if (varTime == consTime) {
                              explicitVar = consvars[v];
                              SCIPdbgMsg("identified explicit var: %s\n",SCIPvarGetName(explicitVar));
                           }

                           //This might be a forward variable of an algebraic constraint?
                           SCIPdbgMsg("checking for forward variable, comparing %s with %s\n",varName.c_str(),consName.c_str());
                           if (varName.compare(consName) == 0 && varTime == consTime) {
                              SCIPdbgMsg("identified forward algebraic(?) variable %s\n",varName.c_str());
                              algebraicForwardVar = consvars[v];
                              SCIPdbgMsg("pointer goes to %s\n",SCIPvarGetName(algebraicForwardVar));
                           }
                        }

                        //Add variable to bookkeeping as algebraic or control (will be updated to differential during constraint type detection if necessary)
                        // or to counting of control variables
                        if (type == sdscip::SDproblemStructureInterface::CONTROL)
                        {

                              SCIPdebugMessage("pushing var %s into controlVarTimes map at time %i\n", SCIPvarGetName(consvars[v]), consTime);
                              controlVarTimes[SCIPvarGetIndex(consvars[v])].insert(consTime);
                              controlVarPointers[SCIPvarGetIndex(consvars[v])] = consvars[v];
                        }
                        else
                           structure->addVariable(SCIPvarGetIndex(consvars[v]), consvars[v], varTime, type, /*TODO: Proper varId*/ sdVarIdTmp++);
                     }
                     else
                     {
                        SCIPwarningMessage(scip, "variable %s did not match varregex\n",varFullName.c_str());
                     }

                  }
                  SCIPfreeBufferArray(scip, &consvars);

                  /* 2. Step : Evaluate varTimeMap to decide constraint type */
                  assert(timeNVarsMap.size() > 0);        //There must be variables in constraint
                  //assert(varTimeMap.size() < 3);        //So far no multistep methods

                  if (timeNVarsMap.size() == 1) //algebraic constraint
                  {
                     assert(timeNVarsMap.count(consTime) != 0);

                     /* Add constraint with time to bookkeeping of constraint handler */
                     SCIPdbgMsg("Adding cons %s at time= %i, level=%i, type=%i\n",SCIPconsGetName(conss[c]), consTime, consLevel, consType);
                     structure->addAlgebraicCons(conss[c], algebraicForwardVar, consTime, consLevel, consType, /*TODO:PROPER VAR_ID*/sdVarIdTmp++);
                  }
                  else if (timeNVarsMap.size() >= 2) //single or multi-step differential explicit or implicit
                  {
                     //Distinguish explicit from implicit multi-step methods by evaluating nVarsAtLatestTime
                     if (nVarsAtLatestTime == 1)  //Explicit
                     {
                        SCIPdebugMessage("Identified explicit %s constraint %s with forward Variable %s\n",conshdlrName.c_str(),consFullName.c_str(),SCIPvarGetName(explicitVar));

                        structure->addExplicitDifferential(conss[c],explicitVar,SCIPvarGetIndex(explicitVar),consTime, /*TODO:PROPER VAR_ID*/sdVarIdTmp++);
                     }
                     else //implicit scheme
                     {
                        SCIPdebugMessage("Identified implicit %s constraint %s - not yet supported, bailing out\n",conshdlrName.c_str(),consFullName.c_str());
                        assert(FALSE);
                     }
                  }
                  else
                  {
                     SCIPdbgMsg("size of timeNvarsmap is %i\n",(int) timeNVarsMap.size());
                     assert(false);
                  }
               } //Close Constraint matched regular expression for transcribed control problems
               else
               {
                  if (consFullName.compare(0,7,"propcut") == 0)
                  {
                     SCIPdbgMsg("Found propcut, ignoring in structure\n");
                  }
                  else
                  {
                	  SCIPdbgMsg("could not match name of constraint %s\n",consFullName.c_str());
                	  assert(false);
                  }

               }
            } //Close constraint has variables
         } //Close loop over constraints
   } //Close loop over constraint handlers

   /* Iterate over control variables and add at to structure */
   if (reformulated)
   {
      SCIP_CALL( structure->setIsReformulated(reformulated) );
   }
   else
   {
      //SCIPdbgMsg("adding control variables at times of first occurance\n");
      for (std::map<int, std::multiset<int> >::const_iterator varIter= controlVarTimes.begin(); varIter != controlVarTimes.end(); ++varIter)
      {
         int index(varIter->first);
         int varTime = *varIter->second.begin();
         int lastVarTime = *varIter->second.rbegin();
         //SCIPdbgMsg("pushing variable %s into controlVariables at times %i -> %i\n",SCIPvarGetName(controlVarPointers[index]),varTime,lastVarTime);
         SCIP_CALL( structure->addControlVar(controlVarPointers[index], index, varTime, lastVarTime, /*TODO:PROPER VAR_ID*/sdVarIdTmp++) );
      }
   }

   SCIPdebugMessage("done reading structure\n");
   structure->doneReading();

   SCIP_Bool check;
   SCIP_CALL( SCIPgetBoolParam(scip ,"sd/checkStructure", &check) );
   if( check ) {
      SCIPinfoMessage(scip, NULL, "\n=== Performing structure checks ===\n");
      checkStructure(scip);
   }

   return SCIP_OKAY;
}





SCIP_RETCODE SDcheckStructure(SCIP* scip)
{
   return checkStructure(scip);


}


SCIP_RETCODE SDprintStructure(SCIP* scip)
{
   SDensureValidStructure( scip );

   //Get propdata
   SCIP_PROBDATA *probdata = SCIPgetProbData(scip);
   assert(probdata != NULL);
   sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);
   int nParamsPerTime = structure->getNParamsPerTime();

   SCIPinfoMessage(scip, NULL, "\n=== Printing full structure data ===\n");

   for (int currentTime = structure->startTimeIteration(); structure->timesLeft(); currentTime = structure->incrementTime())
   {
      SCIPinfoMessage(scip,NULL, "t = %i\n",currentTime );
      //if (timeIt != (*probdata->explicitDifferential).begin())
      {
         //List Variables in this time step with times
         SCIPinfoMessage(scip, NULL, "Variables in t=%i\n",currentTime);
         {
            for (structure->startVarIteration(); structure->varsLeft();structure->incrementVar())
            {
               sdscip::SDVarBasic var = structure->getCurrentVar();
               SCIPinfoMessage(scip,NULL,"   Var: %s, Type: %i",SCIPvarGetName(var.getScipVariable()) ,var.getType());
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         //List identified control Variables in this time step
         SCIPinfoMessage(scip, NULL, "Control Variables in t=%i\n",currentTime);
         {
            for (structure->startControlVarIteration(); structure->controlVarsLeft();structure->incrementControlVar())
            {
               SCIPinfoMessage(scip,NULL,"   Control Var: %s",SCIPvarGetName(structure->getControlVar()));
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         //List identified control Variables in this time step
         SCIPinfoMessage(scip, NULL, "ControlVarsAtT at in t=%i\n",currentTime);
         {
            for (structure->startControlVarAtTIteration(currentTime); structure->controlVarsAtTLeft(currentTime);structure->incrementControlVarAtT())
            {
               SCIPinfoMessage(scip,NULL,"   Control Var: %s",SCIPvarGetName(structure->getControlVarAtTOrig()));
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         SCIPinfoMessage(scip, NULL, "Cuts found for states at t=%i\n",currentTime);
         {
            for (structure->startCutIteration(); structure->cutsLeft(); structure->incrementCut())
            {
               SCIP_CONS* cut(structure->getCut());
               assert(!SCIPconsIsDeleted(cut));
               SCIP_CALL_ABORT( SCIPprintCons(scip, cut, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         SCIPinfoMessage(scip, NULL, "Explicit Differential Constraints connecting t=%i with t=%i\n",currentTime - 1, currentTime);
         //Iterate over vector with links to constraints
         {

            for (structure->startDiffConsIteration(); structure->diffConsLeft(); structure->incrementDiffCons())
            {
               SCIP_CONS * cons(structure->getDiffConsCons());
               if(cons != nullptr) {
                  assert(!SCIPconsIsDeleted(cons));
                  SCIP_CALL_ABORT( SCIPprintCons(scip, cons, NULL) );
                  SCIPinfoMessage(scip, NULL, ";\n");
               }
            }
         }


         SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (simple list, used for problem construction)\n",currentTime);
         //Iterate over vector with links to algebraic constraints
         {
            //TODO: Return iterator from structure instead of managing it in structure
            //for (auto it = structure->algebraicConsBegin(); it != strucutre-algebraicConsEnd(); ++ it)
            for (structure->startAlgebraicConsIteration(currentTime); structure->algebraicConsLeft(currentTime); structure->incrementAlgebraicCons())
            {
               SCIP_CONS* cons(structure->getAlgebraicCons());
               SCIP_VAR* var(structure->getAlgebraicVar());
               //assert(!SCIPconsIsDeleted(cons));
               if (SCIPconsIsDeleted(cons)) {
                  SCIPinfoMessage(scip, NULL, "DELETED cons: ");
               }
               SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(cons),SCIPvarGetName(var));
               SCIP_CALL_ABORT( SCIPprintCons(scip, cons, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (detailed list, used for solving in maxctrl heuristic)\n",currentTime);
         for (structure->startLevelIteration(); structure->levelsLeft();structure->incrementLevel())
         {
            int level(structure->getCurrentLevel());
            int type(structure->getCurrentLevelType());
            SCIPinfoMessage(scip, NULL, "   level: %i, type: %i, \n",level, type);
            for (structure->startLevelConsIteration(); structure->levelConsLeft(); structure->incrementLevelCons())
            {
               if (structure->currentLevelConsHasVar())
               {
                  SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(structure->getCurrentLevelConsCons()),SCIPvarGetName(structure->getCurrentLevelConsVar()));
               }
               else if (level == 8) //SOS2-Implemented  Lookup table
               {
                  if (structure->currentLevelConsHasVar())
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(structure->getCurrentLevelConsCons()),SCIPvarGetName(structure->getCurrentLevelConsVar()));
                  }
                  else
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(structure->getCurrentLevelConsCons()));
                  }
               }
               else
               {
                  SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(structure->getCurrentLevelConsCons()));
               }
               SCIP_CALL_ABORT( SCIPprintCons(scip, structure->getCurrentLevelConsCons(), NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }

         }

         if( nParamsPerTime != 0)
         {
            SCIPinfoMessage(scip, NULL, "Parameters at time %i \n",currentTime);
            SCIP_Real* params = structure->getXdotParams(currentTime);
            for (int i = 0; i < nParamsPerTime; ++i)
            {
               SCIPinfoMessage(scip, NULL, "%f,\n", params[i]);
            }
         }


#if 0
         SCIPinfoMessage(scip, NULL, "Cuts found for states at t=%i\n",timeIt->first);
         {
            std::vector<SCIP_CONS*>::iterator consIt;
            for ( consIt = (*probdata->propCuts)[timeIt->first].begin(); consIt != (*probdata->propCuts)[timeIt->first].end(); ++consIt)
            {
               assert(!SCIPconsIsDeleted(*consIt));
               SCIP_CALL_ABORT( SCIPprintCons(scip, *consIt, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

#endif


#if 0
         LevelConsMap::iterator levelIt;
         for ( levelIt = (*probdata->algebraicConstraints)[timeIt->first-1].begin(); levelIt != (*probdata->algebraicConstraints)[timeIt->first-1].end(); ++levelIt)
         {
            SCIPinfoMessage(scip, NULL, "   level: %i, type: %i, \n",levelIt->first,(levelIt->second).first);

            ConsVarVec::iterator consIt;
            for ( consIt = (levelIt->second).second.begin(); consIt != (levelIt->second).second.end(); ++consIt)
            {
               if ((levelIt->second).first == 0)
               {
                  SCIPdbgMsg("constraint name is %s\n",SCIPconsGetName(consIt->first));
                  SCIPdbgMsg("variable name is %s\n",SCIPvarGetName(consIt->second));

                  SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),SCIPvarGetName(consIt->second));
               }
               else if ((levelIt->second).first == 8) //SOS2-Implemented  Lookup table
               {
                  if (consIt->second != NULL)
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),""); //SCIPvarGetName(consIt->second));
                  }
                  else
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
                  }
               }
               else
               {
                  SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
               }
               SCIP_CALL_ABORT( SCIPprintCons(scip, consIt->first, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }

         }
#endif
      }
   }

#if 0

   ExplicitDifferentialMap::iterator timeIt;
   //Iterate over Map elements (order is handled by map internally in ascending time order)
   for (timeIt = (*probdata->explicitDifferential).begin(); timeIt != (*probdata->explicitDifferential).end(); timeIt++) {
      SCIPinfoMessage(scip,NULL, "t = %i\n",timeIt->first );
      //if (timeIt != (*probdata->explicitDifferential).begin())
      {
         //List Variables in this time step with times
         SCIPinfoMessage(scip, NULL, "Variables in t=%i\n",timeIt->first -1);
         {
            std::map<unsigned int, IntVarPair >::iterator pairIt;
            for ( pairIt = (*probdata->variableTypes)[timeIt->first- 1].begin(); pairIt != (*probdata->variableTypes)[timeIt->first -1 ].end(); ++pairIt)
            {
               SCIPinfoMessage(scip,NULL,"   Var: %s, Type: %i",SCIPvarGetName((pairIt->second).second),pairIt->second.first);
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         //List identified control Variables in this time step
         SCIPinfoMessage(scip, NULL, "Control Variables in t=%i\n",timeIt->first -1);
         {
            VarVec::iterator vecIt;
            for ( vecIt = (*probdata->controlVariables)[timeIt->first- 1].begin(); vecIt != (*probdata->controlVariables)[timeIt->first -1 ].end(); ++vecIt)
            {
               SCIPinfoMessage(scip,NULL,"   Control Var: %s",SCIPvarGetName(*vecIt));
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (simple list, used for problem construction)\n",timeIt->first - 1);
         //Iterate over vector with links to algebraic constraints
         {
            std::vector<SCIP_CONS*>::iterator consIt;
            for ( consIt = (*probdata->algebraic)[timeIt->first-1].begin(); consIt != (*probdata->algebraic)[timeIt->first-1].end(); ++consIt)
            {

               assert(!SCIPconsIsDeleted(*consIt));
               SCIP_CALL_ABORT( SCIPprintCons(scip, *consIt, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }
         SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (detailed list, used for solving in maxctrl heuristic)\n",timeIt->first - 1);
         LevelConsMap::iterator levelIt;
         for ( levelIt = (*probdata->algebraicConstraints)[timeIt->first-1].begin(); levelIt != (*probdata->algebraicConstraints)[timeIt->first-1].end(); ++levelIt)
         {
            SCIPinfoMessage(scip, NULL, "   level: %i, type: %i, \n",levelIt->first,(levelIt->second).first);
            ConsVarVec::iterator consIt;
            for ( consIt = (levelIt->second).second.begin(); consIt != (levelIt->second).second.end(); ++consIt)
            {
               if ((levelIt->second).first == 0)
               {
                  SCIPdbgMsg("constraint name is %s\n",SCIPconsGetName(consIt->first));
                  SCIPdbgMsg("variable name is %s\n",SCIPvarGetName(consIt->second));

                  SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),SCIPvarGetName(consIt->second));
               }
               else if ((levelIt->second).first == 8) //SOS2-Implemented  Lookup table
               {
                  if (consIt->second != NULL)
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),""); //SCIPvarGetName(consIt->second));
                  }
                  else
                  {
                     SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
                  }
               }
               else
               {
                  SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
               }
               SCIP_CALL_ABORT( SCIPprintCons(scip, consIt->first, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }

         }

         SCIPinfoMessage(scip, NULL, "Explicit Differential Constraints connecting t=%i with t=%i\n",timeIt->first - 1, timeIt->first);
         //Iterate over vector with links to constraints
         {
            ConsVarVec::iterator pairIt;
            for ( pairIt = timeIt->second.begin(); pairIt != timeIt->second.end(); ++pairIt)
            {
               assert(!SCIPconsIsDeleted(pairIt->first));
               SCIP_CALL_ABORT( SCIPprintCons(scip, pairIt->first, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

         SCIPinfoMessage(scip, NULL, "Cuts found for states at t=%i\n",timeIt->first);
         {
            std::vector<SCIP_CONS*>::iterator consIt;
            for ( consIt = (*probdata->propCuts)[timeIt->first].begin(); consIt != (*probdata->propCuts)[timeIt->first].end(); ++consIt)
            {
               assert(!SCIPconsIsDeleted(*consIt));
               SCIP_CALL_ABORT( SCIPprintCons(scip, *consIt, NULL) );
               SCIPinfoMessage(scip, NULL, ";\n");
            }
         }

      } //Close omit-first-step-clause
   }
   timeIt = (*probdata->explicitDifferential).end();
   timeIt--;

   SCIPinfoMessage(scip, NULL, "Algebraic Constraints in last step t=%i\n",timeIt->first);
   //Iterate over vector with links to algebraic constraints
   /*
   std::vector<SCIP_CONS*>::iterator consIt;
   for ( consIt = (*probdata->algebraic)[timeIt->first].begin(); consIt != (*probdata->algebraic)[timeIt->first].end(); ++consIt)
   {
      assert(!SCIPconsIsDeleted(*consIt));
      SCIP_CALL_ABORT( SCIPprintCons(scip, *consIt, NULL) );
      SCIPinfoMessage(scip, NULL, ";\n");
   }
   */
   LevelConsMap::iterator levelIt;
   for ( levelIt = (*probdata->algebraicConstraints)[timeIt->first].begin(); levelIt != (*probdata->algebraicConstraints)[timeIt->first].end(); ++levelIt)
   {
      SCIPinfoMessage(scip, NULL, "   level: %i, type: %i, \n",levelIt->first,(levelIt->second).first);
      ConsVarVec::iterator consIt;
      for ( consIt = (levelIt->second).second.begin(); consIt != (levelIt->second).second.end(); ++consIt)
      {
         if ((levelIt->second).first == 0)
         {
            SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),SCIPvarGetName(consIt->second));
         }
         else
         {
            SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
         }
         SCIP_CALL_ABORT( SCIPprintCons(scip, consIt->first, NULL) );
         SCIPinfoMessage(scip, NULL, ";\n");
      }

   }


   SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (simple list, used for problem construction)\n",timeIt->first);
   //Iterate over vector with links to algebraic constraints
   {
	   std::vector<SCIP_CONS*>::iterator consIt;
	   for ( consIt = (*probdata->algebraic)[timeIt->first].begin(); consIt != (*probdata->algebraic)[timeIt->first].end(); ++consIt)
	   {

		   assert(!SCIPconsIsDeleted(*consIt));
		   SCIP_CALL_ABORT( SCIPprintCons(scip, *consIt, NULL) );
		   SCIPinfoMessage(scip, NULL, ";\n");
	   }
   }
   SCIPinfoMessage(scip, NULL, "Algebraic Constraints preparing in t=%i (detailed list, used for solving in maxctrl heuristic)\n",timeIt->first);
   for ( levelIt = (*probdata->algebraicConstraints)[timeIt->first].begin(); levelIt != (*probdata->algebraicConstraints)[timeIt->first].end(); ++levelIt)
   {
	   SCIPinfoMessage(scip, NULL, "   level: %i, type: %i, \n",levelIt->first,(levelIt->second).first);
	   ConsVarVec::iterator consIt;
	   for ( consIt = (levelIt->second).second.begin(); consIt != (levelIt->second).second.end(); ++consIt)
	   {
		   if ((levelIt->second).first == 0)
		   {
			   SCIPdbgMsg("constraint name is %s\n",SCIPconsGetName(consIt->first));
			   SCIPdbgMsg("variable name is %s\n",SCIPvarGetName(consIt->second));

			   SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),SCIPvarGetName(consIt->second));
		   }
		   else if ((levelIt->second).first == 8) //SOS2-Implemented  Lookup table
		   {
			   if (consIt->second != NULL)
			   {
				   SCIPinfoMessage(scip, NULL, "      Constraint: %s ----> %s\n    ",SCIPconsGetName(consIt->first),""); //SCIPvarGetName(consIt->second));
			   }
			   else
			   {
				   SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
			   }
		   }
		   else
		   {
			   SCIPinfoMessage(scip, NULL, "      Constraint: %s \n    ",SCIPconsGetName(consIt->first));
		   }
		   SCIP_CALL_ABORT( SCIPprintCons(scip, consIt->first, NULL) );
		   SCIPinfoMessage(scip, NULL, ";\n");
	   }

   }



   //List Variables in this time step with times
   SCIPinfoMessage(scip, NULL, "Variables in last Step t=%i\n",timeIt->first);
   {
      std::map<unsigned int, IntVarPair >::iterator pairIt;
      for ( pairIt = (*probdata->variableTypes)[timeIt->first].begin(); pairIt != (*probdata->variableTypes)[timeIt->first].end(); ++pairIt)
      {
         SCIPinfoMessage(scip,NULL,"   Var: %s, Type: %i",SCIPvarGetName((pairIt->second).second),pairIt->second.first);
         SCIPinfoMessage(scip, NULL, ";\n");
      }
   }

   //List identified control Variables in last time step
   SCIPinfoMessage(scip, NULL, "Control Variables in t=%i\n",timeIt->first );
   {
      VarVec::iterator vecIt;
      for ( vecIt = (*probdata->controlVariables)[timeIt->first].begin(); vecIt != (*probdata->controlVariables)[timeIt->first].end(); ++vecIt)
      {
         SCIPinfoMessage(scip,NULL,"   Control Var: %s",SCIPvarGetName(*vecIt));
         SCIPinfoMessage(scip, NULL, ";\n");
      }
   }

#endif
   SCIPinfoMessage(scip, NULL, "Done printing\n");
   return SCIP_OKAY;
}


SCIP_RETCODE SDaddConsWithVars(SCIP_CONS* currentCons, SCIP* scip, SCIP* subscip,SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, SCIP_Bool noObj, SCIP_Bool global, std::map<SCIP_VAR*, SCIP_Real>* solMap, SCIP_Bool copysol)
{
   int nConsVars;
   SCIP_VAR** consvars;
   SCIP_Bool success;
   SCIP_CONS* targetcons = NULL;
   SCIP_SOL* scipSol;

   assert(currentCons != NULL);
   assert(scip != NULL);
   assert(subscip != NULL);
   assert(varmap != NULL);
   assert(consmap != NULL);

   scipSol = SCIPgetBestSol(scip);

   SCIPdebugMessage("adding cons with Vars from scip in stage %i\n",SCIPgetStage(scip));

    //Add constraint to subscip

   SCIP_CONSHDLR* conshdlr;
   conshdlr = SCIPconsGetHdlr(currentCons);
   SCIP_CALL( SCIPgetConsCopy(scip, subscip, currentCons, &targetcons, conshdlr, varmap, consmap, NULL,
         SCIPconsIsInitial(currentCons), SCIPconsIsSeparated(currentCons),
         SCIPconsIsEnforced(currentCons), SCIPconsIsChecked(currentCons),
         SCIPconsIsPropagated(currentCons), FALSE, SCIPconsIsModifiable(currentCons),
         SCIPconsIsDynamic(currentCons), SCIPconsIsRemovable(currentCons), FALSE, TRUE, &success) );


   /* Set original bounds in target scip from local/global bounds in source scip
    * necessary, since the this runs in the presolving of the source scip only original bounds are copied */
   SCIP_CALL( SCIPgetConsNVars(scip, currentCons, &nConsVars, &success) );
   assert(success);
   SCIP_CALL( SCIPallocBufferArray(scip, &consvars, nConsVars) );
   SCIP_CALL( SCIPgetConsVars(scip, currentCons, consvars, nConsVars, &success) );
   assert(success);
   for( int v = 0; v < nConsVars; v++ )
   {
      SCIPdbgMsg("considering %s variable %s %p\n",SCIPvarIsOriginal(consvars[v]) ? "original" : "transformed", SCIPvarGetName(consvars[v]), (void*) consvars[v]);
      SCIP_VAR* sourcevar = consvars[v];
      SCIP_VAR* targetvar = (SCIP_VAR*) SCIPhashmapGetImage(varmap,consvars[v]);

      assert(targetvar != NULL);
      SCIPdbgMsg("lhs = %e\n",(global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)));
      SCIPdbgMsg("rhs = %e\n",(global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));
      SCIPdbgMsg("delta = %e\n",global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar) - global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar));
      assert((global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)) <= (global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));
      SCIPchgVarLb(subscip, targetvar, global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar));
      SCIPchgVarUb(subscip, targetvar, global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar));
      assert(SCIPisEQ(scip, SCIPvarGetLbLocal(targetvar), global ? SCIPvarGetLbGlobal(sourcevar) : SCIPvarGetLbLocal(sourcevar)));
      assert(SCIPisEQ(scip, SCIPvarGetUbLocal(targetvar), global ? SCIPvarGetUbGlobal(sourcevar) : SCIPvarGetUbLocal(sourcevar)));

      if (noObj)
         SCIP_CALL( SCIPchgVarObj(subscip,targetvar,0) );

      if (scipSol != NULL && copysol == TRUE)
      {
         SCIP_Real solVal = SCIPgetSolVal(scip,scipSol,consvars[v]);
         (*solMap)[targetvar] = solVal;
      }

   }
   SCIPfreeBufferArray(scip, &consvars); //TODO _SD allocating buffer outside of loop could increase performance?

   /* add the copied constraint to target SCIP if the copying process was valid */
   if( success )
   {
      SCIPdbgMsg("copied constraint %s to subscip\n",SCIPconsGetName(currentCons));
      assert(targetcons != NULL);
       /* add constraint to target SCIP */
       SCIP_CALL( SCIPaddCons(subscip, targetcons) );
       /* release constraint once for the creation capture */
       SCIP_CALL( SCIPreleaseCons(subscip, &targetcons) );
   }
   else
   {
      SCIPdebugMessage("failed to copy constraint %s\n", SCIPconsGetName(currentCons));
      assert(FALSE);
   }

   return SCIP_OKAY;
}

void SDsetIsReformulated(SCIP * scip, bool isReformulated)
{
	   SCIP_PROBDATA* probdata;
	   assert(scip != NULL);
	   //Get propdata
	   probdata = SCIPgetProbData(scip);
	   assert(probdata != NULL);
	   probdata->isReformulated = isReformulated;
}

bool SDgetIsReformulated(SCIP *scip)
{
	   SCIP_PROBDATA* probdata;
	   assert(scip != NULL);
	   //Get propdata
	   probdata = SCIPgetProbData(scip);
	   assert(probdata != NULL);
	   sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);

	   //return probdata->isReformulated ;
	   return structure->isReformulated();
}

void SDsetIsStructureValid(SCIP * scip, bool isValid)
{
	   SCIP_PROBDATA* probdata;
	   assert(scip != NULL);
	   //Get propdata
	   probdata = SCIPgetProbData(scip);
	   assert(probdata != NULL);
	   probdata->structure->setIsValid(isValid);
}

bool SDgetIsStructureValid(SCIP *scip)
{
	   SCIP_PROBDATA* probdata;
	   assert(scip != NULL);
	   //Get propdata
	   probdata = SCIPgetProbData(scip);
	   assert(probdata != NULL);
	   return probdata->structure->isValid();
}

SCIP_RETCODE SDprintStateVarNames(SCIP *scip)
{

   SCIPdbgMsg("printing state var names\n");
   SCIP_PROBDATA* probdata;
   assert(scip != NULL);
   //Get propdata
   probdata = SCIPgetProbData(scip);
   assert(probdata != NULL);
   std::string list(probdata->structure->getStateVarList());
   SCIPinfoMessage(scip, NULL, list.c_str());
   SCIPinfoMessage(scip, NULL, "\n");
   SCIPdbgMsg("returning\n");
   return SCIP_OKAY;
}


/* This method fixes a variable but previously sets epsilon to the smallest possible value
 * this makes sure that the varbounds saved in the expression graph are exactly
 * the same as the variable bounds
 */
SCIP_RETCODE SDfixVarProbingExact(SCIP* scip, SCIP_VAR* var, SCIP_Real fixVal) {
   assert(SCIPinProbing(scip));
   SCIP_Real oldEpsilon;

   /* Setting epsilon very small as above for non-forward variables */
   SCIP_CALL( SCIPgetRealParam(scip,"numerics/epsilon",&oldEpsilon) );
   SCIP_CALL( SCIPsetRealParam(scip,"numerics/epsilon",1e-20) );
   SCIP_CALL( SCIPfixVarProbing(scip,var,fixVal) );
   SCIP_CALL( SCIPsetRealParam(scip,"numerics/epsilon",oldEpsilon) );

   return SCIP_OKAY;
}


/*
 * dialog specific interface methods
 */

/** creates the setup dialog and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogSDinit(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: _SD (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */
   
   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, DIALOG_NAME) )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog, 
            NULL, dialogExecSDinit, NULL, NULL,
            DIALOG_NAME, DIALOG_DESC, DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );


   }

   return SCIP_OKAY;
}

/** creates the setup dialog and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogSDprintStructure(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, "sdPrintStructure") )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecSDprintStructure, NULL, NULL,
            "sdPrintStructure", "print SD Problem Strcuture", DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );

   }

   return SCIP_OKAY;
}

/** creates the setup dialog and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogSDensureValidStructure(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, "sdEnsureValidStructure") )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecSDensureValidStructure, NULL, NULL,
            "sdEnsureValidStructure", "ensure SD Problem Structure is valid", DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );

   }

   return SCIP_OKAY;
}

/** forces a refresh of problem structure */
SCIP_RETCODE SCIPincludeDialogSDrefreshStructure(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, "sdRefreshStructure") )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecSDrefreshStructure, NULL, NULL,
            "sdRefreshStructure", "forces a refresh of problem Structure", DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );

   }
   return SCIP_OKAY;
}


/** creates the setup dialog and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogSDdoSomething(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, "sdDoSomething") )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecSDdoSomething, NULL, NULL,
            "sdDoSomething", "used for testing of methods in sd plugin", DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );

   }
   return SCIP_OKAY;
}

/** creates the setup dialog and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogSDdisable(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, "sdDisable") )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecSDdisable, NULL, NULL,
            "sdDisable", "used for testing of methods in sd plugin", DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );

   }
   return SCIP_OKAY;
}




sdscip::SDproblemStructureInterface* SDgetStructure(SCIP* scip)
{
   SCIP_PROBDATA* probdata;
   probdata = SCIPgetProbData(scip);
   assert(probdata != NULL);
   if( SCIPgetStage(scip) > SCIP_STAGE_TRANSFORMED &&
       !probdata->structure->isTranformed() )
      probdata->structure->setIsTransformed(true);

   return probdata->structure;
}


/** creates the writeTransprobSD and includes it in SCIP */
SCIP_RETCODE SCIPincludeDialogWriteTransprobSD(
   SCIP*                 scip                /**< SCIP data structure */
   )
{

   SCIP_DIALOG* dialog;
   SCIP_DIALOG* parentdialog;

   /** includes or updates the default dialog menus in SCIP */
   SCIP_CALL( SCIPincludeDialogDefault(scip) );

   /* get parent dialog */
   parentdialog = SCIPgetRootDialog(scip);
   assert(parentdialog != NULL);
   /* TODO: _SD (optional) change parent dialog from root dialog to another existing dialog (needs to be a menu) */

   /* create, include, and release dialog */
   if( !SCIPdialogHasEntry(parentdialog, DIALOG_WRITE_NAME) )
   {
      SCIP_CALL( SCIPincludeDialog(scip, &dialog,
            NULL, dialogExecWriteTransprobSD, NULL, NULL,
            DIALOG_WRITE_NAME, DIALOG_DESC, DIALOG_ISSUBMENU, NULL) );
      SCIP_CALL( SCIPaddDialogEntry(scip, parentdialog, dialog) );
      SCIP_CALL( SCIPreleaseDialog(scip, &dialog) );
   }

   return SCIP_OKAY;
}

/** includes sdscip */
SCIP_RETCODE SCIPaddParamsSD(
   SCIP*                 scip                /**< SCIP data structure */
)
{

   SCIPdbgMsg("adding parameters");
   /* Add parameters concerning problem data */
   SCIPaddIntParam(scip,
      "sd/problemStructureVersion",
      "Which version of the problemStructure Class should be loaded",
      NULL, FALSE, 1, 0, INT_MAX, NULL, NULL);

   return SCIP_OKAY;
}




