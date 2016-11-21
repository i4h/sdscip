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

/**@file    TestStatistics.h
 * @brief   Test class for basic statistics class
 * @author  Ingmar Vierhaus
 *
 */


#ifndef I4H_TESTSTATISTICS_H_
#define I4H_TESTSTATISTICS_H_

#include "Statistics.h"
#include "BaseTest.h"


namespace I4H
{

class TestStatistics : public BaseTest
{
public:
   TestStatistics();
   virtual ~TestStatistics();

   int getNsuccess();
   int getNerror();

   void runAll();

   void testMean();


   std::ostream& toString(std::ostream& strm) const;


private:
};

}

#endif /* I4H_TESTSTATISTICS_H_ */
