//#define SCIP_DBG
/*
 * SBrateEvaluator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#include "SBrateEvaluator.h"
using namespace ctrl;


//SBrateEvaluator::SBrateEvaluator(ODEintegrator* _integrator, int _nStates) : PointRateEvaluatorInterface(_integrator, _nStates)
SBrateEvaluator::SBrateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip) :
   PointRateEvaluator(_nStates, _nAlgebraic, _nControls,  _scip)
{ }

SBrateEvaluator::~SBrateEvaluator()
{ }


std::string SBrateEvaluator::getName()
{
   return std::string("SBrateEvaluator");
}

std::vector<SCIP_Real> SBrateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::vector<SCIP_Real>();
}

std::vector<SCIP_Real> SBrateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params)
{
   //TODO
   SCIPerrorMessage("%s:%s not implemented\n",__FILE__,__func__);
   return std::vector<SCIP_Real>();
}

std::vector<SCIP_Interval> SBrateEvaluator::getRates(SCIP_Real t, std::vector<SCIP_Interval>& varValues, const BoundMap& stateBounds, SCIP_Real* params, SCIP_Real infinity)
{
  SCIPdbgMsg("  SBrateEvaluator::getRates, t = %f\n", t);

  std::vector<SCIP_Interval> rates(nStates_);
  for (int i = 0; i < nStates_; ++i)
  {
     for (int boundType = SCIP_BOUNDTYPE_LOWER; boundType <= SCIP_BOUNDTYPE_UPPER; ++boundType)
     {
        SCIPdbgMsg("=============== considering %s Bound of State %i\n", boundType == SCIP_BOUNDTYPE_LOWER ? "lower" : "upper", i);
        std::vector<SCIP_Interval> omega = getOmega(i, (SCIP_BOUNDTYPE) boundType, varValues, stateBounds);
        SCIPdbgMsg("     omega is %s", intervalVecToString(omega).c_str());

        /* Compute values of algebraic variables in omega */
        computeAlgebraic(varValues, params, infinity);

        SCIP_Interval result;
        SCIPdbgMsg("     evaluating expression xDot_[%i]:\n", i);
        SCIPexprEvalInt(xDot_[i], infinity, &omega[0], params, &result );
        assert(result.inf <= result.sup);
        SCIPdbgMsg("     result of exprEvalInt is [%f, %f] (width = %1.16e)\n", result.inf, result.sup, result.sup - result.inf);
        if (boundType == SCIP_BOUNDTYPE_LOWER)
           rates[i].inf = result.inf;
        else
           rates[i].sup = result.sup;
     }
     /* It is possible at this point that result.sup < result.inf. This can happen anytime,
      * because rates[i].inf, rates[i].sup are just containers for \dot v and \dot w
      * and don't have to be ordered.
      * We do it this way (instead of vector<SCIP_Real>) to keep the correlation between varValues and rates
      *  */
  }
  SCIPdbgMsg("returning rates: \n%s",intervalVecToString(rates).c_str());
  return rates;
}

std::vector<SCIP_Interval> SBrateEvaluator::getOmega(int state, SCIP_BOUNDTYPE boundType, const std::vector<SCIP_Interval>& varValues, const BoundMap& stateBounds)
{
   SCIPdbgMsg("   SBrateEvaluator::getOmega, state=%i, boundType=%i\n", state, (int) boundType);
   std::vector<SCIP_Interval> omega = varValues; /* Copy */
   applyB(state, boundType, omega);
   //TODO _SD: reenable this
   //applyEnclosure(state, boundType, stateBounds, omega);

   return omega;
}

void SBrateEvaluator::computeAlgebraic(std::vector<SCIP_Interval>& varValues, SCIP_Real* params, SCIP_Real infinity)
{
   /* Compute varValues[i >= nStates_ + nControls_] using algebraic expressions */
   for( int i = 0; i < nAlgebraic_; ++i)
   {
      SCIPdbgMsg("evaluating algebraicExpressions[%i]\n", i);
      SCIP_Interval result;
      SCIPexprEvalInt(algebraicExpressions_[i], infinity,  &varValues[0], params, &result);
      varValues[nStates_ + nControls_ + i] = result;

   }
   SCIPdbgMsg("done, varValues: %s",intervalVecToString(varValues).c_str());
}

