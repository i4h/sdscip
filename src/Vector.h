/*
 * Vector.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#ifndef SD_GEOM_VECTOR_H_
#define SD_GEOM_VECTOR_H_

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include <iostream>
#include "Point.h"


namespace SDgeom {


class Vector : public Point {

public:
   typedef std::vector<double>  Components ;
   typedef std::vector<double>::iterator ComponentIterator ;
   Vector();
   Vector(int _ndim);
   Vector(std::vector<double>);
   /* Shortcut constructors Used for testing */
   Vector(double x1, double x2);
   Vector(double x1, double x2, double x3);
   static std::string vec2string(std::vector<double> vec, std::string message);
   static void printVec(std::vector<double> vec, std::string message);

   virtual ~Vector();

   Vector& operator+=(Vector const& lhs);
   Vector& operator*=(double scalar);
   Vector& operator-=(Vector const& rhs);

   double length();


/*
   std::string toString();
   void addDim(double);
   Components::iterator beginIt();
   Components::iterator endIt();
   Components::iterator lastIt();
   int getDim();
   void setComponent(int dim, double value);

private:
   int ndim_;
   Components components_;
   */
};

Vector operator+( Vector lhs, Vector const & rhs );
Vector operator*( Vector lhs, double rhs );
Vector operator*( double rhs , Vector lhs);
/* Scalar product */
double operator*( Vector rhs , Vector lhs);
Vector operator-( Vector lhs, Vector const & rhs );
}

#endif /* SD_GEOM_VECTOR_H_ */
