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

/**@file    TestSDplugin.h
 * @brief   Base class for tests of SCIP plugins used by SD-SCIP
 * @author  Ingmar Vierhaus
 *
 */


#ifndef TestSDplugin_H_
#define TestSDplugin_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "ProbDataSD.h"
#include "PointODEintegrator.h"
#include "IntervalODEintegrator.h"
#include "PointRateEvaluator.h"
#include "SDSCIPtest.h"

namespace sdscip
{

class TestSDplugin : public SDSCIPtest
{
public:
   TestSDplugin(SCIP* scip);
   virtual ~TestSDplugin();

   //int getNsuccess();
   //int getNerrors();
   //int getNtests();

   /* Helpers */
   int getRandInt(int min, int max);
   int getRandInt(double min, double max);
   double getRandDouble(double min, double max);

protected:
   SCIP* subscip_; /* Private scip to hold memory for testing expressions */
   //int nSuccess_;
   //int nErrors_;
   //int nTests_;
};

}

#endif /* TestSDplugin_H_ */
