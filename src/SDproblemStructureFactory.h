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

/**@file    SDproblemStructureFactory.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
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
