/*
 * SdscipTest.h
 *
 *  Created on: 05.11.2016
 *      Author: bzfvierh
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
