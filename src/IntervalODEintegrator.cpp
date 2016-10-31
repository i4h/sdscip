//#define SCIP_DBG
//#define SCIP_DEBUG
/*
 * IntervalODEintegrator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"


namespace sdscip
{

IntervalODEintegrator::IntervalODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls) :
   ODEintegrator(_scip,_discretization, _dt, _nIntermediateSteps, _nStates, _nAlgebraic, _nControls)
   ,infinity_(SCIP_REAL_MAX)
   ,controlMode_(CONTROL_MODE_SINGLE_INTERVAL)
{
   SCIPdbgMsg("Constructing IntervalODEintegrator, using %s, dt = %f, intermediateSteps = %i, nStates = %i, nAlgebraic = %i, nControls = %i\n",discretization_.c_str(), dt_, nIntermediateSteps_, nStates_, nAlgebraic_, nControls_);
   /* No factory needed so far */
   rateEvaluator_ = new SBrateEvaluator(_nStates, _nAlgebraic, _nControls, _scip);

   /* Initialize varValues (states and controls with correct number of elements) */
   SCIP_Interval zero;
   zero.inf = 0.0;
   zero.sup = 0.0;
   varValues_ = std::vector<SCIP_Interval>(nStates_ + nControls_ + nAlgebraic_, zero);

   /* Default configuration */
   saneBoundGap_ = 3.0;
}

IntervalODEintegrator::~IntervalODEintegrator()
{}

SBrateEvaluator* IntervalODEintegrator::rateEvaluator()
{
   return rateEvaluator_;
}


std::string IntervalODEintegrator::toString()
{
   /* Summarize state of integrator    */
   std::ostringstream oss;
   oss << "ODE Integrator Configuration:" << std::endl;
   oss << "# nStates = " << nStates_ << std::endl;
   oss << "# Scheme = " << discretization_ << std::endl;
   oss << "# dt = " << dt_ << std::endl;
   oss << "# intermediateSteps = " << nIntermediateSteps_ << std::endl;
   oss << "# dtIntermediate = " << dtIntermediate_<< std::endl;
   oss << "# rateEvaluator = " << rateEvaluator_->getName() << std::endl;
   oss << "ODE Integrator State:" << std::endl;
   oss << "# t = " << t_ << std::endl;
   oss << "# x = " << statesToString() << std::endl;
   oss << "# z = " << controlsToString() << std::endl;

   return oss.str();
}

std::string IntervalODEintegrator::statesToString()
{
   std::ostringstream oss;
   oss << "x(" << t_ << ") = (";
   int precision(8);
   for (int i = 0; i < nStates_ - 1; ++i)
   {
      oss << "[" << std::setprecision(precision) << varValues_[i].inf << "," << varValues_[i].sup << "], ";
   }
   oss << "[" << std::setprecision(precision) << varValues_[nStates_ - 1].inf << "," << varValues_[nStates_ - 1].sup << "])";
   return oss.str();
}

void IntervalODEintegrator::writeStates(std::ofstream& outFile)
{
   if( outFile.is_open())
   {
      outFile << std::setw(4) << t_ << "\t";
      for (int i = 0; i < nStates_; ++i)
         outFile << std::setw(8) << varValues_[i].inf << "\t"
         << std::setw(8) << varValues_[i].sup  << "\t";
      outFile << std::endl;
   }
}

std::string IntervalODEintegrator::controlsToString()
{
   std::ostringstream oss;
   oss << "z(" << t_ << ") = (";
   int precision(8);
   for (int i = nStates_; i < nStates_ + nControls_ - 1; ++i)
   {
      oss << std::setprecision(precision) << varValues_[i].inf << "," << varValues_[i].sup << ", ";
   }
   oss << std::setprecision(precision) << varValues_[nStates_ + nControls_ - 1].inf << "," << varValues_[nStates_ + nControls_ - 1].sup << ")";
   return oss.str();
}


