/*
 * BaseTest.cpp
 *
 *  Created on: 31.10.2016
 *      Author: bzfvierh
 */

#include "BaseTest.h"

namespace sdscip {

BaseTest::BaseTest()
{
   // TODO Auto-generated constructor stub

}

BaseTest::~BaseTest()
{
   // TODO Auto-generated destructor stub
}

void BaseTest::test(bool t) {
   if (t)
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      assert(false);
   }
}

} /* namespace sdscip */
