#define SCIP_DEBUG

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/**@file   HeurMaxCtrl.cpp
 * @brief  Control First Branching Rule
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
 *  @see SCIP_DECL_BRANCHEXECEXT(x) in @ref type_branch.h
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
	 *  @see SCIP_DECL_BRANCHEXECPS(x) in @ref type_branch.h
	 */
	SCIP_DECL_BRANCHEXECPS(BranchruleControlFirst::scip_execps)
{  /*lint --e{715}*/
	SCIPdbgMsg("entering BranchControlFirst execps\n");
   assert(result != NULL);
   *result = SCIP_DIDNOTRUN;
   return SCIP_OKAY;
}


