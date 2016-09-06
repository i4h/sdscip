/*
 * SDVarBasic.h
 *
 *  Created on: 03.02.2015
 *      Author: bzfvierh
 */

#ifndef SDVARBASIC_H_
#define SDVARBASIC_H_

#include "sdscip.h"

namespace ctrl {

class SDVarBasic
{
public:
   SDVarBasic();
   SDVarBasic( SCIP_VAR* scipVar, unsigned int time, int type );
   virtual ~SDVarBasic();

   const SCIP_VAR* getScipVariable() const;
   SCIP_VAR* getScipVariable();
   unsigned int getTime() const;
   int getType() const;

private:
   SCIP_VAR* scipVar_;
   unsigned int time_;
   int type_;
};



} /* namespace ctrl */

#endif /* SDVARBASIC_H_ */
