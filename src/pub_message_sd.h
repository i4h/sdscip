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

/**@file   pub_message_sd.h
 * @ingroup PUBLICMETHODS
 * @brief  public methods for message output used in sdscip
 * @author Ingmar Vierhaus
  */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_PUB_MESSAGE__SD_H__
#define __SCIP_PUB_MESSAGE__SD_H__

#include <stdarg.h>

#include "scip/def.h"
#include "scip/type_message.h"

#ifdef __cplusplus
extern "C" {
#endif


/** SCIP_DBG introduces a second debug level for finer debug output then SCIPdebugMessage */
#ifdef SCIP_DBG
/** prints a debugging message if SCIP_DBG flag is set */
#define SCIPdbgMsg                printf("[%s:%d]   dbg: ", __FILE__, __LINE__); printf

/** prints debugging message in c++ "std::cout << ... " style*/
#define SCIPcppDbgMsg(x)         printf("[%s:%d]   dbg: ", __FILE__, __LINE__); std::cout << x



/** executes command only if SCIP_DEBUG flag is set */
#define SCIPdbg(x)                        x



#else


#define SCIPdbgMsg                while( FALSE ) printf

#define SCIPcppDbgMsg(x)

/** executes command only if SCIP_DEBUG flag is set */
#define SCIPdbg(x)

#endif

#endif