void SBrateEvaluator::applyB(int state, SCIP_BOUNDTYPE boundType, std::vector<SCIP_Interval>& varValues)
{
   if (boundType == SCIP_BOUNDTYPE_LOWER)
      varValues[state].sup = varValues[state].inf;
   else
      varValues[state].inf = varValues[state].sup;
}

void SBrateEvaluator::applyEnclosure(int state, SCIP_BOUNDTYPE boundType, const BoundMap& stateBounds, std::vector<SCIP_Interval>& varValues)
{
   //SCIPdbgMsg("entered applyEnclosure\n");
   //BoundMap bounds = getTightestEnclosure(stateBounds);
   const BoundMap& bounds = stateBounds;
   /* Apply available bounds */
   for( auto it = bounds.begin(); it != bounds.end(); ++it)
   {
      int state = it->first.first;
      SCIP_BOUNDTYPE type = it->first.second;
      SCIP_Real bound = it->second;
      //SCIPdbgMsg("    applying bound for state %i of type %i = %f to current interval [%f, %f]\n", state, type, it->second, varValues[state].inf, varValues[state].sup);
      /* If [v,w] \cap enclosure is empty, we set v := \gamma = w
       * which is equivalent to                   inf = \gamma = sup */
      if (type == SCIP_BOUNDTYPE_LOWER) /* Lower bound */
      {
         /* If [v,w] \cap enclosure is empty, we set v := \gamma = w
          * which is equivalent to                   inf = \gamma = sup */
         if ((varValues)[state].sup < bound)
         {
            varValues[state].inf = varValues[state].sup;
            SCIPdbgMsg("      degenerated bound to [inf, inf]\n");
         }
         /* Else If the infimum is below the global bound, we set the infimum to the global bound to remove only points outside of the enclosure */
         else if (varValues[state].inf < bound)
         {
            varValues[state].inf = bound;
            SCIPdbgMsg("     reduced interval by setting inf to bound\n");
         }
         else
         {
            //SCIPdbgMsg("interval is within bound, nothing to be done\n");
         }
         SCIPdbgMsg("     interval after applying enclosure for lb: [%f,%f]\n", varValues[state].inf,varValues[state].sup);
         assert(varValues[state].inf <= varValues[state].sup);
      }
      else /* Upper bound */
      {
         /* If [v,w] \cap enclosure is empty, we set w := \gamma = v
          * which is equivalent to                   sup = \gamma = inf */
         if (varValues[state].inf > bound)
         {
            varValues[state].sup= varValues[state].inf;
            SCIPdbgMsg("     degenerated bound to [sup, sup]\n");
         }
         /* Else If the supremum is above the global bound, we set the supremum to the global bound to remove only points outside of the enclosure */
         else if (varValues[state].sup > bound)
         {
            varValues[state].sup = bound;
            SCIPdbgMsg("     reduced interval by setting sup to bound\n");
         }
         else
         {
            SCIPdbgMsg("interval is within bound, nothing to be done\n");
         }
         SCIPdbgMsg("     interval afer applying enclosure for ub: [%f,%f]\n", varValues[state].inf,varValues[state].sup);
         assert(varValues[state].inf <= varValues[state].sup);
      }
   }
}

