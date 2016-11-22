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

/**@file    ReduceODEintegrator.hpp
 * @brief   ODE integrator for scalar ODEs, reducing interval rates to points
 * @author  Ingmar Vierhaus
 *
 */


#ifndef REDUCEODEINTEGRATOR_H_
#define REDUCEODEINTEGRATOR_H_

#include "ODEintegrator.h"
#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "PointRateEvaluator.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "Vector.h"
#include <string>
#include <vector>
#include "scip/scip.h"

namespace sdscip
{


class ReduceODEintegrator : public PointODEintegrator
{
public:

	/* Reduction modes of the integrator. Update
	 * - ReduceODEintegrator::getReductionModeString
	 * - ReduceODEintegrator::getReductionModeVector
	 * when updating this enum class.
	 */
   enum class REDUCTION_MODE
   {
      REDUCTION_MODE_LOWER
      ,REDUCTION_MODE_UPPER
      ,REDUCTION_MODE_MIDPOINT
   };

   enum SOLVE_MODE
   {
      SOLVE_MODE_SIM /* If all intervals are degenerate, we have a simulation problem and can fix variables... */
      ,SOLVE_MODE_CONTROL /* ...if not we just look for a primal solution */
   };

   ReduceODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls);
   ~ReduceODEintegrator();

   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states);
   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states, std::vector<SCIP_Real> controls);
   void setInitial(SCIP_Real t, std::vector<SCIP_Interval> states);

   void setEndControls(const std::vector<SCIP_Interval>& endControls);
   void setControls(const std::vector<SCIP_Interval>& controls);

   SOLVE_MODE getSolveMode();
   void setReductionMode(REDUCTION_MODE mode);
   static std::vector<REDUCTION_MODE> getReductionModeVector();

   std::string toString();
   std::string getSolveModeString();
   std::string getReductionModeString();
   static std::string getReductionModeString(REDUCTION_MODE mode);


private:
   SCIP_Real reduce(const SCIP_Interval& interval);
   SOLVE_MODE solveMode_;
   REDUCTION_MODE reductionMode_;
};
}
#endif /* REDUCEODEINTEGRATOR_H_ */
