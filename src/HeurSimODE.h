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

//#include
/**@file   HeurMaxCtrl.cpp
 * @brief  Heuristic simulating sdo problems while fixing control variables
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __HEURSIMODE_H__
#define __HEURSIMODE_H__

#include <boost/regex.hpp>
#include <vector>
#include <string>

#include "objscip/objscip.h"
#include "scip/clock.h"
#include "ProbDataSD.h"
#include "SDproblemStructureInterface.h"
#include "ReduceODEintegrator.hpp"
#include "Statistics.h"



namespace sdscip
{

/** C++ wrapper */
class HeurSimODE : public scip::ObjHeur
{

public:

   using REDUCTION_MODE = ReduceODEintegrator::REDUCTION_MODE;

   using BoundKey = SDproblemStructureInterface::BoundKey;
   using BoundMap = SDproblemStructureInterface::BoundMap;

   int                ncalls_;            /**< number of calls of the heuristic since the last solution was found */
   SCIP_SOL*          sol_;               /**< current solution */
   int                timesCalled_;       /**< number of calls to the heuristic*/

   /** default constructor */
   HeurSimODE(
      SCIP* scip
      )
      : ObjHeur(
            scip,                                                 /**< SCIP data structure */
            "simODE",                                            /**< name of primal heuristic */
            "Simulation Heuristic for Control Problems",     /**< description of primal heuristic */
            'S',                                                  /**< display character of primal heuristic */
            100000000,                                                 /**< priority of the primal heuristic */
            1,                                                   /**< frequency for calling primal heuristic */
            1,                                                    /**< frequency offset for calling primal heuristic */
            -1,                                                    /**< maximal depth level to call heuristic at (-1: no limit) */
           SCIP_HEURTIMING_BEFOREPRESOL | SCIP_HEURTIMING_BEFORENODE, /**< positions in the node solving loop where heuristic should be executed; *
                                                                   *   see definition of SCIP_HeurTiming for possible values */
            FALSE                                                 /**< does the heuristic use a secondary SCIP instance? */
            )
   {
      timesCalled_ = 0;

      SCIPaddBoolParam(scip,
             "heuristics/simODE/writesols",
             "Write calculated solutions to file",
             NULL, FALSE, FALSE, NULL, NULL);

      SCIPaddStringParam(scip,
             "heuristics/simODE/outFilePrefix",
             "Path of file to write calculated bounds to. The current node id and a .dat file extension "
             "will be added to the end of the given string",
             NULL, FALSE, "simODEbounds", NULL, NULL);
   }

   /** destructor */
   virtual ~HeurSimODE()
   {
   }

   /** destructor of primal heuristic to free user data (called when SCIP is exiting) */
   virtual SCIP_DECL_HEURFREE(scip_free);

   /** initialization method of primal heuristic (called after problem was transformed) */
   virtual SCIP_DECL_HEURINIT(scip_init);

   /** deinitialization method of primal heuristic (called before transformed problem is freed) */
   virtual SCIP_DECL_HEUREXIT(scip_exit);

   /** solving process initialization method of primal heuristic (called when branch and bound process is about to begin)
    *
    *  This method is called when the presolving was finished and the branch and bound process is about to begin.
    *  The primal heuristic may use this call to initialize its branch and bound specific data.
    *
    */
   virtual SCIP_DECL_HEURINITSOL(scip_initsol);

   /** solving process deinitialization method of primal heuristic (called before branch and bound process data is freed)
    *
    *  This method is called before the branch and bound process is freed.
    *  The primal heuristic should use this call to clean up its branch and bound data.
    */
   virtual SCIP_DECL_HEUREXITSOL(scip_exitsol);

   /** execution method of primal heuristic
    *
    *  Searches for feasible primal solutions. The method is called in the node processing loop.
    *
    *  possible return values for *result:
    *  - SCIP_FOUNDSOL   : at least one feasible primal solution was found
    *  - SCIP_DIDNOTFIND : the heuristic searched, but did not find a feasible solution
    *  - SCIP_DIDNOTRUN  : the heuristic was skipped
    *  - SCIP_DELAYED    : the heuristic was skipped, but should be called again as soon as possible, disregarding
    *                      its frequency
    */
   virtual SCIP_DECL_HEUREXEC(scip_exec);

   /** clone method which will be used to copy a objective plugin */
   virtual SCIP_DECL_HEURCLONE(ObjCloneable* clone);

   /** returns whether the objective plugin is copyable */
   virtual SCIP_DECL_HEURISCLONEABLE(iscloneable)
   {
      return true;
   }

private:
   SCIP_RETCODE prepareOutFile(std::vector<std::string>  stateVarNames, std::string reductionModeString);
   SCIP_RETCODE finalizeOutFile(std::string message);

   /* Dimension of state space */
   int nStates_;

   /* Dimension of control space */
   int nControls_;

   /* Number of algebraic variables */
   int nAlgebraic_;

   /* File resource for solution output */
   std::ofstream outFile_;
};

}

#endif
