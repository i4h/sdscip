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

/**@file   PropODE.h
 * @brief  Propagating bounds of control problems using interval valued odes, implementing Scott, Barton 2012
 * @author Ingmar Vierhaus
 *
 */

#ifndef __PropODE_H__
#define __PropODE_H__

#include "objscip/objscip.h"
#include "scip/struct_tree.h"
#include "scip/clock.h"
#include "SDproblemStructureInterface.h"
#include "IntervalODEintegrator.h"
#include "ProbDataSD.h"
#include "Statistics.h"
#include <spline/PiecewisePolynomial.hpp>
#include <nlpi/pub_expr.h>
#include <nlpi/type_expr.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

namespace sdscip
{

class PropODE: public scip::ObjProp
{
public:

   /** default constructor */
   PropODE(
      SCIP* scip
      )
      : ObjProp(
    		  scip,                                              /**< SCIP data structure */
    		  "ode", 									                 /** name of the propagator */
    		  "solving auxiliary ODEs to bound SDO Problems",    /** description of the propagator */
    		   100000,                                           /** default priority of the propagator */
    		   1,                                                /** freq */
    		   0,                                                /** delay */
     		   SCIP_PROPTIMING_AFTERLPLOOP,                      /** timingmask */
    		   100,                                                /** presolpriority */
    		   5,                                                /** presolmaxrounds */
    		   //SCIP_PRESOLTIMING_EXHAUSTIVE                    /** presoltiming */
    		   SCIP_PRESOLTIMING_FAST                            /** presoltiming */
      )
   ,scip_(scip)
      ,scipIsSet_(true)
      ,nStates_(0)
      ,nAlgebraic_(0)
      ,nControls_(0)
      ,nParams_(0)
      ,intermediateSteps_(0)
      ,dt_(0)
      ,dtIntermediate_(0)
      ,t0_(0)
      ,tf_(0)
      ,execCount_(0)
      ,infeasCount_(0)
      ,lastNodeNumber_(0)
      ,nLookups_(0)
      ,boundApplyCutoff_(1e10)
      ,outfilePrefix_(NULL)
      ,addErrorTerms_(FALSE)
   {
      SCIPaddBoolParam(scip,
             "propagating/ode/writeBounds",
             "Write calculated bounds to file",
             NULL, FALSE, FALSE, NULL, NULL);

      SCIPaddBoolParam(scip,
             "propagating/ode/addErrorTerms",
             "Add error terms corresponding to step size when applying bounds",
             NULL, FALSE, TRUE, NULL, NULL);

      SCIPaddIntParam(scip,
             "propagating/ode/intermediateSteps",
             "Number of integration steps performed by PropODE in additon to problem discretization",
             NULL, FALSE, 1, 0, 1000, NULL, NULL );

      SCIPaddStringParam(scip,
             "propagating/ode/outFilePrefix",
             "Path of file to write calculated bounds to. The current node id and a .dat extension "
             "will be added to the end of the given string",
             NULL, FALSE, "propODEbounds", NULL, NULL);

      boundApplyCutoff_ = SCIPgetHugeValue(scip);
   }

   /** destructor */
   virtual ~PropODE()
   {

      SCIPdbgMsg("destroying PropODE\n");

      for (auto it = lookups_.begin(); it != lookups_.end(); ++it)
         delete *it;


   }

   virtual SCIP_DECL_PROPINIT(scip_init);
   virtual SCIP_DECL_PROPEXEC(scip_exec);
   virtual SCIP_DECL_PROPPRESOL(scip_presol);

private:
#if 0
   SCIP_RETCODE createLookupExpression(std::vector<SCIP_Real> x, std::vector<SCIP_Real> y, SCIP_EXPR* arg, SCIP_EXPR** target);
#endif

   SCIP_RETCODE getOmegaL(std::vector<SCIP_Real> v, std::vector<SCIP_Real> w, SCIP_Interval** varIntervals, int ind);
   SCIP_RETCODE getOmegaU(std::vector<SCIP_Real> v, std::vector<SCIP_Real> w, SCIP_Interval** varIntervals, int ind);
   SCIP_RETCODE getLG(std::vector<SCIP_Real> v, std::vector<SCIP_Real> w, SCIP_Interval** varIntervals);
   SCIP_RETCODE updateXdot();
   SCIP_RETCODE prepareOutFile(std::vector<std::string>  stateVarNames);
   SCIP_RETCODE finalizeOutFile(std::string message);
   SCIP_RETCODE applyPropODE(SCIP* scip, int *nchgbds, SCIP_RESULT *result, unsigned int startTime);
   SCIP_RETCODE applyPropODEold(SCIP* scip, SCIP_Real tStart, int *nchgbds, SCIP_RESULT *result, unsigned int startTime);
   SCIP_RETCODE addGlobalEnclosure(int nState, SCIP_BOUNDTYPE boundType, SCIP_Real val);
   SCIP_RETCODE applyEnclosure(SCIP_Interval** varIntervals, int t, sdscip::SDproblemStructureInterface* structure);

   /* Set params for given time. Params array is expected to be pre-allocated with nParams elements */
   SCIP_RETCODE getParams(SCIP_Real t, SCIP_Real* params);

   SCIP* scip_;
   SCIP_Bool scipIsSet_;
   std::vector<SCIP_EXPR*> xDot_;
   std::map<int, SCIP_Real> globalEnclosureLbs_;
   std::map<int, SCIP_Real> globalEnclosureUbs_;
   int nStates_;
   int nAlgebraic_;
   int nControls_;
   int nParams_;
   int intermediateSteps_;
   SCIP_Real dt_;
   SCIP_Real dtIntermediate_;
   SCIP_Real t0_;
   SCIP_Real tf_;
   int execCount_;
   int infeasCount_;
   int lastNodeNumber_;
   std::vector<spline::PiecewisePolynomial<1, SCIP_Real>* > lookups_;
   std::vector<std::vector<SCIP_Real>> xVals_;
   std::vector<std::vector<SCIP_Real>> yVals_;
   int nLookups_;
   std::ofstream outFile_;

   /* We dont apply bounds outside of [-boundAppplyCutoff, boundApplyCutoff ] to avoid
    * numerical problems with bounds very close to SCIPinfinity */
   SCIP_Real boundApplyCutoff_;

   /* Private variables for scip parameters */
   SCIP_Bool writeFile_ = false;
   char* outfilePrefix_;
   SCIP_Bool addErrorTerms_;



};


}

#endif
