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
/**@file   BranchControlFirst.h
 * @brief  C++ Control First Branching rule for SDO Problems
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __BranchruleControlFirst_H__
#define __BranchruleControlFirst_H__

#include "objscip/objscip.h"


namespace sdscip
{


class BranchruleControlFirst : public scip::ObjBranchrule
{
public:

   /** default constructor */
   BranchruleControlFirst(
      SCIP* scip
      )
      : ObjBranchrule(
    		  scip,                                              /**< SCIP data structure */
    		  "ControlFirst", 									/** name of the branching rule */
    		  "Branching rule that starts on Controls first in SDO Problems",    /** description of the branching rule */
    		  -100000, /** default priority of the branching rule */
    		  -1, /** default maximal depth for applying the branching rule */
    		   1.0 /** default maximal relative distance from current node's dual bound to primal bound
    		   	   	   	   	   	   	   	   	   	   	   *  compared to best node's dual bound for applying branching rule
    		   	   	   	   	   	   	   	   	   	   	   *  (0.0: only on current best node, 1.0: on all nodes)
    		   	   	   	   	   	   	   	   	   	   	   */
      )
   {
      printf("BranchControlFirst Reporting\n");
   }

   /** destructor */
   virtual ~BranchruleControlFirst()
   {
   }

   virtual SCIP_DECL_BRANCHEXECPS(scip_execps);
   virtual SCIP_DECL_BRANCHEXECLP(scip_execlp);
   virtual SCIP_DECL_BRANCHEXECEXT(scip_execext);

};


}

#endif
