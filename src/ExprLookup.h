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

/**@file    ExprLookup.h
 * @brief   User Expression for univariate lookup functions
 * @author  Robert L. Gottwald
 * @author  Ingmar Vierhaus
 *
 */


#ifndef _EXPR_LOOKUP_H_
#define _EXPR_LOOKUP_H_


#include <spline/BSplineCurve.hpp>
#include <scip/type_retcode.h>
#include <blockmemshell/memory.h>
#include <scip/def.h>
#include <nlpi/type_expr.h>
#include <boost/shared_ptr.hpp>
#include "sdscip.h"

/**
 * Creates a piecewise linear expression using its piecewise cubic approximation
 * in order to have first and second derivatives.
 */
SCIP_RETCODE SCIPexprCreateLookup(
   BMS_BLKMEM           *blkmem,                 /**< block memory data structure */
   SCIP_EXPR           **expr,                   /**< pointer to buffer for expression address */
   SCIP_EXPR            *child,                  /**< child of lookup expression, i.e. argument to lookup */
   const boost::shared_ptr< spline::BSplineCurve<3, SCIP_Real> > &spline
);
#if 0
   const spline::PiecewiseLinear &model,         /**< piecewise linear function that is approximated by given piecewise cubic function */
   const spline::PiecewiseCubic &lookup,         /**< piecewise cubic approximation of piecewise linear model */
   const spline::PiecewiseQuadratic &deriv,      /**< derivative of piecewise cubic function */
   const spline::PiecewiseLinear &secondDeriv    /**< second derivative of piecewise cubic function */
);
#endif

/**
 * Sets the epsilon value used for comparisons in the lookup expressions routines.
 */
void SCIPexprLookupSetEpsilon( SCIP_Real epsilon );

#endif
