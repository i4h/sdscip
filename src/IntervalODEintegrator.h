/*
 * IntervalODEintegrator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */

#ifndef INTERVALODEINTEGRATOR_H_
#define INTERVALODEINTEGRATOR_H_

#include "ODEintegrator.h"
#include "ProbDataSD.h"
#include "PointRateEvaluator.h"
#include "ConstRateEvaluator.h"
#include "SimRateEvaluator.h"
#include "SBrateEvaluator.h"
#include "Vector.h"
#include <string>
#include "sdscip.h"
#include <fstream>
#include <sstream>


namespace sdscip
{


class IntervalODEintegrator : public ODEintegrator
{
public:
   enum INTERVAL_INTEGRATOR_CONTROL_MODE
   {
      CONTROL_MODE_SINGLE_INTERVAL = 0 /* Use the the SCIP_Interval given in varValues[nStates ... nStates + nControls - 1] for all rate evaluations */
      ,CONTROL_MODE_STARTMIDEND = 1 /* Use varValues[nStates ... nStates + nControls - 1] for t, endControls for t+\Delta t and midControls for everything else */
   };

   IntervalODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls);
   ~IntervalODEintegrator();

   using BoundMap = SDproblemStructure::BoundMap;
   using BoundKey = SDproblemStructure::BoundKey;

   SBrateEvaluator* rateEvaluator();

   SCIP_Interval getState(int dim);
   std::vector<SCIP_Interval> getStates();
   SCIP_Real getState(int dim, SCIP_BOUNDTYPE bndtype);
   std::vector<SCIP_Interval> getControls();

   void setInitial(SCIP_Real t, std::vector<SCIP_Interval> states, std::vector<SCIP_Interval> controls);
   void setInitial(SCIP_Real t, std::vector<SCIP_Interval> states);

   void setControl(int controlId, SCIP_Real inf, SCIP_Real sup);
   void setControls(const std::vector<SCIP_Interval>& controls);
   void setEndControls(const std::vector<SCIP_Interval>& endControls);


   /* Set varValues[nStates ... nStates + nControls - 1] = endControls, empty endControls_, midControls_ */
   void cycleControls();

   /* Used in the step() functions. Gets an approximated state vector at t \in (t, t + \dt]
    * using the appropriate control intervals
    *  input:
    *  - kMatrix         : the kMatrix build so far
    *  - s               : the current stage of the scheme
    *  - c               : the c_s value of the scheme (i.e. newX is an approximation of states at t = t + c * \Delta t)
    *                      we need this to decide which controlInterval to use
    *  */
   std::vector<SCIP_Interval> getNewX(const std::vector<std::vector<SCIP_Interval> >& kMatrix, const std::vector<double>& row, int s, SCIP_Real c);

   /* These functions perform a step from t_ to t_ + dt_, using the integrators current states,
    * control bounds and if applicable the stateBounds given as BoundMaps via function arguments*/
   void step(SCIP_Real* params = NULL);
   void step(const BoundMap& stateBounds, SCIP_Real* params = NULL);
   void step(const BoundMap& startStateBounds, const BoundMap& endStateBounds, SCIP_Real* params = NULL);
   void step(const BoundMap& startStateBounds, const BoundMap& midStateBounds, const BoundMap& endStateBounds, SCIP_Real* params = NULL);

   /* Check if the state bounds are diverging, i.e. ALL bounds are outside of SCIPinfinty */
   SCIP_Bool isDiverging() const;
   SCIP_Bool checkBounds(const BoundMap& bounds) const;

   /* Helpers */
   std::string toString();

   std::string statesToString();
   void writeStates(std::ofstream& outFile);
   std::string controlsToString();
   void setControlMode(INTERVAL_INTEGRATOR_CONTROL_MODE mode);
   void setXdots(std::vector<SCIP_EXPR*> xDot);
   void setXdot(SCIP_EXPR** xDot);
   void printXdot();

   /**
    * Performs sanity checks of the configured initial values.
    * Should be called after the initial set and  the control set were set.
    * */
   SCIP_Bool sane() const;

   /* How many orders of magnitude can lowest upper and highest lower bound of initial states be apart for Integrator to be sane*/
   SCIP_Real saneBoundGap_;


private:
   /* vector varValues_ contains the state of the integrator:
    * varValues[0,1,..nStates_-1].inf = \vec v
    * varValues[0,1,..nStates_-1].sup= \vec w
    * varValues[nStates-,nStates + 1, ... , nStates_ + nControls - 1] = U
    */
   std::vector<SCIP_Interval> varValues_;
   std::vector<SCIP_Interval> endControls_; /* To be used in the integration step, if set */
   std::vector<SCIP_Interval> midControls_; /* To be used in the integration step, if set */
   SCIP_Real infinity_;
   INTERVAL_INTEGRATOR_CONTROL_MODE controlMode_;

   SBrateEvaluator* rateEvaluator_; /* Computes right hand sides of (3) in [1] */


};
}
#endif /* INTERVALODEINTEGRATOR_H_ */
