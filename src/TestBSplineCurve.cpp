#define SCIP_DEBUG
#define SCIP_DBG

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

/**@file    TestBSplineCurve.cpp
 * @brief   Test for ExprPiecewiseLinear
 * @author  Ingmar Vierhaus
 *
 */

#include "TestBSplineCurve.h"

namespace sdscip
{

TestBSplineCurve::TestBSplineCurve(SCIP* scip) :
    TestSDplugin(scip)
   ,tolerance_(1e-9)
   ,zeroTolerance_(1e-14)

{ }

TestBSplineCurve::~TestBSplineCurve()
{ }


std::ostream& TestBSplineCurve::toString(std::ostream& strm) const {
  return strm << "TestBSplineCurve";
}

/***********************************************
 *  Helper methods
 ***********************************************/

/* Check the lookup from world2 model */
void TestExprPiecewiseLinear::runEvalWorldLookup()
{
   SCIP_RETCODE retcode;
   SCIP_EXPR* expr;
   SCIP_EXPR* child;
   SCIP_VAR* arg;
   bool overestimate = true;

   std::vector<double> xvals = {0, 1, 2, 3, 4} ;

   std::vector<double> yvals = {0, 1, 1.8, 2.4, 2.7};

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(xvals, yvals);

   SCIPcreateVarBasic(subscip_, &arg, "argument", -SCIPinfinity(scip_), SCIPinfinity(scip_), 0, SCIP_VARTYPE_CONTINUOUS);
   retcode = SCIPexprCreate(SCIPblkmem(subscip_), &child, SCIP_EXPR_VARIDX, 0);
   assert(retcode == SCIP_OKAY);

   char identifier[7] = "lookup";

   retcode = SCIPexprCreatePiecewiseLinear( SCIPblkmem( subscip_ ), &expr, child, pcwlin , identifier);
   SCIPdbg( SCIPexprPiecewiseLinearPrintPoints(SCIPexprGetUserData(expr), SCIPgetMessagehdlr(scip_), NULL) );
   assert(retcode == SCIP_OKAY);
   SCIP_Real argvals;
   SCIP_Interval argbounds;
   SCIP_Real coeffs;
   SCIP_Real constant;
   SCIP_Bool success;
   argbounds.inf = -1e100;
   argbounds.sup = 1e100;
   SCIP_Interval val;

   retcode = SCIPexprEvalInt(expr, SCIPinfinity(scip_), &argbounds, NULL, &val);
   SCIPdbgMsg("Evaluated lookup in [%e,%e], returned [%f, %f]\n", argbounds.inf, argbounds.sup, val.inf, val.sup);
   assert(retcode == SCIP_OKAY);

   testEqual(val.inf, 0 );
   testEqual(val.sup, 2.7 );


   ++nExecutedTests_;
   SCIPexprFreeDeep(SCIPblkmem(subscip_), &expr);
   SCIPreleaseVar(subscip_, &arg);
}


/** Method running all tests of this class */
void TestBSplineCurve::runAll()
{
}

}
