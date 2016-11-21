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

/**@file    ConstRateEvaluator.h
 * @brief   Rate evaluator for constant rates (used for testing)
 * @author  Ingmar Vierhaus
 *
 */


#ifndef CONSTRATEEVALUATOR_H_
#define CONSTRATEEVALUATOR_H_

#include "PointRateEvaluator.h"
#include <string>

namespace sdscip{

class ConstRateEvaluator: public PointRateEvaluator
{
public:
   ConstRateEvaluator(int _nStates, SCIP* scip);
   ConstRateEvaluator(int _nStates, int _nAlgebraic, int _nControls, SCIP* _scip);
   virtual ~ConstRateEvaluator();

   void setXdots(std::vector<SCIP_EXPR*> xDot);
   SCIP_EXPR* getXdot(int nDim);

   std::string getName() const;

   PointRateEvaluator* clone();

   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states);
   std::vector<SCIP_Real> getRates(SCIP_Real t, std::vector<SCIP_Real> states, SCIP_Real* params);
};

}

#endif /* CONSTRATEEVALUATOR_H_ */
