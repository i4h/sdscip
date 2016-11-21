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

/**@file   BranchControlFirst.cpp
 * @brief  Branching rule for SDO problems, selecting control variables first
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#include "BranchControlFirst.h"
#include "ProbDataSD.h"

using namespace sdscip;

SCIP_DECL_BRANCHEXECLP(BranchruleControlFirst::scip_execlp)
{
	SCIPdbgMsg("entering BranchControlFirst execlp\n");
		assert(result != NULL);
	*result = SCIP_DIDNOTRUN;
	return SCIP_OKAY;
}

/** branching execution method for external candidates
 *
 *  @see SCIP_DECL_BRANCHEXECEXT(x) in type_branch.h of SCIP
 */
SCIP_DECL_BRANCHEXECEXT(BranchruleControlFirst::scip_execext)
{  /*lint --e{715}*/
   SCIP_NODE* downchild;
   SCIP_NODE* eqchild;
   SCIP_NODE* upchild;
   SCIP_Real brpoint;

   *result = SCIP_DIDNOTRUN;

   int depth = SCIPgetDepth( scip );

	SCIPdbgMsg("entering BranchControlFirst execext, depth = %i\n",depth);
	/*
	std::ostringstream oss;
	oss << "bnbtransprob"<< "_" << depth << ".cip";
	SCIPdbgMsg("WRITING transformed problem to file %s\n",oss.str().c_str());
	SCIPwriteTransProblem(scip, oss.str().c_str(), std::string("cip").c_str(), false);
	 */
	if (depth < 100)
	{
	   SCIPdbgMsg("branching in depth %i, picking  %i th control var\n", depth, depth);
	   /* Spatial branching on the first appearing control */
	   /* Get the first control here */
	   sdscip::SDproblemStructureInterface* structure(SDgetStructure(scip));
	   SCIP_VAR* branchVar(structure->getNthsControlVar(depth));

	   /* Break if no control var was returned */
	   if (branchVar != NULL)
	   {
	      SCIPdebugMessage("branching on control %s in depth %i\n",SCIPvarGetName(branchVar),depth);
	      brpoint = SCIPvarGetLbLocal(branchVar) + 0.5 * (SCIPvarGetUbLocal(branchVar) - SCIPvarGetLbLocal(branchVar) );

	      SCIPdbgMsg(" -> selected variable <%s> , branching point=%g\n", SCIPvarGetName(branchVar), brpoint);

	      /* perform the branching */
	      SCIP_CALL( SCIPbranchVarVal(scip, branchVar, brpoint, &downchild, &eqchild, &upchild) );
	      if (downchild == NULL)
	      {
	         SCIPdbgMsg("downchild is NULL\n");
	      }
	      if (upchild == NULL)
	      {
	         SCIPdbgMsg("upchild is NULL\n");
	      }
	      if (eqchild == NULL)
	      {
	         SCIPdbgMsg("eqchild is NULL\n");
	      }

	      if( downchild != NULL || eqchild != NULL || upchild != NULL )
	      {
	         SCIPdbgMsg("setting result to SCIP_BRANCHED\n");
	         *result = SCIP_BRANCHED;
	      }
	   }
	   else
	   {
	      SCIPdebugMessage("no controls found in problem data\n");
	   }
	}
	else
	{
	   /* Get history and make a decision */
	   *result = SCIP_DIDNOTRUN;
	}
	assert(result != NULL);
	return SCIP_OKAY;
}

	/** branching execution method for not completely fixed pseudo solutions
	 *
	 *  @see SCIP_DECL_BRANCHEXECPS(x) in type_branch.h of SCIP
	 */
	SCIP_DECL_BRANCHEXECPS(BranchruleControlFirst::scip_execps)
{  /*lint --e{715}*/
	SCIPdbgMsg("entering BranchControlFirst execps\n");
   assert(result != NULL);
   *result = SCIP_DIDNOTRUN;
   return SCIP_OKAY;
}


