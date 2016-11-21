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

/**@file    SDVarBasic.h
 * @brief   Class representing basic SD variable
 * @author  Robert L. Gottwald
 *
 */


#ifndef SDVARBASIC_H_
#define SDVARBASIC_H_

#include "sdscip.h"

namespace sdscip {

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



} /* namespace sdscip */

#endif /* SDVARBASIC_H_ */
