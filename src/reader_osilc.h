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

//#include
/**@file   reader_osilc.h
 * @ingroup FILEREADERS
 * @brief  OS instance language (OSiL) format file reader
 * @author Stefan Vigerske
 *
 * This reader allows to parse OSiL files with linear and nonlinear constraints and objective.
 * Writing is not implemented yet.
 *
 * The OSiL format is an XML based format to represent a broad class of mathematical programming instances, see http://www.coin-or.org/OS/OSiL.html .
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

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
