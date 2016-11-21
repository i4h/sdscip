/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 20016     Ingmar Vierhaus <mail@ingmar-vierhaus.de>      */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
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
