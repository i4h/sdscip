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

/**@file    TestODEintegrator.h
 * @brief   Test class for ODEintegrator
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TESTODEINTEGRATOR_H_
#define TESTODEINTEGRATOR_H_

#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"
#include "SDSCIPtest.h"

namespace sdscip
{

class TestODEintegrator : public SDSCIPtest
{
public:
   TestODEintegrator(SCIP* scip);
   virtual ~TestODEintegrator();

   std::ostream& toString(std::ostream& strm) const;

   int getNsuccess();
   int getNerrors();

   void runAll();

   /* sim tests */
   void runSimTests();
   void runConstRateEvaluatorTest();
   void runPredatorPreySimTest();
   void runPredatorPreySimIntermediateStepsTest();

   /* sb tests */
   void runSBtests();
   void runPredatorPreySBsimTest();
   void runPredatorPreySBcontrolTest();
   void runPredatorPreySBglobalBoundsTest();
   void runPredatorPreySBboundsTest();

   std::vector<std::string> getTestDiscretizations();

   void createVar(SCIP_VAR* &var, const char* name , SCIP_Real lb, SCIP_Real ub, SCIP_Real obj, SCIP_VARTYPE vartype);
   std::vector<SCIP_EXPR*> getXdotPredatorPrey();


private:
   /* Private scip to hold memory for testing expressions */
   SCIP* subscip_;

   /* Vars to be released in destructor */
   std::vector<SCIP_VAR*> subscipVars_;

   /* Expressions to be freed in destructor */
   std::vector<SCIP_EXPR*> subscipExpressions_;

};

}

#endif /* TESTODEINTEGRATOR_H_ */