#if 0
      /* Apply lower bound */
      {
         std::vector<SCIP_Real> candidates;

         /* Add global enclosure */
         if ( globalEnclosureLbs_.find(n) != globalEnclosureLbs_.end() )
         {
            candidates.push_back(globalEnclosureLbs_[n]);
            if (execCount_ >= outCount) { SCIPdbgMsg("        added global enclosure candidate, %f\n",globalEnclosureLbs_[n]); }
         }
         /* Add local var bound */
         if (useVarBounds)
         {
            candidates.push_back(SCIPvarGetLbLocal(stateVar));
            if (execCount_ >= outCount) { SCIPdbgMsg("        added local var bound candidate, %f\n",(SCIPvarGetLbLocal(stateVar))); }
         }
         if (candidates.size() >= 1)
         {
            SCIPdbgMsg("execCount_ is %i, outCount is %i\n",execCount_, outCount);
            SCIP_Real bound(*(std::max_element(candidates.begin(), candidates.end())));
            if (execCount_ >= outCount) { SCIPdbgMsg("        applying best lower bound %f in dimension %i to interval [%f,%f]\n", bound, n, (*varIntervals)[n].inf,(*varIntervals)[n].sup); }

            /* If [v,w] \cap enclosure is empty, we set v := \gamma = w
             * which is equivalent to                   inf = \gamma = sup */
            if ((*varIntervals)[n].sup < bound)
            {
               (*varIntervals)[n].inf = (*varIntervals)[n].sup;
               if (execCount_ >= outCount) { SCIPdbgMsg("        degenerated bound to [sup, sup]\n"); }
            }
            /* Else If the infimum is below the global bound, we set the infimum to the global bound to remove only points outside of the enclosure */
            else if ((*varIntervals)[n].inf < bound)
            {
               (*varIntervals)[n].inf = bound;
               if (execCount_ >= outCount) { SCIPdbgMsg("        cut interval be setting inf to bound\n"); }
            }
            if (execCount_ >= outCount) { SCIPdbgMsg("        interval is now [%f,%f]\n", (*varIntervals)[n].inf,(*varIntervals)[n].sup); }
            SCIPdbgMsg("here i am\n");
            //assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
            SCIPdbgMsg("subscips epsilon is %1.16e\n",SCIPepsilon(subscip_));
            assert(SCIPisLE(subscip_,(*varIntervals)[n].inf, (*varIntervals)[n].sup));
         }
      }


      /* Apply upper bound */
      {
         if (execCount_ >= outCount) { SCIPdbgMsg("    finding best known upper bound\n"); }
         std::vector<SCIP_Real> candidates;

         /* Add global enclosure */
         if ( globalEnclosureUbs_.find(n) != globalEnclosureUbs_.end() )
         {
            candidates.push_back(globalEnclosureUbs_[n]);
            if (execCount_ >= outCount) { SCIPdbgMsg("        added global enclosure candidate, %f\n",globalEnclosureUbs_[n]); }
         }
         /* Add local var bound */
         if (useVarBounds)
         {
            candidates.push_back(SCIPvarGetUbLocal(stateVar));
            if (execCount_ >= outCount) { SCIPdbgMsg("        added local var bound candidate, %f\n",(SCIPvarGetUbLocal(stateVar))); }
         }
         if (candidates.size() >= 1)
         {
            SCIP_Real bound(*(std::min_element(candidates.begin(), candidates.end())));
            if (execCount_ >= outCount) { SCIPdbgMsg("        applying best upper bound %f in dimension %i to interval [%f,%f]\n", bound, n, (*varIntervals)[n].inf,(*varIntervals)[n].sup); }

            /* If [v,w] \cap enclosure is empty, we set w := \gamma = v
             * which is equivalent to                   sup = \gamma = inf */
            assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
            if ((*varIntervals)[n].inf > bound)
               (*varIntervals)[n].sup= (*varIntervals)[n].inf;
            /* Else If the supremum is above the global bound, we set the supremum to the global bound to remove only points outside of the enclosure */
            else if ((*varIntervals)[n].sup > bound)
               (*varIntervals)[n].sup = bound;

            if (execCount_ >= outCount) { SCIPdbgMsg("        interval is now [%f,%f]\n", (*varIntervals)[n].inf,(*varIntervals)[n].sup); }
            assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
         }
      }
      ++n;
