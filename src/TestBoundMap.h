/*
 * TestBoundMap.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef TESTBOUNDMAP_H_
#define TESTBOUNDMAP_H_

#include "sdscip.h"
#include "SDproblemStructureInterface.h"
#include "BoundMapHelpers.cpp"
#include "SDSCIPtest.h"



namespace sdscip
{

class TestBoundMap : public SDSCIPtest
{
public:
   TestBoundMap(SCIP* _scip);
   virtual ~TestBoundMap();

   int getNsuccess();
   int getNerror();

   void runAll();
   void testOperations();

   std::ostream& toString(std::ostream& strm) const;


private:
};

}

#endif /* TESTBOUNDMAP_H_ */
