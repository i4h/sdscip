/*
 * Line.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#ifndef SD_GEOM_LINE_H_
#define SD_GEOM_LINE_H_

#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
#include <iterator>

#include "Vector.h"
#include "Vector.h"
#include "HyperPlane.h"

namespace sdscip {

class Vector;
class HyperPlane;


class Line
{

public:
   typedef sdscip::Vector::Components::iterator ComponentIterator ;
   Line();
   Line(int _ndim);
   Line(sdscip::Vector a, sdscip::Vector b);
   virtual ~Line();

   /* Shortcut constructors Used for testing */

   std::string toString();
   sdscip::Vector intersection(const sdscip::HyperPlane *plane);
   /*
   Vector::Components::iterator aBeginIt();
   Vector::Components::iterator aEndIt();
   Vector::Components::iterator aLastIt();
   */
   int getDim();

private:
   int ndim_;
   Vector a_;
   Vector b_;
};

}

#endif /* SD_GEOM_LINE_H_ */
