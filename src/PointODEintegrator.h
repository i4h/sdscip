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

/**@file    PointODEintegrator.h
 * @brief   ODE integrator class for scalar ODEs
 * @author  Ingmar Vierhaus
 *
 */


#ifndef POINTODEINTEGRATOR_H_
#define POINTODEINTEGRATOR_H_

#include "ODEintegrator.h"
#include "ProbDataSD.h"
#include "PointRateEvaluator.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "CopyablePointer.h"
#include "Vector.h"
#include <string>
#include "sdscip.h"
#include <fstream>

namespace sdscip
{


class PointODEintegrator : public ODEintegrator
{
   friend class ReduceODEintegrator;
public:
   PointODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls, PointRateEvaluator::POINT_RATE_EVALUATOR_TYPE _rateEvalType);
   virtual ~PointODEintegrator() = default;


   /* Copy constructor */
   //PointODEintegrator( const ODEintegrator &d ) : ODEintegrator(d)   { std::cout << "copy constructor\n" << std::endl << std::flush; }

   /* Move constructor */
   //PointODEintegrator(PointODEintegrator&& o) noexcept : ODEintegrator(o) { std::cout << "move failed!\n" << std::endl << std::flush; }


   //Object(const Object&) = delete;
   //Object(Object&&);

   /* Copy constructor */
   //PointODEintegrator(const ODEintegrator &d );
   //PointODEintegrator(const PointODEintegrator&);

   /* Copy assignment */
   //PointODEintegrator& operator=(const PointODEintegrator&);

   /* Move assignment */
   //PointODEintegrator& operator=(PointODEintegrator &&);

   CopyablePointer<PointRateEvaluator> rateEvaluator();

   std::vector<SCIP_Real> getStates();

   std::vector<SCIP_Real> getControls();
   SCIP_Real getState(int dim);
   SCIP_Real getAlgebraic(int varId);
   SCIP_Real getControl(int varId);
   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states);
   void setInitial(SCIP_Real t, std::vector<SCIP_Real> states, std::vector<SCIP_Real> controls);

   void step();
   void step(SCIP_Real* startParams, SCIP_Real* endParams);

   /* Helpers */
   std::string toString();

   std::string statesToString();
   std::string algebraicToString();
   void writeStates(std::ofstream& outFile);
   std::string controlsToString();
   void setXdots(std::vector<SCIP_EXPR*> &xDot);
   void setXdots(SCIP_EXPR** xDot);
   void setAlgebraicExpressions(SCIP_EXPR** algebraicExpressions);
   void printXdot();

   void computeAlgebraic(SCIP_Real* params);
   void setControls(const std::vector<SCIP_Interval>& controls);
   void setEndControls(const std::vector<SCIP_Interval>& endControls);

private:
/** First nStates_ items contain state var values,
   * following nControls items contain control values,
   * following nAlgebraic items contain space reserved
   * for the values of algebraic variables (are set by rateEvluator)
   * **/
   std::vector<SCIP_Real> varValues_;
   SCIP_Real tAlgebraic_;

   CopyablePointer<PointRateEvaluator> rateEvaluator_;
   std::vector<SCIP_Real> endControls_; /* To be used in the integration step */


}
;
}
#endif /* POINTODEINTEGRATOR_H_ */
