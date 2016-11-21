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

/**@file    SDproblemStructureFactory.cpp
 * @brief   Factory for generation of problem structure depending on scip parameters
 * @author  Ingmar Vierhaus
 *
 */


#include "SDproblemStructureFactory.h"



namespace sdscip {

SDproblemStructureFactory::SDproblemStructureFactory()
{
   // TODO Auto-generated constructor stub

}

SDproblemStructureFactory::~SDproblemStructureFactory()
{
   // TODO Auto-generated destructor stub
}

SDproblemStructureInterface* SDproblemStructureFactory::create(int version, SCIP* scip)
{
   switch (version)
   {
   case 0:
      return new sdscip::SDproblemStructure(scip);
      break;
   case 1:
      return new sdscip::SDproblemStructureV1(scip);
      break;

      /* Add more versions here */

   default:
      SCIPerrorMessage("Configured Problem Structure Version does not exist\n");
   }
   return NULL;
}



} /* namespace sdscip */
