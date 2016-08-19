/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2012 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file
 * @brief
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_PROBDATA_SD__
#define __SCIP_PROBDATA_SD__


#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "scip/scip.h"
#include "SDproblemStructureInterface.h"
#include "SDproblemStructureFactory.h"


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
   ctrl::SDproblemStructureInterface* structure;
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
SCIP_RETCODE SDprintStructure(SCIP* scip);
SCIP_RETCODE SDprintStateVarNames(SCIP *scip);
ctrl::SDproblemStructureInterface* SDgetStructure(SCIP* scip);

SCIP_RETCODE SDaddConsWithVars(SCIP_CONS* currentCons, SCIP* scip, SCIP* subscip,SCIP_HASHMAP* varmap, SCIP_HASHMAP* consmap, SCIP_Bool noObj, SCIP_Bool global, std::map<SCIP_VAR*, SCIP_Real>* solMap, SCIP_Bool copysol);

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
