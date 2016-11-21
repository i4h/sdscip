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
