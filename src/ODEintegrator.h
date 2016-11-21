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

/**@file    ODEintegrator.h
 * @brief   Base class for ODE integrators
 * @author  Ingmar Vierhaus
 *
 */


#ifndef ODEINTEGRATOR_H_
#define ODEINTEGRATOR_H_

#include "ProbDataSD.h"
//#include "PointRateEvaluatorInterface.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "Vector.h"
#include <string>
#include "sdscip.h"

namespace sdscip
{

class ODEintegrator
{

public:

   ODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls);
   virtual ~ODEintegrator() = default;
   void setXdots(std::vector<SCIP_EXPR*> xDot);
   SCIP_Real getT();
   SCIP* getScip();

   void printVec(std::vector<double> vec, std::string message);
   void printXdot();

   int getNStates();
   int getNControls();
   int getNAlgebraic();

   //* Just for testing */
   void setNStates(int states);


protected:
   SCIP* scip_;
   int nStates_;
   int nControls_;
   int nAlgebraic_;
   SCIP_Real dt_;
   int nIntermediateSteps_;
   SCIP_Real dtIntermediate_;
   SCIP_Real t_;
   std::string discretization_;
   sdo::ButcherTableau tableau_;

};
}
#endif /* ODEINTEGRATOR_H_ */
