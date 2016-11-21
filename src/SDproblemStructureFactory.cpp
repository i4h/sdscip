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

/**@file    SDproblemStructureFactory.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
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
