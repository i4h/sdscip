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

/**@file   ProbDataSD.cpp
 * @brief  Problem data for SD-SCIP
 * @author Ingmar Vierhaus
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_PROBDATA_SD__
#define __SCIP_PROBDATA_SD__


#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "sdscip.h"
#include "SDproblemStructureInterface.h"
#include "SDproblemStructureFactory.h"
#include "pub_message_sd.h"


/* For usage of these classes see declaration of  class variables in ProbDataSD.h */


/* Classes used for construction */
typedef std::vector<SCIP_VAR*> VarVec;

typedef std::map<unsigned int, unsigned int> IntIntMap;

typedef std::pair<SCIP_CONS*,SCIP_VAR*> ConsVarPair;
/*
typedef std::pair<unsigned int, SCIP_VAR*> IntVarPair;
typedef std::map<unsigned int, SCIP_VAR* > IntVarMap;
*/
typedef std::vector< ConsVarPair > ConsVarVec;
typedef std::map<unsigned int, std::vector<SCIP_CONS*> > PropCutMap;

/*
typedef std::pair < int, ConsVarVec> TypeConsPair;
typedef std::map <int, TypeConsPair> LevelConsMap;

// Classes used for class variables 


// typedef std::map<unsigned int, ConsVarVec > ExplicitDifferentialMap;
// typedef std::map<unsigned int, std::vector<SCIP_CONS*> > AlgebraicMap;
// typedef std::map<unsigned int, LevelConsMap > AlgebraicConsMap;
// typedef std::map<unsigned int, std::map<unsigned int, IntVarPair > > VarTimeTypeMap;
// typedef std::map<unsigned int, VarVec > VarVecMap;
*/

/** @brief Problem data which is accessible in all places
 *
 * This problem data is used to store the input of the sd, all variables which are created, and all
 * Constraints.
 */


struct SCIP_ProbData
{
   sdscip::SDproblemStructureInterface* structure;
   PropCutMap* propCuts;
   bool isReformulated;
   bool isStructureValid;
#if 0

   VarTimeTypeMap* variableTypes;           /*variableTypes_[int time][int SCIPvarId] = std::pair<varType, Pointer>, varType= 0: state variable, varType = 1: algebraic */
   VarVecMap* controlVariables;
#endif

   boost::regex* varRegex;
   boost::regex* consRegex;

};


SCIP_RETCODE SDrefreshStructure(SCIP* scip);

SCIP_RETCODE SDensureValidStructure(SCIP* scip);
SCIP_RETCODE SDreadStructure(SCIP* scip);
//SCIP_RETCODE checkStructure(SCIP* scip);
SCIP_RETCODE SDcheckStructure(SCIP* scip);
SCIP_RETCODE SDprintStructureSummary(SCIP* scip);
SCIP_RETCODE SDprintStructure(SCIP* scip);
SCIP_RETCODE SDprintStateVarNames(SCIP *scip);
sdscip::SDproblemStructureInterface* SDgetStructure(SCIP* scip);

/* Getter methods for the problem data */

//ExplicitDifferentialMap* SDgetExplicitDifferentialMap(SCIP* scip);

PropCutMap* SDgetPropCuts(SCIP* scip);


/*

AlgebraicConsMap* SDgetAlgebraicConstraints(SCIP* scip);

VarTimeTypeMap* SDgetVariableTypes(SCIP* scip);

VarVecMap* SDgetControlVariables(SCIP* scip);

boost::regex* SDgetVarRegex(SCIP *scip);

boost::regex* SDgetConsRegex(SCIP *scip);

*/

void SDsetIsReformulated(SCIP* scip, bool isReformulated);
bool SDgetIsReformulated(SCIP* scip);

void SDsetIsStructureValid(SCIP * scip, bool isValid);
bool SDgetIsStructureValid(SCIP *scip);


bool SDisEquation(SCIP* scip, SCIP_CONS* cons);

std::string SDgetVarBasename(SCIP_VAR* var);


/* Useful functions in the SD context*/

SCIP_RETCODE SDfixVarProbingExact(SCIP* scip, SCIP_VAR* var, SCIP_Real fixVal);


/** creates the setup dialog and includes it in SCIP */

SCIP_RETCODE SCIPincludeDialogSD(
   SCIP*                 scip                /**< SCIP data structure */
				    );


SCIP_RETCODE SCIPincludeDialogSDinit(
   SCIP*                 scip                /**< SCIP data structure */
				    );

SCIP_RETCODE SCIPincludeDialogSDprintStructure(
   SCIP*                 scip                /**< SCIP data structure */
				    );

SCIP_RETCODE SCIPincludeDialogSDensureValidStructure(
   SCIP*                 scip                /**< SCIP data structure */
   );

SCIP_RETCODE SCIPincludeDialogWriteTransprobSD(
   SCIP*                 scip                /**< SCIP data structure */
				    );

SCIP_RETCODE SCIPincludeDialogSDrefreshStructure(
   SCIP*                 scip                /**< SCIP data structure */
				    );


SCIP_RETCODE SCIPincludeDialogSDdoSomething(
   SCIP*                 scip                /**< SCIP data structure */
   );

SCIP_RETCODE SCIPincludeDialogSDdisable(
   SCIP*                 scip                /**< SCIP data structure */
   );

SCIP_RETCODE SCIPaddParamsSD(
   SCIP*                 scip                /**< SCIP data structure */
);


SCIP_RETCODE SDinit(SCIP* scip);

#endif
