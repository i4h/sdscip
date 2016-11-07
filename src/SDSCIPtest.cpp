/*
 * SDSCPItest.cpp
 *
 *  Created on: 05.11.2016
 *      Author: bzfvierh
 */

#include "SDSCIPtest.h"

namespace sdscip {

SDSCIPtest::SDSCIPtest()
{
   // TODO Auto-generated constructor stub

}

SDSCIPtest::SDSCIPtest(SCIP* _scip) :
   scip_(_scip)
{ }


SDSCIPtest::~SDSCIPtest()
{
   // TODO Auto-generated destructor stub
}

/* Overwrites testEqual of BaseTest using scips floating point comparison */
void SDSCIPtest::testEqual(double a, double b)
{
   // std::cout << "testing equality of " << a << " and " << b << std::endl;
   if (SCIPisEQ(scip_,a,b))
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      assert(false);
   }
}

}
