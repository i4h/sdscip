/*
 * TestBoundMap.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef TESTBOUNDMAP_H_
#define TESTBOUNDMAP_H_

#include "scip/scip.h"
#include "SDproblemStructureInterface.h"
#include "BoundMapHelpers.cpp"


namespace ctrl
{

class TestBoundMap
{
public:
   TestBoundMap();
   virtual ~TestBoundMap();

   int getNsuccess();
   int getNerrors();

   void runAll();
   void testUnion();
   void testOperations();

private:
   int nSuccess_;
   int nErrors_;
};

}

#endif /* TESTBOUNDMAP_H_ */
