/*
 * SDproblemStructureFactory.h
 *
 *  Created on: 05.02.2015
 *      Author: bzfvierh
 */

#ifndef SDPROBLEMSTRUCTUREFACTORY_H_
#define SDPROBLEMSTRUCTUREFACTORY_H_

#include "sdscip.h"
#include "SDproblemStructureInterface.h"
#include "SDproblemStructure.h"
#include "SDproblemStructureV1.h"


namespace sdscip {

class SDproblemStructureFactory
{
public:
   SDproblemStructureFactory();
   virtual ~SDproblemStructureFactory();
   static SDproblemStructureInterface* create(int version, SCIP* scip);
};

} /* namespace sdscip */

#endif /* SDPROBLEMSTRUCTUREFACTORY_H_ */