#endif
   /* Apply polyhedral bounds (cut constraints)*/
   /*@todo*/


/* Implementation of procedure described in Definition 4 */
void SBrateEvaluator::applyEnclosure( int t, std::vector<SCIP_Interval> varValues, ctrl::SDproblemStructureInterface* structure)
{
   assert(structure->getCurrentTime()*structure->getTstep()  == t);

#if 0
   //int outCount(0);
   //if (execCount_ >= outCount) { SCIPdbgMsg("applying enclosure, structure has time %i\n",structure->getCurrentTime()); }
   unsigned int n(0);
   for (structure->startStateVarIteration(); structure->stateVarsLeft();structure->incrementStateVar())
   {
      SCIP_Bool useVarBounds(true);
      SCIP_VAR* stateVar = structure->getCurrentStateVar();
      assert(stateVar != NULL);
      if (execCount_ >= outCount) {  SCIPdbgMsg("  applying enclosure to var %i: %s\n",n, SCIPvarGetName(stateVar)); }

      /* Apply lower bound */
      {
         if (execCount_ >= outCount) { SCIPdbgMsg("    finding best known lower bound\n"); }
         std::vector<SCIP_Real> candidates;

         /* Add global enclosure */
         if ( globalEnclosureLbs_.find(n) != globalEnclosureLbs_.end() )
         {
            candidates.push_back(globalEnclosureLbs_[n]);
            if (execCount_ >= outCount) { SCIPdbgMsg("        added global enclosure candidate, %f\n",globalEnclosureLbs_[n]); }
         }
         /* Add local var bound */
         if (useVarBounds)
         {
            candidates.push_back(SCIPvarGetLbLocal(stateVar));
            if (execCount_ >= outCount) { SCIPdbgMsg("        added local var bound candidate, %f\n",(SCIPvarGetLbLocal(stateVar))); }
         }
         if (candidates.size() >= 1)
         {
            SCIPdbgMsg("execCount_ is %i, outCount is %i\n",execCount_, outCount);
            SCIP_Real bound(*(std::max_element(candidates.begin(), candidates.end())));
            if (execCount_ >= outCount) { SCIPdbgMsg("        applying best lower bound %f in dimension %i to interval [%f,%f]\n", bound, n, (*varIntervals)[n].inf,(*varIntervals)[n].sup); }

            /* If [v,w] \cap enclosure is empty, we set v := \gamma = w
             * which is equivalent to                   inf = \gamma = sup */
            if ((*varIntervals)[n].sup < bound)
            {
               (*varIntervals)[n].inf = (*varIntervals)[n].sup;
               if (execCount_ >= outCount) { SCIPdbgMsg("        degenerated bound to [sup, sup]\n"); }
            }
            /* Else If the infimum is below the global bound, we set the infimum to the global bound to remove only points outside of the enclosure */
            else if ((*varIntervals)[n].inf < bound)
            {
               (*varIntervals)[n].inf = bound;
               if (execCount_ >= outCount) { SCIPdbgMsg("        cut interval be setting inf to bound\n"); }
            }
            if (execCount_ >= outCount) { SCIPdbgMsg("        interval is now [%f,%f]\n", (*varIntervals)[n].inf,(*varIntervals)[n].sup); }
            SCIPdbgMsg("here i am\n");
            //assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
            SCIPdbgMsg("subscips epsilon is %1.16e\n",SCIPepsilon(subscip_));
            assert(SCIPisLE(subscip_,(*varIntervals)[n].inf, (*varIntervals)[n].sup));
         }
      }

      /* Apply upper bound */
      {
         if (execCount_ >= outCount) { SCIPdbgMsg("    finding best known upper bound\n"); }
         std::vector<SCIP_Real> candidates;

         /* Add global enclosure */
         if ( globalEnclosureUbs_.find(n) != globalEnclosureUbs_.end() )
         {
            candidates.push_back(globalEnclosureUbs_[n]);
            if (execCount_ >= outCount) { SCIPdbgMsg("        added global enclosure candidate, %f\n",globalEnclosureUbs_[n]); }
         }
         /* Add local var bound */
         if (useVarBounds)
         {
            candidates.push_back(SCIPvarGetUbLocal(stateVar));
            if (execCount_ >= outCount) { SCIPdbgMsg("        added local var bound candidate, %f\n",(SCIPvarGetUbLocal(stateVar))); }
         }
         if (candidates.size() >= 1)
         {
            SCIP_Real bound(*(std::min_element(candidates.begin(), candidates.end())));
            if (execCount_ >= outCount) { SCIPdbgMsg("        applying best upper bound %f in dimension %i to interval [%f,%f]\n", bound, n, (*varIntervals)[n].inf,(*varIntervals)[n].sup); }

            /* If [v,w] \cap enclosure is empty, we set w := \gamma = v
             * which is equivalent to                   sup = \gamma = inf */
            assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
            if ((*varIntervals)[n].inf > bound)
               (*varIntervals)[n].sup= (*varIntervals)[n].inf;
            /* Else If the supremum is above the global bound, we set the supremum to the global bound to remove only points outside of the enclosure */
            else if ((*varIntervals)[n].sup > bound)
               (*varIntervals)[n].sup = bound;

            if (execCount_ >= outCount) { SCIPdbgMsg("        interval is now [%f,%f]\n", (*varIntervals)[n].inf,(*varIntervals)[n].sup); }
            assert((*varIntervals)[n].inf <= (*varIntervals)[n].sup);
         }
      }
      ++n;
   }
   /* Apply polyhedral bounds (cut constraints)*/
   /*@todo*/

#endif
}


