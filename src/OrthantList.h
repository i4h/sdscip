/*
 * OrthantList.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#ifndef ORTHANTLIST_H_
#define ORTHANTLIST_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <iterator>

#include "Orthant.h"


namespace sdscip {


class OrthantList
{
public:
   typedef std::vector<Orthant>::iterator OrthantIterator;
   OrthantList();
   OrthantList(int ndim);
   virtual ~OrthantList();
   void makeOrthants(int ndim);
   std::string toString();
   std::vector<Orthant>::iterator beginIt();
   std::vector<Orthant>::iterator endIt();

private:
   std::vector<Orthant> orthants_;
};

}
#endif /* ORTHANTLIST_H_ */
