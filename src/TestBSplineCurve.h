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

/**@file    TestBSplineCurve.h
 * @brief   Test for ExprPiecewiseLinear
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TestBSplineCurve_H_
#define TestBSplineCurve_H_


#include "ProbDataSD.h"
#include "ExprPiecewiseLinear.h"
#include "Vector.h"
#include <boost/make_shared.hpp>
#include <spline/BSplineCurve.hpp>
#include <sdo/ExpressionGraph.hpp>
#include "BoundMapHelpers.cpp"
#include "TestSDplugin.h"
#include "Vector.h"
#include <sstream>



namespace sdscip
{

class TestBSplineCurve : public TestSDplugin
{

public:

   TestBSplineCurve(SCIP* scip);
   virtual ~TestBSplineCurve();

   /* Helpers */
   std::ostream& toString(std::ostream& strm) const;

   void runEvalWorldLookup();

   /* Run all tests */
   void runAll();

   /* Tolerance for floating point comparisons */
   const double tolerance_;

   /* (Low) Tolerance when comparing tightness of estimators */
   const double zeroTolerance_;

private:


};

}

#endif /* TestBSplineCurve_H_ */
