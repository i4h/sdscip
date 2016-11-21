/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 20016     Ingmar Vierhaus <mail@ingmar-vierhaus.de>      */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    SDVarBasic.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
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


