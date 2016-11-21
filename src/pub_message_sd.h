/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#include
/**@file   pub_message_sd.h
 * @ingroup PUBLICMETHODS
 * @brief  public methods for message output based on scips pub_message.h
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
