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

/**@file    PropagationPattern.cpp
 * @brief   Propgation pattern used by PropOBRA
 * @author  Ingmar Vierhaus
 *
 */


#include "PropagationPattern.h"
#include "HyperCube.h"



PropagationPattern::PropagationPattern() :
   currentDim_(0)
   ,currentConfiguration_(0)
   ,currentTime_(-1)
   ,totalPatterns_(0)
   ,subscip_(NULL)
   ,scip_(NULL)
   ,configurationLoaded_(false)
   ,hyperCubeLoaded_(false)
   ,addCuts_(true)
   ,useUnitCuts_(true)
   ,usingUnitCutsNow_(true)
   ,currentConfIsCut_(false)
   ,cutConf3d_(0)
   ,patternType_(0)
   ,solMap_()
{
	stats_.reset();
}

PropagationPattern::PropagationPattern(int _confType) : PropagationPattern()
{
	PropagationPattern();
	patternType_ = _confType;
}


PropagationPattern::~PropagationPattern()
{
   // TODO Auto-generated destructor stub
}

void PropagationPattern::clearVars()
{
   vars_.clear();
   configurationLoaded_ = false;
   hyperCubeLoaded_ = false;
}

SCIP* PropagationPattern::getSubscip()
{
	return subscip_;
}

SCIP* PropagationPattern::getScip()
{
	return scip_;
}

void PropagationPattern::setSubscip(SCIP * subscip)
{
   subscip_ = subscip;
}
void  PropagationPattern::setScip(SCIP * scip)
{
   scip_ = scip;
}

void  PropagationPattern::setCurrentTime(int currentTime)
{
   currentTime_ = currentTime;
}


void PropagationPattern::addVar(SCIP_VAR * scipVar, SCIP_VAR * subscipVar)
{
	vars_.push_back(VarPair(scipVar, subscipVar));
}


/*
 * Gets the pattern for the current number of added variables,
 * prepares for the iteration with next()
 */
SCIP_RETCODE PropagationPattern::start() {
   assert(subscip_ != NULL);
   assert(scip_ != NULL);
   currentDim_ =  vars_.size();
   ensureValidPattern();
   currentConfiguration_ = -1;
   totalPatterns_ = pattern_[currentDim_].size();
   SCIP_CALL( SCIPsetObjsense(subscip_, SCIP_OBJSENSE_MAXIMIZE) );
   this->next();

   return SCIP_OKAY;
}

/*
 * Makes sure a valid pattern for ndim exists (implements cashing via instance variables),
 */
void PropagationPattern::ensureValidPattern()
{
   if (!patternValid_[currentDim_])
      if (this->fetchPattern(currentDim_))
         patternValid_[currentDim_] = true;

   assert(patternValid_[currentDim_]);
}

/*
 * Gets the pattern for ndim
 */
