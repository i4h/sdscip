/*
 * Point.h
 *
 *  Created on: 24.01.2014
 *      Author: bzfvierh
 */

#ifndef SD_GEOM_POINT_H_
#define SD_GEOM_POINT_H_

#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>
#include <iomanip>


namespace SDgeom {

class Point
{

public:
   typedef std::vector<double>  Components ;
   Point();
   Point(int _ndim);
   Point(std::vector<double> components);
   //Point(SDgeom::Vector vec);
   virtual ~Point();

   /* Shortcut constructors Used for testing    */
   Point(double x1, double x2);
   Point(double x1, double x2, double x3);


   std::string toString() const;
   void addDim(double);
   Components::iterator beginIt();
   Components::iterator endIt();
   Components::iterator lastIt();
   Point::Components::const_iterator constBeginIt() const;
   Point::Components::const_iterator constEndIt() const;
   Point::Components::const_iterator constLastIt() const;
   int getDim() const;
   void setComponent(int dim, double value);
   double getComponent(int dim) const;

protected:
   int ndim_;
   Components components_;
};

}

#endif /* SD_GEOM_POINT_H_ */
