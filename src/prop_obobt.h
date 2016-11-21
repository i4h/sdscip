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

//#include
/**@file    prop_obobt.h
 * @ingroup PROPAGATORS
 * @brief   optimization-based bound tightening propagator
 * @author  Stefan Weltge
 *
 * In Optimization-Based Bound Tightening (OBOBT), we solve auxiliary LPs of the form
 * \f[
 *      \min / \max \, \{ x_i \mid x \in P' \},
 * \f]
 * where \f$P'\f$ is the current LP relaxation restricted by the primal cutoff constraint \f$c^T x <= z\f$, \f$z\f$ the
 * current cutoff bound. Trivially, the optimal objective value of this LP provides a valid lower/upper bound on
 * variable \f$x_i\f$.
 *
 * Since solving LPs may be expensive, the propagator inspects solutions \f$x \in P'\f$ and does not run for variable
 * bounds which are tight at \f$x\f$: First, we check SCIP's last LP relaxation solution. Second, we solve a sequence of
 * filtering LP's \f$\min / \max \, \{ \sum w_i \, x_i \mid x \in P' \}\f$ in order to push several variables towards
 * one of their bounds in one LP solve. Third, we inspect all solutions of the auxiliary LPs solved along the way.
 *
 * By default, OBOBT is only applied for nonbinary variables that occur in nonlinear constraints.
 *
 * Additionally, the propagator uses the dual solution of the auxiliary LPs to construct globally valid generalized
 * variable bounds which may be propagated during the branch-and-bound search.
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_PROP_OBOBT_H__
#define __SCIP_PROP_OBOBT_H__


#include "sdscip.h"
#include "ProbDataSD.h"
#include "SDproblemStructureInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

/** creates the obobt propagator and includes it in SCIP */
EXTERN
SCIP_RETCODE SCIPincludePropObobt(
   SCIP*                 scip                /**< SCIP data structure */
   );

#ifdef __cplusplus
}
#endif

#endif
