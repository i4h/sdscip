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

/**@file   reader_osilc.c
 * @ingroup FILEREADERS
 * @brief  OS instance language (OSiL) format file reader
 * @author Ingmar Vierhaus
 *
 * This reader is for the most part identical to the original osil reader.
 * Differences are:
 * - The SOS2 Constraint reader assumes that that constraints and variables follow
 *   the syntax used for gams control problems, i.e.
 *   - SOS2-Variables must be named variablename_[level]_8(t,sos2index)
 *   - Constraints must be named: consname_[level]_8_[v/k/n](t)
 *     with the meanings:
 *     - v: constraint defining the function value via the lamba values
 *     - a: constraint defining the argument of the function via the lambda values
 *     - n: Norm-Constraint, ( \f$\sum_k lambda_k = 1\f$ )
 *   - The SOS2 Constraint will then receive the name: SOS2-n_[level]_8_sos(t) with a running number n.
 *   The level describes the order, in which the equations need to be solved in the simulation case.
 *
 *   CF ProbDataSD.cpp
 */



#ifndef __SCIP_READER_OSILC_H__
#define __SCIP_READER_OSILC_H__


#include "sdscip.h"
#include <boost/regex.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/** includes the osilControl file reader into SCIP */
EXTERN
SCIP_RETCODE SCIPincludeReaderOsilC(
   SCIP*                 scip                /**< SCIP data structure */
   );

#ifdef __cplusplus
}
#endif

#endif
