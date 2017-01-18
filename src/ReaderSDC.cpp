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

/**@file   ReaderSDC.cpp
 * @brief  C++ file reader for SDC data files
 * @author Ingmar Vierhaus
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "objscip/objscip.h"

#include "ReaderSDC.h"

using namespace sdscip;


/** destructor of file reader to free user data (called when SCIP is exiting) */
SCIP_DECL_READERFREE(ReaderSDC::scip_free)
{
   return SCIP_OKAY;
} /*lint !e715*/

/** problem reading method of reader
 *
 *  possible return values for *result:
 *  - SCIP_SUCCESS    : the reader read the file correctly and created an appropriate problem
 *  - SCIP_DIDNOTRUN  : the reader is not responsible for given input file
 *
 *  If the reader detected an error in the input file, it should return with RETCODE SCIP_READERR or SCIP_NOFILE.
 */
SCIP_DECL_READERREAD(ReaderSDC::scip_read)
{
   SCIP_RETCODE retcode;


   *result = SCIP_SUCCESS;

   return SCIP_OKAY;
} /*lint !e715*/

/** writing method of sdc reader
 *
 * writes all cuts that are currently in problem structure to file
 */
SCIP_DECL_READERWRITE(ReaderSDC::scip_write)
{
   structure_ = SDgetStructure(scip_);
   for (int currentTime = structure_->startTimeIteration(); structure_->timesLeft(); currentTime = structure_->incrementTime())
   {
      SCIPinfoMessage(scip,file, "t = %i\n",currentTime );
      for (structure_->startCutIteration(); structure_->cutsLeft(); structure_->incrementCut())
      {
         SCIP_CONS* cut(structure_->getCut());
         assert(!SCIPconsIsDeleted(cut));
         SCIP_CALL( SCIPprintCons(scip, cut, file) );
         SCIPinfoMessage(scip, file, ";\n");
      }
   }
   *result = SCIP_SUCCESS;

   return SCIP_OKAY;
} /*lint !e715*/
