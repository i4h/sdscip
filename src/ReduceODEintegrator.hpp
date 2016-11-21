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

private:
   SCIP_Real reduce(const SCIP_Interval& interval);
   SOLVE_MODE solveMode_;
   REDUCTION_MODE reductionMode_;
};
}
#endif /* REDUCEODEINTEGRATOR_H_ */
