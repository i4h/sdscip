//#define SCIP_DEBUG
//#define SCIP_DBG
/*
 * PointODEintegrator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "ReduceODEintegrator.hpp"
#include "PointRateEvaluator.h"


namespace ctrl
{

/* Delegate constructor */
ReduceODEintegrator::ReduceODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls) :
      PointODEintegrator(_scip,_discretization, _dt, _nIntermediateSteps, _nStates, _nAlgebraic, _nControls, PointRateEvaluator::RATE_EVALUATOR_SIM)
      ,solveMode_(SOLVE_MODE_SIM)
      ,reductionMode_(REDUCTION_MODE::REDUCTION_MODE_LOWER)

{ }

ReduceODEintegrator::~ReduceODEintegrator()
{}

SCIP_Real ReduceODEintegrator::reduce(const SCIP_Interval& interval)
{
   if( SCIPisEQ(scip_, interval.sup, interval.inf))
      return 0.5*(interval.sup + interval.inf);
   else
   {
      if( solveMode_ == SOLVE_MODE_SIM)
      {
         SCIPdbgMsg("set solveMode to control at t = %f\n", getT());
         solveMode_ = SOLVE_MODE_CONTROL;
      }

      if( reductionMode_ == REDUCTION_MODE::REDUCTION_MODE_LOWER)
         return interval.inf;
      else if( reductionMode_ == REDUCTION_MODE::REDUCTION_MODE_UPPER)
         return interval.sup;
      else
         return 0.5*(interval.sup + interval.inf);
   }
}

void ReduceODEintegrator::setInitial(SCIP_Real t, std::vector<SCIP_Interval> states)
{
   for (int i = 0; i < nStates_; ++i)
      varValues_[i] = reduce(states[i]);
   t_ = t;
}

void ReduceODEintegrator::setControls(const std::vector<SCIP_Interval>& controls)
{
   assert(controls.size() == std::size_t(nControls_));
   for (int i = 0; i < nControls_; ++i)
   {
      SCIPdbgMsg("Setting control %f\n",controls[i]);
      varValues_[nStates_ + i] = reduce(controls[i]);
      SCIPdbgMsg("Set to %f\n",varValues_[nStates_ + i]);
   }
}

void ReduceODEintegrator::setEndControls(const std::vector<SCIP_Interval>& endControls)
{
   assert(endControls.size() == std::size_t(nControls_));
   for( auto it = endControls.begin(); it != endControls.end(); ++it)
      endControls_[it - endControls.begin()] = reduce(*it);
}



ReduceODEintegrator::SOLVE_MODE ReduceODEintegrator::getSolveMode()
{
   return solveMode_;
}

void ReduceODEintegrator::setReductionMode(REDUCTION_MODE mode)
{
   reductionMode_ = mode;
}

std::string ReduceODEintegrator::toString()
{
   /* Summarize state of integrator    */
   std::ostringstream oss;
   oss << PointODEintegrator::toString();

   oss << "# reductionMode_ = " << getReductionModeString() << std::endl;

   return oss.str();
}

std::string ReduceODEintegrator::getSolveModeString()
{
	switch (solveMode_) {
		case SOLVE_MODE::SOLVE_MODE_SIM:
			return std::string("Simulation Mode");
			break;
		case SOLVE_MODE::SOLVE_MODE_CONTROL:
			return std::string("Control Mode");
			break;
		default:
			return std::string("Unknown solve mode");
			break;
	}
}

std::string ReduceODEintegrator::getReductionModeString()
{
	switch (reductionMode_) {
		case REDUCTION_MODE::REDUCTION_MODE_LOWER:
			return std::string("Lower");
			break;
		case REDUCTION_MODE::REDUCTION_MODE_UPPER:
			return std::string("Upper");
			break;
		case REDUCTION_MODE::REDUCTION_MODE_MIDPOINT:
			return std::string("Midpoint");
			break;
		default:
			return std::string("Unknown reduction mode");
			break;
	}
}

std::vector<ReduceODEintegrator::REDUCTION_MODE> ReduceODEintegrator::getReductionModeVector() {
	using REDUCTION_MODE = ReduceODEintegrator::REDUCTION_MODE;
	return std::vector<ReduceODEintegrator::REDUCTION_MODE> {REDUCTION_MODE::REDUCTION_MODE_LOWER, REDUCTION_MODE::REDUCTION_MODE_UPPER, REDUCTION_MODE::REDUCTION_MODE_MIDPOINT};
}

}
