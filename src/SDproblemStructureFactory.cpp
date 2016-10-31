/*
 * SDproblemStructureFactory.cpp
 *
 *  Created on: 05.02.2015
 *      Author: bzfvierh
 */



#include "SDproblemStructureFactory.h"



namespace sdscip {

SDproblemStructureFactory::SDproblemStructureFactory()
{
   // TODO Auto-generated constructor stub

}

SDproblemStructureFactory::~SDproblemStructureFactory()
{
   // TODO Auto-generated destructor stub
}

SDproblemStructureInterface* SDproblemStructureFactory::create(int version, SCIP* scip)
{
   switch (version)
   {
   case 0:
      return new sdscip::SDproblemStructure(scip);
      break;
   case 1:
      return new sdscip::SDproblemStructureV1(scip);
      break;

      /* Add more versions here */

   default:
      SCIPerrorMessage("Configured Problem Structure Version does not exist\n");
   }
   return NULL;
}



} /* namespace sdscip */
