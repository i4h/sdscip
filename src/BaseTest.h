/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 2012-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*    Copyright (C) 2016      Helmut-Schmidt University Hamburg              */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Lesser General Public License        */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.*/
/*                                                                           */
/*                                                                           */
/* Based on SCIP - Solving Constraint Integer Programs                       */
/* Copyright (C) 2002-2016 Zuse Institute Berlin                             */
/* SCIP is distributed under the terms of the SCIP Academic Licence,         */
/* see file COPYING in the SCIP distribution.                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    BaseTest.h
 * @brief   Base class for unit tests
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDSCIP_BASETEST_H_
#define SDSCIP_BASETEST_H_

#include <iostream>
#include <sstream>


namespace I4H {

class BaseTest
{
public:
   BaseTest();
   virtual ~BaseTest();

   /** Test that expression evaluates to true */
   virtual void test(bool t);

   /** Test that a and b are equal */
   virtual void testEqual(double a, double b);

   /** Run all tests */
   virtual void runAll() = 0;

   /* Successful checks while executing tests */
   int nSuccess_;

   /* Number of detected errors executing tests */
   int nError_;

   /* Number of executed tests */
   int nExecutedTests_;

   friend std::ostream& operator << (std::ostream& os, const BaseTest& derivedTest) {
     return derivedTest.toString(os); // polymorphic print via reference
   }

   /** Pure virtual toString method  */
   virtual std::ostream& toString(std::ostream&) const = 0;

   /* To be called by every test */
   void testStart();

   /** Output summary of tests */
   std::string summaryString() const;

private:

   double epsilon_ = 1e-6;


};

} /* namespace I4H */

#endif /* SDSCIP_BASETEST_H_ */
