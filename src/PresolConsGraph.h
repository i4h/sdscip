/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2012 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License.             */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   PresolConsGraph.h
 * @brief  Creates a Graph that represents the structure of Constraints and Variables of the NLP-Problem
 * @author Ingmar Vierhaus <vierhaus@zib.de>
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __PRESOLCONSGRAPH_H__
#define __PRESOLCONSGRAPH_H__

#include "objscip/objscip.h"
#include "GomoryHuTree.h"
#include "ProbDataTSP.h"


/** C++ Minimal Presolver constraints */
class PresolConsGraph : public scip::ObjPresol
{

public:
   /** default constructor */
   PresolConsGraph(
      SCIP* scip
      )
      :  ObjPresol(
         scip,                      /**< SCIP data structure */
         "CppMin",                  /**< name of presolver */
         "Minimal CPP Presolver",   /**< description of presolver */
         1000000,                   /**< priority of the presolver */
         1,                  /**< maximal number of presolving rounds the presolver participates in (-1: no limit) */
         0                  /**< should presolver be delayed, if other presolvers found reductions? */
         )
   {
   }

   virtual ~PresolConsGraph()
   {
   }


   virtual SCIP_DECL_PRESOLEXEC(scip_exec);


};

#endif
