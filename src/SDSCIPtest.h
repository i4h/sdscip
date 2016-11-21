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

/**@file    SDSCIPtest.h
 * @brief   Base class for SD-SCIP unit tests
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDSCIPTEST_H_
#define SDSCIPTEST_H_

#include "sdscip.h"
#include "BaseTest.h"

namespace sdscip {

class SDSCIPtest : public I4H::BaseTest
{
public:
   SDSCIPtest();
   SDSCIPtest(SCIP*);

   virtual ~SDSCIPtest();

   void testEqual(double a, double b);


   /** Pointer to a SCIP instance, needed for memory management,
     * floating point comparisons, etc.
     * */
   SCIP* scip_;

};

}

#endif /* SDSCIPTEST_H_ */