SCIP_Bool SBrateEvaluator::hasStateBound(int state, SCIP_BOUNDTYPE boundtype)
{
   BoundMap::iterator it = globalStateBounds_.find(BoundKey(state, boundtype));
   return it!=globalStateBounds_.end();
}

SCIP_Real SBrateEvaluator::getStateBound(int state, SCIP_BOUNDTYPE boundtype)
{
   return globalStateBounds_[BoundKey(state, boundtype)];
}


void SBrateEvaluator::addGlobalStateBound(int state, SCIP_BOUNDTYPE boundtype, SCIP_Real bound)
{
   if (hasStateBound(state, boundtype))
      globalStateBounds_[BoundKey(state,boundtype)] = (
                                boundtype == SCIP_BOUNDTYPE_LOWER ?
                                std::max(bound, getStateBound(state, boundtype)) :
                                std::min(bound, getStateBound(state, boundtype))
                           );
   else
      globalStateBounds_[BoundKey(state,boundtype)] = bound;

}

void SBrateEvaluator::printGlobalStateBounds()
{
   printf("Printing global State Bounds\n");
   for( auto it = globalStateBounds_.begin(); it != globalStateBounds_.end(); ++it)
   {
      int state = it->first.first;
      SCIP_BOUNDTYPE type = it->first.second;
      printf("global bound for state %i of type %i = %f\n", state, type, it->second);
   }

}

SBrateEvaluator::BoundMap SBrateEvaluator::getTightestEnclosure(const SBrateEvaluator::BoundMap& stateBounds)
{
   BoundMap tightestBounds(globalStateBounds_);
   for( auto it = stateBounds.begin(); it != stateBounds.end(); ++it)
   {
      BoundKey key = it->first;
      SCIP_BOUNDTYPE type = it->first.second;

      auto globalStateBoundsIt = globalStateBounds_.find(key);
      if (globalStateBoundsIt != globalStateBounds_.end())
      {
         tightestBounds[key] = (type == SCIP_BOUNDTYPE_LOWER
                              ? std::max(globalStateBoundsIt->second, it->second)
                              : std::min(globalStateBoundsIt->second, it->second) );
      }
      else
         tightestBounds[key] = it->second;
   }
   return tightestBounds;
}




