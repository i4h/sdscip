/*
 * SDVarBasic.cpp
 *
 *  Created on: 03.02.2015
 *      Author: bzfvierh
 */

#include "SDVarBasic.h"

namespace ctrl {

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



} /* namespace ctrl */


