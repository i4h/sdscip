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

/**@file   PresolConsGraph.h
 * @brief  Creates a Graph that represents the structure of Constraints and Variables of the NLP-Problem
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __PRESOLCONSGRAPH_H__
#define __PRESOLCONSGRAPH_H__

#include "objscip/objscip.h"

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
