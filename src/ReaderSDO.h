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

/**@file   ReaderSDO.h
 * @brief  C++ file reader for SDO data files
 * @author Robert Lion Gottwald
 */

#ifndef __SDOREADER_H__
#define __SDOREADER_H__

#include "objscip/objscip.h"
#include "scip/pub_message.h"
#include "scip/def.h"

namespace sdo {
class ReaderSDO : public scip::ObjReader {
public:
     char *discretization;
     char *lookuptype;
     SCIP_Bool positiveStates;
     SCIP_Bool simplify;
     SCIP_Bool useMinVariableFormulation;
     SCIP_Bool isolatelookups;
     SCIP_Bool ratealgebraic;
     int multistep;
     int stepOverride;
     int nsinglesteps;
     SCIP_Real lookupMaxRelErr;
     SCIP_Real lookupAproxTol;
     
     ReaderSDO ( SCIP* scip ) :
        scip::ObjReader(scip, "sdoreader", "file reader for SDO files", "sdo" ),
        discretization(nullptr),
        lookuptype(nullptr)
     {
          SCIP_CALL_ABORT( SCIPaddStringParam ( scip, "reading/sdoreader/discretization",
                                                "Method used for discretization. Supported values are "
                                                "'rk2', 'rk3', 'rk4', 'imid2', 'gl4' or 'euler'",
                                                &discretization, 0, "euler", nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddStringParam ( scip, "reading/sdoreader/lookuptype",
                                                "Spline type used for lookups. Supported values are 'cubic' and 'linear'",
                                                &lookuptype, 0, "linear", nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddBoolParam ( scip, "reading/sdoreader/positiveStates",
                                              "If true, the lower bound of all states will be set to zero",
                                              &positiveStates, 0, false, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddBoolParam ( scip, "reading/sdoreader/simplify",
                                              "If true, the expressions will be simplified before they are stored in the prob structure",
                                              &simplify, true, true, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddIntParam ( scip,"reading/sdoreader/stepOverride",
                                              "If this is set to a positive value the number of steps given in the problem will be overriden by the value",
                                              &stepOverride, false, -1, -1, 1e6, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddBoolParam ( scip, "reading/sdoreader/isolatelookups",
                                              "If true, the lookups will get a variable for their argument and for their result",
                                              &isolatelookups, false, false, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddBoolParam ( scip, "reading/sdoreader/ratealgebraic",
                                              "If true, the rates of the states will get a variable",
                                              &ratealgebraic, false, false, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddBoolParam ( scip,"reading/sdoreader/minVariableFormulation",
                                              "If true the formulation will only create variables if they are needed, "
                                              "i.e. for states, controls and objective variables",
                                              &useMinVariableFormulation, 0, true, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddIntParam ( scip,"reading/sdoreader/multistep",
                                              "Use multistep method of given order for values greater than one",
                                              &multistep, false, 1, 1, 5, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddIntParam ( scip,"reading/sdoreader/nsinglesteps",
                                              "Number of additional starting values that should be produced by a singlestep method"
                                              "before a multistep method is used",
                                              &nsinglesteps, false, 1, 1, 4, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddRealParam( scip,"reading/sdoreader/lookupAproxTol",
                                             "The tolerance value used for cubic approximation of lookups",
                                             &lookupAproxTol, 0, 1e-6, 1e-16, 1e-3, nullptr, nullptr ) );

          SCIP_CALL_ABORT( SCIPaddRealParam( scip,"reading/sdoreader/lookupMaxRelErr",
                                             "The maximum relative error for cubic lookup approximations",
                                             &lookupMaxRelErr, 0, 0.05, 1e-3, 0.3, nullptr, nullptr  ) );

          SCIPaddBoolParam(scip, "reading/sdoreader/printSummary",
                                              "Show problem structure summary after reading a sdo file",
                                             NULL, false, true, nullptr, nullptr);

          SCIPaddBoolParam(scip, "reading/sdoreader/checkStructure",
                                             "Performs checks of problem structure after first read",
                                             NULL, FALSE, FALSE, NULL, NULL);

     }
     /** destructor */
     virtual ~ReaderSDO() {
     }

     /** destructor of file reader to free user data (called when SCIP is exiting) */
     virtual SCIP_DECL_READERFREE ( scip_free );

     /** problem reading method of reader
      *
      *  possible return values for *result:
      *  - SCIP_SUCCESS    : the reader read the file correctly and created an appropritate problem
      *  - SCIP_DIDNOTRUN  : the reader is not responsible for given input file
      *
      *  If the reader detected an error in the input file, it should return with RETCODE SCIP_READERR or SCIP_NOFILE.
      */
     virtual SCIP_DECL_READERREAD ( scip_read );

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
     virtual SCIP_DECL_READERWRITE ( scip_write );

private:

};


} /* namespace mdl */
#endif

