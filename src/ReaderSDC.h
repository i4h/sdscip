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

/**@file   ReaderSDC.h
 * @brief  C++ file reader for SDC data files
 * @author Ingmar Vierhaus
 *
 */



#ifndef __SDCREADER_H__
#define __SDCREADER_H__

#include <iostream>
#include <fstream>
#include <string>

#include "sdscip.h"
#include "ProbDataSD.h"
#include "objscip/objscip.h"

namespace sdscip
{

/** SCIP file reader for SDC data files */
class ReaderSDC : public scip::ObjReader
{
public:

   SCIP_Bool round_lengths_;

   /** default constructor */
   ReaderSDC(SCIP* scip)
      : scip::ObjReader(scip, "sdcreader", "file reader for SDC files", "sdc")
   {
   }

   /** destructor */
   virtual ~ReaderSDC()
   {
   }

   /** destructor of file reader to free user data (called when SCIP is exiting) */
   virtual SCIP_DECL_READERFREE(scip_free);

   /** problem reading method of reader
    *
    *  possible return values for *result:
    *  - SCIP_SUCCESS    : the reader read the file correctly and created an appropritate problem
    *  - SCIP_DIDNOTRUN  : the reader is not responsible for given input file
    *
    *  If the reader detected an error in the input file, it should return with RETCODE SCIP_READERR or SCIP_NOFILE.
    */
   virtual SCIP_DECL_READERREAD(scip_read);

   /** problem writing method of reader; NOTE: if the parameter "genericnames" is TRUE, then
    *  SCIP already set all variable and constraint names to generic names; therefore, this
    *  method should always use SCIPvarGetName() and SCIPconsGetName();
    *
    *  possible return values for *result:
    *  - SCIP_SUCCESS    : the reader read the file correctly and created an appropritate problem
    *  - SCIP_DIDNOTRUN  : the reader is not responsible for given input file
    *
    *  If the reader detected an error in the writing to the file stream, it should return
    *  with RETCODE SCIP_WRITEERROR.
    */
   virtual SCIP_DECL_READERWRITE(scip_write);

private:
   sdscip::SDproblemStructureInterface* structure_;

};/*lint !e1712*/

} /* namespace sdc */

#endif
