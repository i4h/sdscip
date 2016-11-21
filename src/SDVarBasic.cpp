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

/**@file    SDVarBasic.cpp
 * @brief   Class representing basic SD variable
 * @author  Robert L. Gottwald
 *
 */


#include "SDVarBasic.h"

namespace sdscip {

SDVarBasic::SDVarBasic()
{
   // TODO Auto-generated constructor stub

}

SDVarBasic::SDVarBasic( SCIP_VAR* _scipVar, unsigned int _time, int _type )
   : scipVar_(_scipVar)
   , time_(_time)
   , type_(_type)
{
   // TODO Auto-generated constructor stub

}

SDVarBasic::~SDVarBasic()
{
   // TODO Auto-generated destructor stub
}


const SCIP_VAR* SDVarBasic::getScipVariable() const
{
   return scipVar_;
}

SCIP_VAR* SDVarBasic::getScipVariable()
{
   return scipVar_;
}

unsigned int SDVarBasic::getTime() const
{
   return time_;
}

int SDVarBasic::getType() const
{
   return type_;
}



} /* namespace sdscip */


