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

/**@file    SBrateEvaluator.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SBRATEEVALUATOR_H_
#define SBRATEEVALUATOR_H_

#include "PointRateEvaluator.h"
#include "SDproblemStructureInterface.h"
#include "BoundMapHelpers.cpp"
#include <string>
#include <map>

namespace sdscip{

class SBrateEvaluator : public PointRateEvaluator
{

   friend class TestSBrateEvaluator;
public:
   using BoundKey = SDproblemStructureInterface::BoundKey;
   using BoundMap = SDproblemStructureInterface::BoundMap;
   SBrateEvaluator(int _nStates, SCIP* scip);
   SBrateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~SBrateEvaluator();

   std::string getName() const;

   PointRateEvaluator* clone();



   /* Returns rates computed according to [1] in a way that looks like a pointIntegrator
    * Input:  vector states = (v_0, w_0, v_i, w_i, ..., v_n_x, w_n_x)
    *         Values of Controls U_i must be set in instance variable beforehand
    * Output: Rates in vector of form (v_0, w_0, v_i, w_i, ..., v_n_x, w_n_x)
    */
   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states);


   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params);


   /* Returns rates computed according to [1], using stateBounds as a priori enclosure
    * Input:  Elements v_i in varValues[i < nStates_].inf, w_i in varValues[w < nStates_].sup
    *         Intervals of Controls U_i in varValues[nStates <= i < nStates_ + nControls]
    *         varValues[nStates + nControls <= i < nStates_ + nControls_ + nAlgebraic_] contains space reserved for intervals of
    *         algebraic variables (computed by RateEvaluator )
    * Output: Rates of v in .inf of returned intervals
    *         Rates of w in .sup of returned intervals
    * WARNING: It is possible that in the returned rates rates[i].sup < rates[i].inf.
    *          because rates[i].inf, rates[i].sup are here just containers for \dot v and \dot w
    *          and don't have to be ordered.
    *          We do it this way (instead of vector<SCIP_Real>) to keep the correlation between varValues and rates
    *          DON'T use interval operations on the intervals in the returned vector
    */
   std::vector<SCIP_Interval> getRates(SCIP_Real t, std::vector<SCIP_Interval>& varValues,const BoundMap& stateBounds, SCIP_Real* params, SCIP_Real infinity);

   std::vector<SCIP_Interval> getOmega(int state, SCIP_BOUNDTYPE boundType, const std::vector<SCIP_Interval>& varValues, const BoundMap& stateBounds);

   /* Compute the values of the algebraic variables in varValues based on the state variables */
   void computeAlgebraic(std::vector<SCIP_Interval>& varValues, SCIP_Real* params, SCIP_Real infinity);

   /* Implements mapping \mathcal{B}_{state}^{boundType} according to Definition 2 of [1] */
   void applyB(int state, SCIP_BOUNDTYPE boundType, std::vector<SCIP_Interval>& varValues);
   void applyEnclosure(int state, SCIP_BOUNDTYPE boundType, const BoundMap& stateBounds, std::vector<SCIP_Interval>& varValues);

   SCIP_Real getStateBound(int state, SCIP_BOUNDTYPE boundtype);
   SCIP_Bool hasStateBound(int state, SCIP_BOUNDTYPE boundtype);

   void addGlobalStateBound(int state, SCIP_BOUNDTYPE, SCIP_Real bound);
   void printGlobalStateBounds();

private:

   /* Apply the local bounds of the state variables pointed to by structure as enclosure */
   void applyEnclosure( int t, std::vector<SCIP_Interval> varValues, sdscip::SDproblemStructureInterface* structure);

   /* Returns a map containing the tightest known bounds for all states/boundtype where bounds are known globally or from stateBounds parameter */
   BoundMap getTightestEnclosure(const BoundMap& stateBounds);

   std::map<std::pair<int, SCIP_BOUNDTYPE>, SCIP_Real> globalStateBounds_;


};

}

#endif /* SBRATEEVALUATOR_H_ */
