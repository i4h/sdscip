#ifndef _EXPR_PIECWEWISE_LINEAR_H_
#define _EXPR_PIECWEWISE_LINEAR_H_
#define EXPR_PCW_LIN_TEST_ESTIMATIONS

#include "TestExprPiecewiseLinear.hpp"

#include <spline/BSplineCurve.hpp>
#include <scip/type_retcode.h>
#include <blockmemshell/memory.h>
#include <scip/def.h>
#include <nlpi/type_expr.h>
#include <boost/shared_ptr.hpp>
#include <fenv.h>
#include <float.h>

#ifdef EXPR_PCW_LIN_TEST_ESTIMATIONS
#include "TestExprPiecewiseLinear.hpp"
#endif

enum SAFE_ESTIMATOR
{
   SAFE_ESTIMATOR_TYPE_1 = 1,
   SAFE_ESTIMATOR_TYPE_2 = 2,
   SAFE_ESTIMATOR_TYPE_3 = 3,
   SAFE_ESTIMATOR_TYPE_4 = 4,
   SAFE_ESTIMATOR_TYPE_5 = 5,
   SAFE_ESTIMATOR_TYPE_6 = 6,
};


/**
 * Creates a piecewise linear expression using its piecewise cubic approximation
 * in order to have first and second derivatives.
 */
SCIP_RETCODE SCIPexprCreatePiecewiseLinear(
   BMS_BLKMEM           *blkmem,                 /**< block memory data structure */
   SCIP_EXPR           **expr,                   /**< pointer to buffer for expression address */
   SCIP_EXPR            *child,                  /**< child of lookup expression, i.e. argument to lookup */
   const boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > &pcwlin,
   std::string           identifier
);
#if 0
   const spline::PiecewiseLinear &model,         /**< piecewise linear function that is approximated by given piecewise cubic function */
   const spline::PiecewiseCubic &lookup,         /**< piecewise cubic approximation of piecewise linear model */
   const spline::PiecewiseQuadratic &deriv,      /**< derivative of piecewise cubic function */
   const spline::PiecewiseLinear &secondDeriv    /**< second derivative of piecewise cubic function */
);
#endif

/**
 * Sets the epsilon value used for comparisons in the lookup expressions routines.
 */
void SCIPexprPiecewiseLinearSetEpsilon( SCIP_Real epsilon );

/**
 * Prints the points of the piecewise linear expression
 */
void SCIPexprPiecewiseLinearPrintPoints(SCIP_USEREXPRDATA* data, SCIP_MESSAGEHDLR*  messagehdlr, FILE* file);

SAFE_ESTIMATOR selectEstimator(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Bool e5valid, SCIP_Bool e6valid);

/** Computes the closest upwards (downwards) rounded representation of y1 - x1*m
 *  when mup is true (false)
 */


#ifdef EXPR_PCW_LIN_TEST_ESTIMATIONS
SCIP_RETCODE estimateSafe(
   SCIP_Bool overestimate,
   SCIP_Real lb,
   SCIP_Real ub,
   SCIP_Real argval ,
   SCIP_Real x1,
   SCIP_Real x2,
   SCIP_Real y1,
   SCIP_Real y2,
   SAFE_ESTIMATOR estimator,
   SCIP_Real *coefficient,
   SCIP_Real *intercept
   );
#endif

boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > SCIPexprPiecewiseLinearGetSpline(SCIP_USEREXPRDATA* data);

#endif
