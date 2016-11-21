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

/**@file    TestBoundMap.h
 * @brief   Test class for BoundMap
 * @author  Ingmar Vierhaus
 *
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
