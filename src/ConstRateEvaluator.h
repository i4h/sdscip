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

/**@file    ConstRateEvaluator.h
 * @brief   Rate evaluator for constant rates (used for testing)
 * @author  Ingmar Vierhaus
 *
 */


#ifndef CONSTRATEEVALUATOR_H_
#define CONSTRATEEVALUATOR_H_

#include "PointRateEvaluator.h"
#include <string>

namespace sdscip{

class ConstRateEvaluator: public PointRateEvaluator
{
public:
   ConstRateEvaluator(int _nStates, SCIP* scip);
   ConstRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~ConstRateEvaluator();

   void setXdots(std::vector<SCIP_EXPR*> xDot);
   SCIP_EXPR* getXdot(int nDim);

   std::string getName() const;

   PointRateEvaluator* clone();

   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states);
   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params);
};

}

#endif /* CONSTRATEEVALUATOR_H_ */
