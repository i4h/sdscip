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

/**@file    PropagationPattern.h
 * @brief   Propgation pattern used by PropOBRA
 * @author  Ingmar Vierhaus
 *
 *
 * This class is owned by the PropOBRA (Optimization Based Reachability Analysis) plugin.
 * OBRA solves series of optimization problems corresponding to the dimensions and directions
 * of the state space of an SDO at a constant time.
 *
 * A PropagationPattern defines several configurations of objective function values, and the order in which
 * the resulting problems should be solved.
 *
 * In terms of containers, a pattern is a vector of configurations of objective function values, which is a vector of doubles.
 * If we have a problem with two objective variables, each objectiveValuesVec will have two elements.
 *
 * Variable pointers to the variables are set via setVars. With the call to start(), the pattern for the current dimension of the
 * state space is fetched by the class and the objective values for the first configuration in the pattern are set.
 * With each call to next() the next configuration is set. When there are no configurations left, patternsLeft() returns false. This allows
 * to iterate all patterns for a constant time with the following for loop:
 *    for (pattern_.start(); pattern_.patternsLeft(); pattern_.next())
 *    {
 *       //Solve the scip and evaluate results
 *    }
 *
 *  @todo: Use SCIP_RETCODE consistently in setters
 */



#ifndef PROPAGATIONPATTERN_H_
#define PROPAGATIONPATTERN_H_

#include "ProbDataSD.h"
#include "scip/primal.h"
#include "scip/cons_linear.h"
#include "scip/struct_scip.h"
#include "scip/type_mem.h"
#include "scip/struct_mem.h"

#include "HyperCube.h"


#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>



typedef std::vector<double> ObjectiveValuesVec;
typedef std::pair<SCIP_VAR *, SCIP_VAR *> VarPair;
typedef std::vector<VarPair > VarPairVec;
typedef std::vector<ObjectiveValuesVec> PatternVec;

enum SDSCIP_PropDir
{
   SDSCIP_UP               =  +1,       /**< normal termination */
   SDSCIP_DOWN             =  -1,       /**< unspecified error */
};
typedef enum SDSCIP_PropDir SDSCIP_PROPDIR;           /**< return code for SCIP method */



struct Statistics
{
	SCIP_Real aggRemainingBounds = 0;
	SCIP_Real aggBoundReduction = 0;
	SCIP_Real aggGapNonOptimal = 0;
	SCIP_Real aggSolutionTime = 0;
	SCIP_Real aggCutsSolutionTime = 0;
	SCIP_Real aggDirectSolutionTime = 0;
	int nSubscips = 0;
	int nCuts = 0;
	int nDirectBounds = 0;
	int nUpdatedBounds = 0;
	int nOptimal = 0;
	int nNonOptimal = 0;
	int nCutsOptimal = 0;
	int nCutsNonOptimal = 0;
	int nCutsUseful = 0;
	int nDirectOptimal = 0;
	int nDirectNonOptimal = 0;
	//TODO: Make sure variables always appear in the same order in the var-vectors of PropagationPatterns
	std::map<std::string,int> usefulCutDistribution;

	void reset()
	{
		aggRemainingBounds = 0;
		aggBoundReduction = 0;
		nSubscips = 0;
		nCuts = 0;
		nDirectBounds = 0;
		nUpdatedBounds = 0;
		nOptimal = 0;
		nNonOptimal = 0;
		aggGapNonOptimal = 0;
		aggSolutionTime = 0;
		usefulCutDistribution.clear();
   }
};

class PropagationPattern
{
public:
   PropagationPattern();
   PropagationPattern(int _confType);
   virtual ~PropagationPattern();

   void addVar(SCIP_VAR * scipVar, SCIP_VAR * subscipVar);
   bool configurationsLeft() const;
   bool fetchPattern(int ndim);
   void clearVars();
   void setSubscip(SCIP *);
   void setScip(SCIP *);
   void  setCurrentTime(int currentTime);
   SCIP* getSubscip();
   SCIP* getScip();
   SCIP_RETCODE start();
   void next();
   void toString() const;
   std::string confString() const;
   void ensureValidPattern();
   void updateIsCut();
   bool isCut();
   SCIP_RETCODE cutIsUseful(SCIP_Real rhs, SCIP_Bool * isUseful);
   int getCurrentDim();
   std::pair<SDSCIP_PROPDIR, VarPair> getBoundVar();
   SCIP_RETCODE setScipVarsArray(SCIP_VAR** vars) const;
   SCIP_RETCODE updateSubscipSolutionVector();
   SCIP_RETCODE setSubscipVarsArray(SCIP_VAR** vars) const;
   SCIP_RETCODE setValsArray(SCIP_Real * vals);
   SCIP_RETCODE setAddCuts(SCIP_Bool addCuts);
   SCIP_RETCODE setSolMap( std::map<SCIP_VAR*, SCIP_Real>* solMap);
   SCIP_RETCODE setCutConf3d(int confId);
   SCIP_RETCODE setUseUnitCuts(SCIP_Bool useUnitCuts);
   SCIP_RETCODE propagate(int currentTime);
   std::string  getCutString();
   SCIP_RETCODE resetObjVals();
   SCIP_RETCODE buildHyperCube();
   Statistics stats_;

   char identifier_;

private:
   VarPairVec vars_; /* Contains Varpairs: <scipVar, subscipVar> */
   int currentDim_;
   int currentConfiguration_;
   int currentTime_;
   int totalPatterns_;
   sdscip::HyperCube hyperCube_;
   sdscip::Vector subscipSolutionVector_;
   SCIP * subscip_;
   SCIP * scip_;
   bool configurationLoaded_;
   bool hyperCubeLoaded_;
   bool addCuts_;
   bool useUnitCuts_;
   bool usingUnitCutsNow_;
   bool currentConfIsCut_;
   std::map<int, PatternVec> pattern_;
   std::map<int, bool> patternValid_;
   int cutConf3d_; /* 0: Only surfaces, 1: surfaces + corners, 2: surfaces + edges + corners */
   int patternType_; /* 0: Configurations for constTimeCuts, 1: configurations for multiTimeCuts */
   std::map<SCIP_VAR*, SCIP_Real>* solMap_;

};

#endif /* PROPAGATIONPATTERN_H_ */
