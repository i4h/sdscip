/*
 * Orthant.cpp
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#include "Orthant.h"

namespace SDgeom {
using namespace SDgeom;


Orthant::Orthant() :
      ndim_(0)
{ }


Orthant::Orthant(int _ndim) :
      ndim_(_ndim)
{
   // Initialize list
   for (int i = 0; i < ndim_; ++i) {
      //std::cout << "Pushing into halfspaces" << std::endl;
      halfSpaces_.push_back(true);
   }
}

Orthant::~Orthant()
{
   // TODO Auto-generated destructor stub
}

std::string Orthant::toString() {
   std::ostringstream o;
   o << ndim_ << "-dim. Orthant: (";
   std::deque<bool>::iterator last = halfSpaces_.end();
   --last;

   for(std::deque<bool>::iterator it = halfSpaces_.begin(); it != halfSpaces_.end(); ++it)
   {
      if (*it)
         o << '+';
      else
         o << '-';
      if (it != last)
         o << ',';
   }
   o << ')';
   return o.str();
}

Orthant::HalfSpaceIterator Orthant::beginIt() {
   return halfSpaces_.begin();
}
Orthant::HalfSpaceIterator Orthant::endIt() {
   return halfSpaces_.end();
}
Orthant::HalfSpaceIterator Orthant::lastIt() {
   HalfSpaceIterator it(halfSpaces_.end());
   --it;
   return it;
}

Orthant::ConstHalfSpaceIterator Orthant::constBeginIt() {
   return halfSpaces_.begin();
}
Orthant::ConstHalfSpaceIterator Orthant::constEndIt() {
   return halfSpaces_.end();
}



/*
 * Sets all elements of halfSpace_ to the given bool value
 */
bool Orthant::setAll(bool val) {
   for(std::deque<bool>::iterator it = halfSpaces_.begin(); it != halfSpaces_.end(); ++it)
      *it = val;
   return true;
}
/*
 * Adds a dimension and sets the value of that dimension to the given bool val
 */
bool Orthant::addDimFront(bool val) {
   halfSpaces_.push_front(val);
   ++ndim_;

   return true;
}

/*
 * Toggles the first halfSpace
 */
bool Orthant::toggleDimFront(bool val) {
   std::deque<bool>::iterator it = halfSpaces_.begin();
   if (*it)
      *it = false;
   else
       *it = true;

   return true;
}

bool Orthant::getHalfSpace(int dim) {
   assert(dim + 1 <= ndim_);
   return halfSpaces_[dim];
}



std::vector<Orthant> Orthant::getAllOrthants(int ndim) {

   if (ndim == 1) /* Recursion root */
   {
      std::vector<Orthant> result;
      result.reserve(2);
      Orthant orthPos(1);
      Orthant orthNeg(1);
      orthNeg.setAll(false);
      result.push_back(Orthant(1));
      result.push_back(orthNeg);
      return result;
   }
   else
   {
      std::vector<Orthant> result;
      std::vector<Orthant> subResult;
      subResult = Orthant::getAllOrthants(ndim-1);
      result.reserve( 2*subResult.size()); // preallocate memory for result
      // Add ndimension to subresult and set positive
      for(std::vector<Orthant>::iterator it = subResult.begin(); it != subResult.end(); ++it)
      {
         it->addDimFront(true);
      }
      // Copy to result
      result.insert( result.end(), subResult.begin(), subResult.end() );
      // Toggle first dimension in subresult
      for(std::vector<Orthant>::iterator it = subResult.begin(); it != subResult.end(); ++it)
      {
         it->toggleDimFront(true);
      }
      result.insert( result.end(), subResult.begin(), subResult.end() );

      return result;
   }
}

int Orthant::getDim() {
   return ndim_;
}


}