bool PropagationPattern::fetchPattern(int ndim)
{
   pattern_[ndim].clear();
   switch (ndim)
   {
      case 0:
      {
         break;
      }
      case 1:
      {
    	 if (patternType_ == 0)
    	 {
			 { static const double arr[] = { 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
    	 }
         break;
      }
      case 2:
      {

    	 if (patternType_ == 0)
    	 {
			 { static const double arr[] = { 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
    	 }
    	 else
    	 {
			 { static const double arr[] = { 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
    	 }
         break;
      }
      case 3:
      {
    	 if (patternType_ == 1)
    	 {
    		 SCIPmessagePrintError("MultiTimeCuts in 3d not implemented yet\n");
    	 }

    	 switch (cutConf3d_)
    	 {
    	 case 0:
    		 SCIPmessagePrintError("Pattern 0 not yet implemented for 3d problems\n");
    		 break;
    	 case 1:
			 { static const double arr[] = { 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0,-1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 1, 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 break;

    	 case 2:
    		 /* Direct bounds and corners */
			 { static const double arr[] = { 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0,-1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 1, 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 /* Sides */
			 { static const double arr[] = { 0, 1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0,-1, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0,-1,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 1, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1, 0,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 0,-1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }

			 { static const double arr[] = { 1, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 1,-1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = {-1,-1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 break;
    	 }

         break;
      }

      case 5:
          if (patternType_ == 1)
          {
             SCIPmessagePrintError("MultiTimeCuts in 3d not implemented yet\n");
             assert(false);
          }
			 { static const double arr[] = { 1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { -1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, -1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, -1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, -1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, -1,}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
         break;

      case 6:
          if (patternType_ == 1)
          {
             SCIPmessagePrintError("MultiTimeCuts in 3d not implemented yet\n");
             assert(false);
          }
			 { static const double arr[] = { 1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { -1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, -1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, -1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, -1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, -1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, -1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
         break;

      case 7:
          if (patternType_ == 1)
          {
             SCIPmessagePrintError("MultiTimeCuts in 3d not implemented yet\n");
             assert(false);
          }
			 { static const double arr[] = { 1, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { -1, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, -1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, -1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, -1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, -1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, -1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, -1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
         break;

      case 8:
          if (patternType_ == 1)
          {
             SCIPmessagePrintError("MultiTimeCuts in 3d not implemented yet\n");
             assert(false);
          }
			 { static const double arr[] = { 1, 0, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { -1, 0, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 1, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, -1, 0, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, -1, 0, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, -1, 0, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, -1, 0, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, -1, 0, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, 1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, -1, 0}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, 0, 1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
			 { static const double arr[] = { 0, 0, 0, 0, 0, 0, 0, -1}; pattern_[ndim].push_back(ObjectiveValuesVec (arr, arr + sizeof(arr) / sizeof(arr[0]) ) ); }
         break;



      default:
      {
         SCIPerrorMessage("no pattern for ndim = %i available\n",ndim);
         return false;
         break;
      }
   }
   return true;
}

void PropagationPattern::updateIsCut()
{
   int nonZeros(0);
   for (
      ObjectiveValuesVec::const_iterator it(pattern_[currentDim_][currentConfiguration_].begin()); it != pattern_[currentDim_][currentConfiguration_].end(); ++it)
   {
      if (!SCIPisZero(subscip_,(*it)))
         ++nonZeros;
   }
   assert(nonZeros != 0);
   currentConfIsCut_ = (nonZeros > 1);
}

bool PropagationPattern::isCut()
{
   assert(configurationLoaded_);
   return currentConfIsCut_;
}

std::pair<SDSCIP_PROPDIR, VarPair> PropagationPattern::getBoundVar()
{
   assert(configurationLoaded_);
   assert(!currentConfIsCut_);
	/*
	 * Iterate over variables and their (pattern) objective values
	 */
   for (
      std::pair<VarPairVec::const_iterator, ObjectiveValuesVec::const_iterator> it(vars_.begin(), pattern_[currentDim_][currentConfiguration_].begin());
      it.first != vars_.end() && it.second != pattern_[currentDim_][currentConfiguration_].end();
      ++it.first, ++it.second
   )
   {
      if (!SCIPisZero(subscip_,*it.second ))
      {
         if (*it.second > 0)
            return std::pair<SDSCIP_PROPDIR, VarPair>(SDSCIP_UP, *(it.first));
         else if (*it.second < 0)
            return std::pair<SDSCIP_PROPDIR, VarPair>(SDSCIP_DOWN, *(it.first));
      }
   }

   assert(false); /* Should have returned already */
   return std::pair<SDSCIP_PROPDIR, VarPair>(SDSCIP_DOWN, VarPair(NULL,NULL));

}


bool PropagationPattern::configurationsLeft() const
{
   //std::cout << "currently at conf " << currentConfiguration_ << "totalPatterns is " << totalPatterns_ << std::endl << std::flush;
   return (currentConfiguration_ < totalPatterns_ );
}


void PropagationPattern::next()
{
   assert(subscip_ != NULL);
   do
   {
      ++currentConfiguration_;
      if (!this->configurationsLeft())
         return;

      //std::cout << "Executing next, incremented, at conf " << currentConfiguration_ << std::endl << std::flush;
      assert(vars_.size() == pattern_[currentDim_][currentConfiguration_].size());

      configurationLoaded_ = true;
      this->updateIsCut();
   }
   while (     !( patternType_ == 1) /* Multitimecuts: add this cut (we configure the multitimecuts for the patternType at construction) */
	        &&  !(addCuts_  || !currentConfIsCut_) ); /* Consttimecut: Repeat until we should add cuts, or the configuration is not a cut */
   SCIPdbgMsg("found valid configuration\n");

   /* Decide if we want to use unit cuts */
   double factor(1);
   usingUnitCutsNow_  = ( useUnitCuts_ || !this->isCut() || !hyperCube_.areExtentsFinite(subscip_)); /* Use unit cuts if we are told to, or we can't use non-unit cuts */
   if (!usingUnitCutsNow_)
	   factor = hyperCube_.getNormalizationFactor();

   if (!useUnitCuts_ && !hyperCube_.areExtentsFinite(subscip_))
   {
	   SCIPdebugMessage("  not using unit cuts because hypercube has non-finite extent(s)\n");
	   //SCIPdebugMessage(hyperCube_.toString().c_str());
   }

   /*
    * Set the objective coefficients to the current configuration
    * it->first iterates variable pairs (scip, subscip), it->second iterates objective values
    * */
   for (
		   std::pair<VarPairVec::const_iterator, ObjectiveValuesVec::const_iterator> it(vars_.begin(), pattern_[currentDim_][currentConfiguration_].begin());
		   it.first != vars_.end() && it.second != pattern_[currentDim_][currentConfiguration_].end();
		   ++it.first, ++it.second
   )
   {
	   SCIP_VAR * subscipVar = it.first->second;
	   int currentDim(it.first - vars_.begin());

	   /* Handle non-unit cuts */
	   double varObj(*it.second);
	   if (!usingUnitCutsNow_)
	   {
		   varObj = varObj * factor * hyperCube_.getExtent(currentDim);
	   }
	   SCIP_RETCODE returnCode;
	   returnCode = SCIPchgVarObj(subscip_,subscipVar,varObj);
	   SCIPdbgMsg("set obj of var %s to %e\n",SCIPvarGetName(subscipVar),varObj);
	   assert(returnCode == SCIP_OKAY);
   }
}

void PropagationPattern::toString() const {
   std::cout << "Propagation Pattern (type " << patternType_ << ") " << vars_.size() << " Variables, currentDim: " << currentDim_ << std::endl;
   for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
   {
      std::cout << "     SCIP: "  << SCIPvarGetName(it->first) << " [" << std::setw(8) << SCIPvarGetLbLocal(it->first) << "," << std::setw(8) << SCIPvarGetUbLocal(it->first) << "]";
      std::cout << "  SUBSCIP: " << SCIPvarGetName(it->second) << " [" << std::setw(8) << SCIPvarGetLbLocal(it->second) << "," << std::setw(8) << SCIPvarGetUbLocal(it->second) << "]" << std::endl << std::flush;
   }
   std::cout << " Valid Patterns for dimensions";

   for( std::map<int, bool>::const_iterator it = patternValid_.begin(); it != patternValid_.end(); ++it)
   {
      if (it->second)
         std::cout << " ," << it->first;
   }
   std::cout << std::endl << std::flush;

   if (configurationLoaded_)
	   std::cout << "  Loaded configuration "<< this->confString() << std::endl << std::flush;

}

std::string PropagationPattern::confString() const
{
	assert(configurationLoaded_);
	std::ostringstream oss;

	for ( ObjectiveValuesVec::const_iterator it = pattern_.at(currentDim_).at(currentConfiguration_).begin();
			it != pattern_.at(currentDim_).at(currentConfiguration_).end(); ++it  )
	{
		if (it == pattern_.at(currentDim_).at(currentConfiguration_).begin())
			oss << *it;
		else
			oss << "," << *it;
	}
	std::string result(oss.str());
	std::replace( result.begin(), result.end(), '-', 'm'); /* the '-' in a constraint name is not compatible with gams */
	return result;
}

int PropagationPattern::getCurrentDim()
{
	return currentDim_;
}

SCIP_RETCODE PropagationPattern::setScipVarsArray(SCIP_VAR** vars) const
{
   for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
   {
	  int count(it - vars_.begin());
	  vars[count] = it->first;
   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::setSubscipVarsArray(SCIP_VAR** vars) const
{
   for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
   {
	  int count(it - vars_.begin());
	  vars[count] = it->second;
   }
   return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::buildHyperCube()
{
	hyperCube_ = sdscip::HyperCube();
	for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
	{
		hyperCube_.addDim(SCIPvarGetLbLocal(it->first),SCIPvarGetUbLocal(it->first));
	}
	hyperCubeLoaded_ = true;
	return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::setValsArray(SCIP_Real * vals)
{
	if (usingUnitCutsNow_)
	{
	   for ( ObjectiveValuesVec::const_iterator it = pattern_[currentDim_][currentConfiguration_].begin();
			   it != pattern_[currentDim_][currentConfiguration_].end(); ++it  )
	   {
		  int count(it - pattern_[currentDim_][currentConfiguration_].begin());
		  vals[count] = *it;
	   }
	}
	else
	{
		for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
		{
			int count(it - vars_.begin());
			vals[count] = SCIPvarGetObj(it->second);
		}
	}
	return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::setAddCuts(SCIP_Bool addCuts)
{
   addCuts_ = addCuts;
   return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::setSolMap( std::map<SCIP_VAR*, SCIP_Real>* solMap)
{
   solMap_ = solMap;
   return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::setUseUnitCuts(SCIP_Bool useUnitCuts)
{
   useUnitCuts_ = useUnitCuts;
   return SCIP_OKAY;
}


SCIP_RETCODE PropagationPattern::setCutConf3d(int confId)
{
   cutConf3d_ = confId;
   return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::cutIsUseful(SCIP_Real rhs, SCIP_Bool * isUseful)
{
	assert(hyperCubeLoaded_);
	SCIP_CALL( this->updateSubscipSolutionVector() );
	*isUseful = !(hyperCube_.isOnVertex(scip_,subscipSolutionVector_));
	return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::updateSubscipSolutionVector() {

	assert(SCIPgetStatus(subscip_) >= SCIP_STATUS_NODELIMIT && SCIPgetStatus(subscip_) <= SCIP_STATUS_OPTIMAL);
	subscipSolutionVector_ = sdscip::Vector();

	for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
	{
		SCIP_VAR * subscipVar = it->second;
		SCIP_SOL* subSol = SCIPgetBestSol(this->subscip_);
		SCIP_Real solVal(SCIPgetSolVal(subscip_,subSol,subscipVar));
		subscipSolutionVector_.addDim(solVal);
	}

	return SCIP_OKAY;
}

SCIP_RETCODE PropagationPattern::propagate(int currentTime)
{

	SCIP_Bool boundsDiverge = false;

	/* Get some parameters */
	int lookback(0);
	char* paramstr,*paramstr2;
	SCIP_Bool writeSubscips;
	SCIP_CALL( SCIPgetIntParam(this->scip_,"propagating/obra/lookback",&lookback));
	SCIPgetStringParam(scip_,"propagating/obra/outFile",&paramstr);
	SCIPgetStringParam(scip_,"propagating/obra/outDir",&paramstr2);
	SCIPgetBoolParam(scip_,"propagating/obra/writeSubscips",&writeSubscips);

	SCIPdebugMessage("entering solving loop------------------------ \n");

	/* Iterate over configurations */
	for (this->start(); (this->configurationsLeft() ); this->next() )
	{
		SCIPdebugMessage("  Loaded Configuration: %s\n",this->confString().c_str());

		if (writeSubscips)
		{
			std::ostringstream oss;
			oss << paramstr2 << paramstr << "_" << lookback << "_" << currentTime << "_pattern_" << this->currentConfiguration_ << "_subscip.cip";
			SCIPdebugMessage("  WRITING transformed subscip to file %s\n",oss.str().c_str());
			SCIP_CALL( SCIPwriteOrigProblem(this->subscip_, oss.str().c_str(), "cip", FALSE) );
		}

		SCIPdbgMsg("ready to solve SCIP\n");
		SCIP_Bool success;
		SCIPtransformProb(this->subscip_);

		/* Try solution values from main scip in subscip */
		if (solMap_->size() > 0)
		{
         SCIP_SOL* subscipSol;
         SCIP_CALL(SCIPcreateSol(this->subscip_,&subscipSol,NULL));
         for( auto iter = solMap_->begin(); iter != solMap_->end(); ++iter)
         {
            SCIPsetSolVal(this->subscip_, subscipSol, iter->first, iter->second);
         }
         SCIPtrySolFree(this->subscip_, &subscipSol, FALSE, TRUE, TRUE, TRUE, TRUE, &success);
         if (success == FALSE)
         {
            SCIPdebugMessage("  primal solution not accepted in subscip\n");
         }
		}

		//@todo _SD: Remove this line
		SDsetIsReformulated(this->subscip_,false);

		/* Solve the subscip */
		SCIP_CALL( SCIPsolve(this->subscip_) );

		stats_.aggSolutionTime += SCIPgetSolvingTime(this->subscip_);
		++stats_.nSubscips;
#ifdef SCIP_DEBUG
		SCIPdebugMessage("  Solved subscip, status: %s, Primal Bound: %f\n"
		   ,( SCIPgetStatus(subscip_) == SCIP_STATUS_OPTIMAL ? "optimal" : (SCIPgetStatus(subscip_) == SCIP_STATUS_NODELIMIT ? "nodelimit" : "not optimal, not nodelimit" ))
		   ,SCIPgetPrimalbound(subscip_));
#endif

		/* Evaluate subscip solution */
		if (SCIPgetStatus(this->subscip_) == SCIP_STATUS_UNBOUNDED)
		{
			boundsDiverge = true;
			SCIPdebugMessage("Set boundsDiverge to true because subproblem was unbounded\n");
			break;
		}
		else if (SCIPgetStatus(this->subscip_) == SCIP_STATUS_INFEASIBLE)
		{
			boundsDiverge = true;
			//SCIPprintTransProblem(this->subscip_,NULL,"cip",FALSE);
			SCIPdebugMessage("Set boundsDiverge to true because subproblem was infeasible\n");
			assert(false);
			break;
		}
		else if (   SCIPgetStatus(this->subscip_) == SCIP_STATUS_OPTIMAL
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_TIMELIMIT
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_GAPLIMIT
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_NODELIMIT
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_TOTALNODELIMIT
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_STALLNODELIMIT
				|| SCIPgetStatus(this->subscip_) == SCIP_STATUS_MEMLIMIT
		)
		{
			SCIPdbgMsg("got a result (optimal or limit), evaluating\n");
			if (!this->isCut())
			{
				double newBound;
				std::pair<SDSCIP_PROPDIR, VarPair> boundVar(this->getBoundVar());
				SCIP_VAR * scipVar = boundVar.second.first;
				SCIP_VAR * subscipVar = boundVar.second.second;
				++stats_.nDirectBounds;
				stats_.aggDirectSolutionTime += SCIPgetSolvingTime(this->subscip_);
				SCIPdebugMessage("  Evaluating direct bound for variable %s\n",SCIPvarGetName(scipVar));
				if (SCIPgetStatus(this->subscip_) == SCIP_STATUS_OPTIMAL)
				{
					SCIP_SOL* subSol = SCIPgetBestSol(this->subscip_);
					SCIP_Bool feasible;
					++stats_.nDirectOptimal;
					SCIPdbgMsg("optimal\n");

					newBound = SCIPgetSolVal(this->subscip_, subSol, boundVar.second.second);
					SCIPdbgMsg("new bound is %1.16e\n",newBound);
					//SCIPprintStatistics(this->subscip_, NULL);
					SCIP_CALL( SCIPcheckSolOrig(this->subscip_, subSol, &feasible, FALSE, FALSE) );

					if( !feasible )
					{
					   //SCIPwarningMessage(scip_, "sol is not feasible\n");
						SCIPdbgMsg("sol is not feasible\n");
						//assert(false);
						if (boundVar.first == SDSCIP_UP)
						{
							SCIPdbgMsg("sol is not feasible, increasing bound slightly\n");
							newBound += 1e-6;
						}
						else
						{
							SCIPdbgMsg("sol is not feasible, lowering bound slightly\n");
							newBound -= 1e-6;
						}
					}
					else
					{
					   SCIPdbgMsg("sol is feasible\n");
					}
				}
				else
				{
					SCIPdbgMsg("non-optimal\n");
					++stats_.nDirectNonOptimal;
					std::pair<SDSCIP_PROPDIR, VarPair> boundVar(this->getBoundVar());
					switch (boundVar.first)
					{
					case SDSCIP_UP:
						newBound = SCIPgetDualbound(this->subscip_);
						break;
					case SDSCIP_DOWN:
						/* Down means objective = -1 */
						newBound = -1.0 * SCIPgetDualbound(this->subscip_);
						break;
					}
					SCIPdbgMsg("newBound is %1.16e\n",newBound);
					SCIPdebugMessage("  did not solve to optimality\n");
				}
				SCIP_CALL( SCIPfreeTransform(this->subscip_) );

				SCIPdebugMessage( "  solved for %s of variable %-10s, old bounds: [%e,%e], newBound %e\n"
				   ,(boundVar.first == SDSCIP_DOWN ? "lb" : "ub")
				   ,SCIPvarGetName(scipVar), SCIPvarGetLbLocal(scipVar),SCIPvarGetUbLocal(scipVar),newBound );


				/* Set the new bound in scip and subscip if it is an improvement */
				//TODO _SD: Update hyperCube extent of Pattern
				if (boundVar.first == SDSCIP_UP && SCIPisLT(this->scip_,newBound,SCIPvarGetUbLocal(scipVar)))
				{
					/* Tighten upper bound */
					SCIP_Real oldBound(SCIPvarGetUbLocal(scipVar));
					SCIP_CALL( SCIPchgVarUb(this->subscip_,subscipVar,newBound)) ;
					SCIP_CALL( SCIPchgVarUb(this->scip_,scipVar,newBound) );
					SCIPdebugMessage( "  ub of %-10s tightened to %1.5e (was %1.5e, delta = %"
							"1.3e)\n",SCIPvarGetName(scipVar),SCIPvarGetUbLocal(scipVar),oldBound,SCIPvarGetUbLocal(scipVar)-oldBound );
					stats_.aggBoundReduction += oldBound - SCIPvarGetUbLocal(scipVar);
					stats_.aggRemainingBounds += SCIPvarGetUbLocal(scipVar);
					++stats_.nUpdatedBounds;
				}
				else if (boundVar.first == SDSCIP_DOWN && SCIPisGT(this->scip_,newBound,SCIPvarGetLbLocal(scipVar)))
				{
					/* Tighten upper bound */
					SCIP_Real oldBound(SCIPvarGetLbLocal(scipVar));
					SCIP_CALL( SCIPchgVarLb(this->subscip_,subscipVar,newBound) );
					SCIP_CALL( SCIPchgVarLb(this->scip_,scipVar,newBound) );
					SCIPdebugMessage( "  lb of %-10s tightened to %1.5e (was %1.5e, delta = %1.3e)\n",SCIPvarGetName(scipVar),SCIPvarGetLbLocal(scipVar),oldBound,oldBound - SCIPvarGetLbLocal(scipVar));
					stats_.aggBoundReduction += SCIPvarGetUbLocal(scipVar) - oldBound ;
					stats_.aggRemainingBounds += SCIPvarGetUbLocal(scipVar);
					++stats_.nUpdatedBounds;
				}
				else
				{
					SCIPdebugMessage("  did not tighten %s when working on non-cut of variable %s\n",(boundVar.first == SDSCIP_UP ? "ub" : "lb" ), SCIPvarGetName(scipVar));
				}
			}
			else /* Pattern is cut */
			{
				/* Create a constraint that will define the cut */
				SCIP_CONS* lincons;
				SCIP_Real rhs;
				int ndim(this->getCurrentDim());
				SCIP_Real* vals;
				SCIP_CALL( SCIPallocBufferArray(scip_, &vals, ndim) );
				SCIP_VAR** vars;
				SCIP_CALL( SCIPallocBufferArray(scip_, &vars, ndim) );

				++stats_.nCuts;
				stats_.aggCutsSolutionTime+= SCIPgetSolvingTime(this->subscip_);
				SCIPdebugMessage("  Evaluating cut\n");

				if (SCIPgetStatus(this->subscip_) == SCIP_STATUS_OPTIMAL)
				{
					rhs = SCIPgetPrimalbound(this->subscip_);
					++stats_.nCutsOptimal;
				}
				else
				{
					rhs = SCIPgetDualbound(this->subscip_);
					++stats_.nCutsNonOptimal;
				}

				/* Find out if the cut is useful */
				SCIP_Bool isUseful;
				SCIP_CALL( this->cutIsUseful(rhs, &isUseful) );
				if (!isUseful)
				{
					SCIPdebugMessage("  Cut is not useful\n");
					SCIP_CALL( SCIPfreeTransform(this->subscip_) );
				}
				else
				{
					++stats_.nCutsUseful;
					++stats_.usefulCutDistribution[this->confString()];
					SCIPdebugMessage("  Cut is useful, creating constraint\n");
					char name[SCIP_MAXSTRLEN];
					(void) SCIPsnprintf(name, SCIP_MAXSTRLEN, "propcut_%i(%i)(%s)", patternType_, currentTime , this->confString().c_str());

					SCIP_CALL (this->setScipVarsArray(vars));
					SCIP_CALL (this->setValsArray(vals));

					/* Create constraint and add to scip */
					//SCIPdebugMessage("coupling constraint to scip:\n");

					SCIP_CALL( SCIPcreateConsLinear(this->scip_, &lincons, name, ndim, vars, vals, -SCIPinfinity(this->scip_), rhs, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE) );
					SCIPdbgMsg("created cut constraint:\n");
					SCIPdbg( SCIPprintCons(this->scip_, lincons, NULL) );
					SCIP_CALL( SCIPaddCons(this->scip_, lincons) );
					SCIPdebugMessage("  Added cut to scip\n");

					/* Make constraint known in problem structure, so it will be considered in the next time steps */
					sdscip::SDproblemStructureInterface* structure(SDgetStructure(this->scip_));
					structure->addCut(lincons, currentTime);
					SCIP_CALL( SCIPreleaseCons(this->scip_, &lincons) );
					SCIP_Real solTime;
					solTime = SCIPgetSolvingTime(this->subscip_);

					/* Create constraint and add to subscip */
					SCIP_CALL (this->setSubscipVarsArray(vars));

					//SCIPdbgMsg("Found a cut the reduces this time slice by %e \n",vol);
					SCIPdebugMessage(" cf ; 	%i ; %i ; %s ; %e ; %f; %s\n"
									,patternType_
										 ,currentTime
											  ,getCutString().c_str()
												   ,rhs
														,solTime
														 	 ,name);

					SCIP_CALL( SCIPfreeTransform(this->subscip_) );

					SCIP_CALL( SCIPcreateConsLinear(this->subscip_, &lincons, name, ndim, vars, vals, -SCIPinfinity(this->subscip_), rhs, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE) );
					SCIP_CALL( SCIPaddCons(this->subscip_, lincons) );
					SCIP_CALL( SCIPreleaseCons(this->subscip_, &lincons) );
				} /* Close cut is useful */

				SCIPfreeBufferArray(scip_, &vals);
				SCIPfreeBufferArray(scip_, &vars);
			}
		}
		else
		{
			SCIPdebugMessage("subscip has unexpected status\n");
			assert(false);
		}

		if (boundsDiverge)
		{
			SCIPdbgMsg("end of pattern loop, boundsDiverge");
		}
		SCIP_CALL( this->resetObjVals() );
	}
	SCIPdbgMsg("returning from propagateWithPattern\n");
	return SCIP_OKAY;
}


std::string PropagationPattern::getCutString()
{
	std::ostringstream oss;
	/*
	 * Iterate over variables and their (pattern) objective values
	 */
	for (
			std::pair<VarPairVec::const_iterator, ObjectiveValuesVec::const_iterator> it(vars_.begin(), pattern_[currentDim_][currentConfiguration_].begin());
			it.first != vars_.end() && it.second != pattern_[currentDim_][currentConfiguration_].end();
			++it.first, ++it.second
	)
	{
		SCIP_VAR* scipVar((*it.first).first);
		SCIP_VAR* subscipVar((*it.first).second);

		double patternVal(*it.second);
		double objVal(SCIPvarGetObj(subscipVar));
		oss << SCIPvarGetName(scipVar) << " " << patternVal << " " << objVal << " ";
	}

	return oss.str();
}

/* Reset objective values of all objective variables of this pattern */
SCIP_RETCODE PropagationPattern::resetObjVals()
{
   for( VarPairVec::const_iterator it = vars_.begin(); it != vars_.end(); ++it)
   {
	   SCIPchgVarObj(this->subscip_,it->second,0);
   }
   return SCIP_OKAY;
}



