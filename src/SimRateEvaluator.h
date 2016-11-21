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

/**@file    SimRateEvaluator.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDSCIP_SIMRATEEVALUATOR_H_
#define SDSCIP_SIMRATEEVALUATOR_H_

#include "PointRateEvaluator.h"
#include "BoundMapHelpers.cpp"
#include <string>

namespace sdscip{

class SimRateEvaluator: public PointRateEvaluator
{
public:
   SimRateEvaluator(int _nStates, SCIP* scip);
   SimRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~SimRateEvaluator();

   std::string getName() const;

   PointRateEvaluator* clone();

   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states);
   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params);

private:

};

}

#endif /* SDSCIP_SIMRATEEVALUATOR_H_ */
