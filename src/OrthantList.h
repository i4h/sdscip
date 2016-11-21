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

/**@file    OrthantList.h
 * @brief   Class representing list of orthants
 * @author  Ingmar Vierhaus
 *
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
