/*
 * OrthantList.cpp
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#include "OrthantList.h"

namespace sdscip {
using namespace sdscip;

OrthantList::OrthantList()
{
}

OrthantList::OrthantList(int ndim) {
   makeOrthants(ndim);
}


OrthantList::~OrthantList()
{
}

std::vector<Orthant>::iterator OrthantList::beginIt() {
   return orthants_.begin();
}
std::vector<Orthant>::iterator OrthantList::endIt() {
   return orthants_.end();
}


std::string OrthantList::toString() {
   std::ostringstream o;
   o << "List of " << orthants_.size() << " Orthants:" << std::endl;
   for(std::vector<Orthant>::iterator it = orthants_.begin(); it != orthants_.end(); ++it)
   {
      o << it->toString() << std::endl;
   }
   return o.str();
}

void OrthantList::makeOrthants(int ndim) {

   if (ndim == 1) /* Recursion root */
   {
      orthants_.clear();
      orthants_.reserve(2);
      Orthant orthPos(1);
      Orthant orthNeg(1);
      orthNeg.setAll(false);
      orthants_.push_back(Orthant(1));
      orthants_.push_back(orthNeg);
      return;
   }
   else
   {
      this->makeOrthants(ndim-1);
      int lastDimSize = orthants_.size();

      orthants_.reserve(2*lastDimSize); // preallocate memory for this dimensions

      // Add dimension to orthants and set positive
      for(std::vector<Orthant>::iterator it = orthants_.begin(); it != orthants_.end(); ++it)
         it->addDimFront(true);

      // Duplicate orthants
      orthants_.insert( orthants_.end(), orthants_.begin(), orthants_.end() );

      // Toggle first dimension the second half (just copied entries)
      std::vector<Orthant>::iterator it = orthants_.begin();
      std::advance(it,lastDimSize);
      while (it != orthants_.end())
      {
         it->toggleDimFront(true);
         ++it;
      }

      return;
   }
}
}