void IntervalODEintegrator::printXdot()
{
   for (int i = 0; i < nStates_; ++i)
   {
      SCIPinfoMessage(scip_, NULL,"\\dot x_%i: ",i);
      SCIPexprPrint(rateEvaluator_->getXdot(i), SCIPgetMessagehdlr(scip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(scip_, NULL,"\n");
   }
}

void IntervalODEintegrator::setControlMode(INTERVAL_INTEGRATOR_CONTROL_MODE mode)
{
   controlMode_ = mode;
}

void IntervalODEintegrator::setXdots(std::vector<SCIP_EXPR*> xDot)
{
   rateEvaluator_->setXdot(xDot);
}

void IntervalODEintegrator::setInitial(SCIP_Real t, std::vector<SCIP_Interval> states, std::vector<SCIP_Interval> controls)
{
   for (int i = 0; i < nControls_; ++i)
      varValues_[nStates_ + i] = controls[i];
   SCIPdbgMsg("controls[0] = [%f,%f]\n",controls[0].inf,controls[0].sup);
   setInitial(t, states);
}

void IntervalODEintegrator::setInitial(SCIP_Real t, std::vector<SCIP_Interval> states)
{
   for (int i = 0; i < nStates_; ++i)
      varValues_[i] = states[i];
   t_ = t;
}

void IntervalODEintegrator::setControl(int controlId, SCIP_Real inf, SCIP_Real sup)
{
   varValues_[nStates_ + controlId].inf = inf;
   varValues_[nStates_ + controlId].sup = sup;
}

void IntervalODEintegrator::setControls(const std::vector<SCIP_Interval>& controls)
{
   assert(controls.size() == std::size_t(nControls_));
   for (int i = 0; i < nControls_; ++i)
   {
      varValues_[nStates_ + i].inf = controls[i].inf;
      varValues_[nStates_ + i].sup = controls[i].sup;
   }
}

void IntervalODEintegrator::setEndControls(const std::vector<SCIP_Interval>& endControls)
{
   assert(endControls.size() == std::size_t(nControls_));
   endControls_ = endControls;
   midControls_.resize(nControls_);
   for (int i = 0; i < nControls_; ++i)
   {
      SCIPintervalUnify(&midControls_[i], varValues_[nStates_ + i], endControls_[i]);
   }
}

SCIP_Interval IntervalODEintegrator::getState(int dim)
{
   return varValues_[dim];
}

SCIP_Real IntervalODEintegrator::getState(int dim, SCIP_BOUNDTYPE bndtype)
{
   if( bndtype == SCIP_BOUNDTYPE_LOWER)
      return varValues_[dim].inf;
   else if( bndtype == SCIP_BOUNDTYPE_UPPER)
      return varValues_[dim].sup;
   else
   {
      SCIPerrorMessage("invalid bndtype");
   }
   return 0;
}

std::vector<SCIP_Interval> IntervalODEintegrator::getStates()
{
   //return states_;
   return std::vector<SCIP_Interval>( varValues_.begin(), varValues_.begin() + nStates_ );
}

std::vector<SCIP_Interval> IntervalODEintegrator::getControls()
{
   //return states_;
   return std::vector<SCIP_Interval>( varValues_.begin() + nStates_, varValues_.end());
}

void IntervalODEintegrator::cycleControls()
{
   if (controlMode_ == CONTROL_MODE_STARTMIDEND)
   {
      assert(endControls_.size() == std::size_t(nControls_));
      for( int i = 0; i < nControls_; ++i)
      {
         varValues_[nStates_ + i] = endControls_[i];
      }
      endControls_.clear();
      midControls_.clear();
   }
}

std::vector<SCIP_Interval> IntervalODEintegrator::getNewX(const std::vector<std::vector<SCIP_Interval> >& kMatrix, const std::vector<double>& row, int s, SCIP_Real c)
{
   std::vector<SCIP_Interval> newX(varValues_.begin(), varValues_.begin() + nStates_);
   //std::vector<SCIP_Interval> newX;
   newX.reserve(nStates_ + nControls_ + nAlgebraic_);
   //newX.resize(nStates_);

   /* Compute the states */
   for (int i = 0; i < nStates_; ++i)
   {
      for (int j = 0; j < s; ++j)
      {
         newX[i].inf = newX[i].inf + row[j+1] * dtIntermediate_ * kMatrix[j][i].inf;
         newX[i].sup = newX[i].sup + row[j+1] * dtIntermediate_ * kMatrix[j][i].sup;
         assert(newX[i].inf <= newX[i].sup);
      }
   }

   /* Set control intervals */
   if( c == 0 || controlMode_ == CONTROL_MODE_SINGLE_INTERVAL) /* Set control values from varValues_ */
      for( int i = 0; i < nControls_; ++i)
         newX.push_back(varValues_[nStates_ + i]);
   else if( c == 1.0) /* Use endControls_ */
      for( auto it = endControls_.begin(); it != endControls_.end(); ++it)
         newX.push_back(*it);
   else /* Use midControls_ */
      for( auto it = midControls_.begin(); it != midControls_.end(); ++it)
         newX.push_back(*it);


   assert(newX.size() == std::size_t(nStates_ + nControls_));
   newX.resize(nStates_ + nControls_ + nAlgebraic_);

   return newX;
}

void IntervalODEintegrator::step(SCIP_Real* params /*= NULL*/)
{
   step(BoundMap(), params);
}

void IntervalODEintegrator::step(const BoundMap& stateBounds, SCIP_Real* params /*= NULL*/)
{
   step(stateBounds, stateBounds, stateBounds, params);
}

void IntervalODEintegrator::step(const BoundMap& startStateBounds, const BoundMap& endStateBounds, SCIP_Real* params /*= NULL*/)
{
   /* Compute midStateBounds */
   SCIPdbgMsg("IntervalODEintegrator::step(startBounds,endBounds)\n");
   step(startStateBounds, getUnion(startStateBounds, endStateBounds), endStateBounds, params);
}

void IntervalODEintegrator::step(const BoundMap& startStateBounds, const BoundMap& midStateBounds, const BoundMap& endStateBounds, SCIP_Real* params /*= NULL*/)
{
   SCIPdbgMsg("Stepping from t = %f, to %f\n", t_, t_ + dt_);

   for (int steps = 0; steps < nIntermediateSteps_; ++steps)
   {
      SCIPdbgMsg("===================================\n");
      SCIPdbgMsg("performing intermediate step %i\n", steps);

      /* Calculate k's successively */
      int stages = tableau_.stages();
      std::vector<std::vector<SCIP_Interval> > kMatrix;

      /* k_1 is trivial */

      /* varValues_ has the control interval at t (the start of the step), so we don't have to modify varValues for this evaluation */
      SCIPdbgMsg("Getting rates for stage 0\n");
      kMatrix.push_back(rateEvaluator_->getRates(t_,  varValues_, startStateBounds, params, infinity_));

      /* Calculate remaining stages */
      for (int s = 1; s < stages; ++s)
      {
         SCIPdbgMsg("Stage = %i\n", s);
         const std::vector<double>& row = *(tableau_.getRowVec(s));
         SCIP_Real c = row[0]; /* Time coefficient c_s */

         SCIP_Real newT = t_ + c * dtIntermediate_;
         SCIPdbgMsg("newT = %f\n", newT);
         std::vector<SCIP_Interval> newX = getNewX(kMatrix, row, s, c);
         assert(newX.size() == std::size_t(nStates_ + nAlgebraic_ + nControls_));
         SCIPdbgMsg("newX = %s\n", intervalVecToString(newX).c_str());

         if (c == 1.0)
         {
            SCIPdbgMsg("using endStateBounds \n");
            SCIPdbg( printBoundMap(endStateBounds) );
            kMatrix.push_back(rateEvaluator_->getRates(newT, newX, endStateBounds, params, infinity_));
         }
         else
         {
            SCIPdbgMsg("using midStateBounds \n");
            SCIPdbg( printBoundMap(midStateBounds) );
            kMatrix.push_back(rateEvaluator_->getRates(newT, newX, midStateBounds, params, infinity_));
         }

         /* These are just rates, they are allowed to switch! */
         /*for (int i = 0; i < nStates_; ++i)
            assert((kMatrix.back())[i].inf <= (kMatrix.back())[i].sup);*/
      }

      /* Calculate next state vector using stages and last row
       * - control intervals remain untouched
       * - we add the contribution of each stage to the current states according to the last row of the tableau
       * */
      const std::vector<double>& row = *(tableau_.getRowVec(stages));
      SCIPdbgMsg("starting to add contributions, varValues:\n %s", intervalVecToString(varValues_).c_str());
      for (int i = 0; i < nStates_; ++i)
      {
         for (int j = 0; j < stages; ++j)
         {
            varValues_[i].inf = varValues_[i].inf + row[j] * dtIntermediate_ * kMatrix[j][i].inf;
            SCIPdbgMsg("stage %i, dim %i, contribution to inf is %1.16e, new val %f\n", i, j, row[j] * dtIntermediate_ * kMatrix[j][i].inf, varValues_[i].inf);
            varValues_[i].sup = varValues_[i].sup + row[j] * dtIntermediate_ * kMatrix[j][i].sup;
            SCIPdbgMsg("stage %i, dim %i, contribution to sup is %1.16e\n", i, j, row[j] * dtIntermediate_ * kMatrix[j][i].sup);
         }

         /* This is possible due to numerical difficulties and really bad bounds */
         if( varValues_[i].inf > varValues_[i].sup)
         {
            std::ostringstream oss;
            oss << "boundswitch of size " <<  (varValues_[i].sup - varValues_[i].inf) << " in state " << i << " at t=" << t_ ;
            throw std::runtime_error(oss.str());
         }
      }

      /* Move time forward */
      t_ = t_ + dtIntermediate_;

      SCIPdbgMsg("after adding contribution,s varValues: %s\n",intervalVecToString(varValues_).c_str());
   }
   /* Cycle control intervals from end to varValues if applicable */
   cycleControls();

}

SCIP_Bool IntervalODEintegrator::isDiverging() const
{
   for( int i = 0; i < nStates_; ++i)
   {
      if (!SCIPisInfinity(scip_, -1.0*varValues_[i].inf) && !SCIPisInfinity(scip_, varValues_[i].sup))
         return false; /* At least one potentially useful bound found */
   }
   return true;

}

SCIP_Bool IntervalODEintegrator::checkBounds(const BoundMap& bounds) const
{
   for( auto it = bounds.begin(); it != bounds.end(); ++it)
   {
      SCIP_BOUNDTYPE type = it->first.second;
      int varId = it->first.first;
      SCIP_Real value = it->second;
      // TODO: As long as the interval contains the strict bound we can still continue, because the violating part will be cut off in the next step /*
      if(    (type == SCIP_BOUNDTYPE_LOWER && varValues_[varId].inf < value)
          || (type == SCIP_BOUNDTYPE_UPPER && varValues_[varId].sup > value)
      )
      {
         return false;
      }
   }
   return true;
}


SCIP_Bool IntervalODEintegrator::sane() const
{
   /* Not sane if highest lower bound is orders of magnitude lower than lowest upper bound */
   if( nStates_ >= 2)
   {
      double lowestUpper = infinity_;
      double highestLower = -infinity_;
      int lowestUpperInd = 0;
      int highestLowerInd = 0;

      for (int i = 0; i < nStates_; ++i)
      {
         /* Update at most one bound */
         if (varValues_[i].sup < lowestUpper )
         {
            lowestUpper = varValues_[i].sup;
            lowestUpperInd = i;
         }

         if (varValues_[i].inf > highestLower )
         {
            highestLower = varValues_[i].inf;
            highestLowerInd = i;
         }
      }

      if(     (highestLowerInd != lowestUpperInd)
           && (highestLower  > lowestUpper)
           && ((std::log10(highestLower) - std::log10(lowestUpper)) > saneBoundGap_ )
           )
      {
         SCIPdebugMessage("Sanity check of IntervalIntegrator failed: x_%i = [%e,] and x_%i = [,%e] are %f orders of magnitude apart (limit %1.2f)\n",
               lowestUpperInd, lowestUpper, highestLowerInd, highestLower,std::log10(highestLower) - std::log10(lowestUpper), saneBoundGap_);
         return false;
      }
   }

   return true;
}

}
