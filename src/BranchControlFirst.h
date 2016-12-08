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

/**@file   BranchControlFirst.h
 * @brief  Branching rule for SDO problems, selecting control variables first
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
   { }

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
