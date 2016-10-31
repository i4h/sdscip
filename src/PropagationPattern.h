/*
 * PropagationPattern.h
 *
 *  Created on: 30.04.2014
 *      Author: bzfvierh
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

/* A pattern defines several configurations of objective function values, and the order in which
 * the resulting problems should be solved.
 *
 * In terms of Containers, a pattern is a vector configurations of objective function values, which is a vector of doubles.
 * If we have a problem with two objective variables, each objectiveValuesVec will have two elements.
 *
 * Variable pointers to the variables are set via setVars. With the call to start(), the pattern for the current number of variable
 * is fetched by the class and the objective values for the first configuration in the pattern are set.
 * With each call to next() the next configuration is set. When there are no configurations left, patternsLeft() returns false. This allows
 * to iterate with the following for loop after setting the variables:
 *    for (pattern_.start(); pattern_.patternsLeft(); pattern_.next())
 *    {
 *       //Solve the scip and evaluate results
 *    }
 */


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


struct test_struct
{
   unsigned int          eventqueueimpl:1;   /**< is an IMPLADDED event on this variable currently in the event queue? */
};

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

   //void addVar(SCIP_VAR *);
   void addVar(SCIP_VAR * scipVar, SCIP_VAR * subscipVar);
   void addStruct(test_struct *);
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

private:
   VarPairVec vars_; /* Contains Varpairs: <scipVar, subscipVar> */
   std::vector<test_struct *> structs_;
   std::vector<double> testVec_;
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
