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

/**@file    Orthant.h
 * @brief   Orthant class used by sdscip
 * @author  Ingmar Vierhaus
 *
 */


#ifndef ORTHANT_H_
#define ORTHANT_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <iterator>

namespace sdscip {


class Orthant
{
public:
   typedef std::deque<bool>::iterator  HalfSpaceIterator ;
   typedef std::deque<bool>::const_iterator  ConstHalfSpaceIterator ;
   Orthant();
   Orthant(int _ndim);
   virtual ~Orthant();
   std::string toString();
   HalfSpaceIterator beginIt();
   HalfSpaceIterator endIt();
   ConstHalfSpaceIterator constBeginIt();
   ConstHalfSpaceIterator constEndIt();

   HalfSpaceIterator lastIt();
   static std::vector<Orthant> getAllOrthants(int ndim);
   bool setAll(bool val);
   bool addDimFront(bool val);
   bool toggleDimFront(bool val);
   bool getHalfSpace(int dim);
   int getDim();


private:
   int ndim_;
   std::deque<bool> halfSpaces_; //Defines the orthand (true = +, false = -)

};
}
#endif /* ORTHANT_H_ */
