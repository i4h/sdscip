#ifndef _EXPR_LOOKUP_H_
#define _EXPR_LOOKUP_H_


#include <spline/BSplineCurve.hpp>
#include <scip/type_retcode.h>
#include <blockmemshell/memory.h>
#include <scip/def.h>
#include <nlpi/type_expr.h>
#include <boost/shared_ptr.hpp>
#include "sdscip.h"

/**
 * Creates a piecewise linear expression using its piecewise cubic approximation
 * in order to have first and second derivatives.
 */
SCIP_RETCODE SCIPexprCreateLookup(
   BMS_BLKMEM           *blkmem,                 /**< block memory data structure */
   SCIP_EXPR           **expr,                   /**< pointer to buffer for expression address */
   SCIP_EXPR            *child,                  /**< child of lookup expression, i.e. argument to lookup */
   const boost::shared_ptr< spline::BSplineCurve<3, SCIP_Real> > &spline
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
void SCIPexprLookupSetEpsilon( SCIP_Real epsilon );

#endif
