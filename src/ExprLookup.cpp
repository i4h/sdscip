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

/**@file    ExprLookup.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "ExprLookup.h"
#include <nlpi/type_expr.h>
#include <nlpi/pub_expr.h>
#include <nlpi/intervalarithext.h>
#include <blockmemshell/memory.h>
#include <spline/BSplineCurve.hpp>
#include <cmath>
#include <scip/intervalarith.h>
#include <scip/pub_message.h>
#include <spline/UnivariateSplineEstimator.hpp>
#include <fstream>

using boost::shared_ptr;
using std::isfinite;

static SCIP_Real EPSILON = 1e-9;

inline static
bool is_equal( SCIP_Real a, SCIP_Real b )
{
   return EPSEQ(a, b, EPSILON);
}

struct SCIP_UserExprData
{
   shared_ptr< spline::BSplineCurve<3, SCIP_Real> > lookup;
};

/**
 * Returns a point inside the given interval.
 */
inline static
SCIP_Real pointInsideInterval(
   SCIP_Real infinity,             /**< value of infinity */
   SCIPInterval interval        /**< the interval that the returned value should be contained in */
)
{
   SCIP_Real inf = SCIPintervalGetInf( interval );
   SCIP_Real sup = SCIPintervalGetSup( interval );

   if( inf <= 0.0 && sup >= 0.0)
      return 0.0;

   if( std::abs(inf) < std::abs(sup))
      return inf;

   return sup;
}

static SCIP_DECL_USEREXPRESTIMATE( estimateLookup )
{
   assert( nargs == 1 );
   *success = false;

   SCIP_Real lb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real ub = SCIPintervalGetSup( argbounds[0] );

   if( lb <= -infinity ) 
   {
      if(ub >= infinity)
         return SCIP_OKAY;

      SCIP_Real val = overestimate ? data->lookup->findMax(lb, ub, EPSILON) : data->lookup->findMin(lb, ub, EPSILON);

      if(argvals[0] <= val || val <= -infinity)
         return SCIP_OKAY;

      lb = val;
   }
   else if(ub >= infinity)
   {
      SCIP_Real val = overestimate ? data->lookup->findMax(lb, ub, EPSILON) : data->lookup->findMin(lb, ub, EPSILON);

      if(argvals[0] >= val || val >= infinity)
         return SCIP_OKAY;

      ub = val;
   }

   SCIPdbgMsg("%sestimating lookup with bounds [%g,%g]\n", overestimate ? "over" : "under" , lb, ub);

   if( is_equal( lb, ub ) )
   {
      SCIPdbgMsg( "Bounds are equal for lookup arg -> coeff is zero\n" );
      SCIPdbgMsg( "bounds of arg = [%.16g,%.16g]\n", lb, ub );

      coeffs[0] = 0.0;
      SCIP_Real lbval = data->lookup->operator()(lb);
      SCIP_Real ubval = data->lookup->operator()(ub);
      *constant = overestimate ? std::max(lbval, ubval) : std::min(lbval,ubval);
   }
   else
   {
      spline::UnivariateSplineEstimator< spline::BSplineCurve<3, SCIP_Real> > estimator(*(data->lookup), lb, ub, overestimate, EPSILON*1e-2);

      auto interval = estimator.findInterval(argvals[0]);

      coeffs[0] = estimator.template evaluate<1>(argvals[0], interval);
      if(coeffs[0] == 0.0)
         return SCIP_OKAY;
      *constant = estimator.template evaluate<0>(argvals[0], interval) - coeffs[0]*argvals[0];
   }
   SCIPdbgMsg( "argval=%.16g\n", argvals[0] );
   SCIPdbgMsg("cut is %.16g*x+%.16g\n", coeffs[0],*constant);
   SCIPdbgMsg("lookup at argval=%.16g\n", data->lookup->operator()(argvals[0]));
   SCIPdbgMsg("cut at argval=%.16g\n", *constant+coeffs[0]*argvals[0]);
   SCIPdbgMsg("bounds of arg = [%.16g,%.16g]\n", SCIPintervalGetInf(argbounds[0]), SCIPintervalGetSup(argbounds[0]));

   *success = true;
   return SCIP_OKAY;
}


SCIP_DECL_USEREXPREVAL( evaluateLookup )
{
   assert( nargs == 1 );
   // SCIPdbgMsg("evluating lookup at x=%.16g\n", *argvals);

   if( ! isfinite( *argvals ) )
   {
      *funcvalue = *argvals;
   }
   else
   {
      spline:: BSplineCurve<3, SCIP_Real>::interval_t interval = data->lookup->findInterval( *argvals );
      *funcvalue = data->lookup->template evaluate<0>( *argvals, interval );

      if( gradient )
         *gradient = data->lookup->template evaluate<1>( *argvals, interval );

      if( hessian )
         *hessian = data->lookup->template evaluate<2>( *argvals, interval );
   }

   return SCIP_OKAY;
}

SCIP_DECL_USEREXPRINTEVAL( intervalEvaluateLookup )
{
   assert( nargs == 1 );
   assert( hessian == NULL );
   SCIP_Real lb =  SCIPintervalGetInf( argvals[0] );
   SCIP_Real ub = SCIPintervalGetSup( argvals[0] );

   std::pair<SCIP_Real, SCIP_Real> minmax = data->lookup->findMinMaxVal(lb, ub, EPSILON);
   SCIPintervalSetBounds(funcvalue, minmax.first, minmax.second);
   SCIPdebugMessage("interval [%g, %g] evaluated to [%g, %g]\n", lb, ub, funcvalue->inf, funcvalue->sup);
   if( gradient )
   {
      minmax = spline::differentiate(*(data->lookup)).findMinMaxVal(lb, ub, EPSILON);
      SCIPintervalSetBounds(gradient, minmax.first, minmax.second);
      SCIPdebugMessage("gradient interval [%g, %g] evaluated to [%g, %g]\n", lb, ub, gradient->inf, gradient->sup);
   }

   /*
      if( hessian )
      {
         int left = data->lookupApx->secondDeriv.getPartition().findInterval( lb );
         int right = data->lookupApx->secondDeriv.getPartition().findInterval( ub, left++ ) + 1;
         SCIP_CALL( intervalEvaluation( data->lookupApx->secondDeriv, argvals, data->lookupApx->secondDeriv.getPartition().begin() + left, data->lookupApx->secondDeriv.getPartition().begin() + right, hessian ) );
      }
   */
   return SCIP_OKAY;
}

SCIP_DECL_USEREXPRCURV( checkLookupCurvature )
{
   assert( nargs == 1 );

   *result = SCIP_EXPRCURV_UNKNOWN;

   if(argcurv[0] == SCIP_EXPRCURV_UNKNOWN)
      return SCIP_OKAY;

   SCIP_Real lb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real ub = SCIPintervalGetSup( argbounds[0] );

   auto derivative2 = spline::differentiate<2>(*(data->lookup));

   SCIP_Real val = derivative2( lb );
   SCIP_EXPRCURV lookupExprCurv = SCIP_EXPRCURV_UNKNOWN;
   if(val >= 0.0)
      lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv | SCIP_EXPRCURV_CONVEX);
   if(val <= 0.0)
      lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv | SCIP_EXPRCURV_CONCAVE);

   std::vector<SCIP_Real> zeros = derivative2.getRealRoots( lb, ub, EPSILON );

   for(std::vector<SCIP_Real>::iterator iter = zeros.begin(); iter != zeros.end(); ++iter)
   {
      val = derivative2(*iter + EPSILON);
      if(val < 0.0) // no more convex
         lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv ^ (SCIP_EXPRCURV_CONVEX & lookupExprCurv));
      if(val > 0.0) // no more concave
         lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv ^ (SCIP_EXPRCURV_CONCAVE & lookupExprCurv));
      if(lookupExprCurv == SCIP_EXPRCURV_UNKNOWN)
         return SCIP_OKAY;
   }

   //if argument linear curvature of lookup is preserved
   if( *argcurv == SCIP_EXPRCURV_LINEAR )
   {
      *result = lookupExprCurv;
      return SCIP_OKAY;
   }

   //ifargument nonlinear but convex or concave we need to check whether the lookup is non-increasing or non-decreasing
   //in order to conclude that the whole expression is convex/concave

   auto derivative1 = spline::differentiate(*(data->lookup));
   val = derivative1( lb );
   bool increasing = val < 0.0;
   bool decreasing = val > 0.0;

   zeros = derivative1.getRealRoots(lb, ub, EPSILON);
   for( std::vector<SCIP_Real>::iterator iter = zeros.begin(); iter != zeros.end(); ++iter )
   {
      val = derivative1( *iter + EPSILON );
      decreasing = decreasing || (val < 0.0);
      increasing = increasing || (val > 0.0);
      if(increasing && decreasing)
         return SCIP_OKAY;
   }

   //composition rule for convex/concave functions
   if( lookupExprCurv & SCIP_EXPRCURV_CONVEX )
   {
      if(
         ( !decreasing && ( argcurv[0] == SCIP_EXPRCURV_CONVEX ) ) ||
         ( !increasing && ( argcurv[0] == SCIP_EXPRCURV_CONCAVE ) )
      )
         *result = SCIP_EXPRCURV( ( *result ) | SCIP_EXPRCURV_CONVEX );
   }

   if( lookupExprCurv & SCIP_EXPRCURV_CONCAVE )
   {
      if(
         ( !decreasing && ( argcurv[0] == SCIP_EXPRCURV_CONCAVE ) ) ||
         ( !increasing && ( argcurv[0] == SCIP_EXPRCURV_CONVEX ) )
      )
         *result = SCIP_EXPRCURV( ( *result ) | SCIP_EXPRCURV_CONCAVE );
   }

   return SCIP_OKAY;
}

SCIP_DECL_USEREXPRPROP( propagateLookup )
{
   assert( nargs == 1 );
   *cutoff = false;

   return SCIP_OKAY;

   SCIP_Real arglb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real argub = SCIPintervalGetSup( argbounds[0] );
   SCIP_Real funclb = SCIPintervalGetInf( funcbounds );
   SCIP_Real funcub = SCIPintervalGetSup( funcbounds );

   SCIPdebugMessage( "propagating lookup with bound [%g,%g] and argbounds [%g,%g]\n",
                     funclb, funcub, arglb, argub );
#if 0
   if( is_equal( funclb, funcub) )
   {
      SCIPdbgMsg( "Funcbounds equal\n" );
      SCIPdbgMsg( "argbounds before backwardprop [%.16g,%.16g]\n", arglb, argub );
      if(is_equal(arglb, argub))
      {
         if(! is_equal(data->lookup->operator()(arglb), funclb) )
            *cutoff = true;
         return SCIP_OKAY;
      }

      spline::SimplePolynomial<0, SCIP_Real> rhs;
      rhs.setCoeff(0, funclb);
      std::vector<SCIP_Real> solution = data->lookup->solveEquation( rhs, arglb, argub, EPSILON );

      if( solution.empty() )
      {
         *cutoff = true;
      }
      else
      {
         SCIPintervalSetBounds( argbounds, solution.front(), solution.back() );
      }

      SCIPdbgMsg( "argbounds after backwardprop [%.16g,%.16g]\n", arglb, argub );
      return SCIP_OKAY;
   }
#endif
   bool sols_empty = true;

   if( funclb > -infinity )
   {
      spline::SimplePolynomial<0, SCIP_Real> rhs;
      rhs.setCoeff(0, funclb-EPSILON);
      std::vector<SCIP_Real> solution = data->lookup->solveEquation( rhs, arglb, argub, EPSILON );
 
      if(!solution.empty())
      {
         sols_empty = false;
         auto derivative1 = spline::differentiate(*(data->lookup));

         SCIPInterval newargbounds;
         SCIPintervalSetEmpty( &newargbounds ); //start with empty interval

         for( std::vector<SCIP_Real>::iterator iter = solution.begin(); iter != solution.end(); ++iter )
         {
            SCIPdebugMessage( "found intersection with funcbound inf: %.16g\n", *iter );
            SCIPInterval currentInterval;
            SCIPintervalSetBounds(
               &currentInterval,
               iter == solution.begin() ? arglb : * ( iter - 1 ),
               iter + 1 == solution.end() ? argub : * ( iter + 1 )
            );
            SCIP_Real g = derivative1( *iter );

            if( g > 0.0 )
            {

               //first derivative is positive at the point where the lookup
               //has the value of the lower bound. Thus right of this point
               //it is above the lower bound and left it is below.
               SCIPdebugMessage( "deriv positive. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, *iter, currentInterval.sup );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdebugMessage( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( g < 0.0 )
            {
               SCIPdebugMessage( "deriv negative. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               //first derivative is negative and thus the valid
               //interval that is above the lower bound is to the left
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, currentInterval.inf, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdebugMessage( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( derivative1.template derivative<1>( *iter ) < 0.0 )
            {
               SCIPdebugMessage( "deriv zero at intersection and second deriv negative\n" );
               //first derivative is zero and second derivative negative
               //thus the lookup has a local maximum that equals the lower bound.
               //The valid interval may be reduced since the lookup is below the
               //lower bound in the interval between the extreme point and the
               //next solution value to the left and to the right where it may go below
               //its upper bound again.
               //so the valid interval in the current interval is only the extreme point


               SCIPInterval tmp;
               SCIPintervalSet( &tmp, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );

            }
            else
            {
               //in this case we have a local minimum ending in the lower bound
               //or the lookup is constant in the current interval with the
               //value equal to the upper bound and thus the whole current interval
               //is valid
               SCIPInterval tmp;
               SCIPintervalUnify( &newargbounds, newargbounds, currentInterval );
            }

            if( SCIPintervalIsSubsetEQ( infinity, argbounds[0], newargbounds ) )
               break;
         }

         //intersect the argbound interval with the valid interval
         SCIPintervalIntersect( argbounds, argbounds[0], newargbounds );

         if( SCIPintervalIsEmpty( infinity, argbounds[0] ) )
         {
            SCIPdebugMessage( "argbounds empty now -> cutoff\n" );
            *cutoff = true;
         }
      }
   }

   if( funcub < infinity )
   {
      spline::SimplePolynomial<0, SCIP_Real> rhs;
      rhs.setCoeff(0, funcub+EPSILON);

      std::vector<SCIP_Real> solution = data->lookup->solveEquation( rhs, arglb, argub, EPSILON );

      if(! solution.empty() )
      {
         auto derivative1 = spline::differentiate(*(data->lookup));
         sols_empty = false;
         SCIPInterval newargbounds;
         SCIPintervalSetEmpty( &newargbounds ); //start with empty interval

         for( std::vector<SCIP_Real>::iterator iter = solution.begin(); iter != solution.end(); ++iter )
         {
            SCIPdebugMessage( "found intersection with funcbound sup: %.16g\n", *iter );
            SCIPInterval currentInterval;
            SCIPintervalSetBounds(
               &currentInterval,
               iter == solution.begin() ? arglb : * ( iter - 1 ),
               iter + 1 == solution.end() ? argub : * ( iter + 1 )
            );
            SCIP_Real g = derivative1( *iter );

            if( g > 0.0 )
            {
               SCIPdebugMessage( "deriv positive. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               //first derivative is positive at the point where the lookup
               //has the value of the upper bound. Thus left of this point
               //it was below the upper bound and right it is above.
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, currentInterval.inf, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdebugMessage( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( g < 0.0 )
            {
               SCIPdebugMessage( "deriv negative. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               //first derivative is negative and thus the valid
               //interval that is below the upper bound is to the right
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, *iter, currentInterval.sup );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdebugMessage( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( derivative1.template derivative<1>( *iter ) > 0.0 )
            {
               SCIPdebugMessage( "deriv zero at intersection and second deriv positive\n" );
               //first derivative is zero and second derivative positive
               //thus the lookup has a local minimum that equals the upper bound.
               //The valid interval may be reduced since the lookup is above the
               //upper bound in the interval between the extreme point and the
               //next solution value to the left and to the right where it may go below
               //its upper bound again.
               //so the valid interval in the current interval is only the extreme point
               SCIPInterval tmp;
               SCIPintervalSet( &tmp, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdebugMessage( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );

            }
            else
            {
               //in this case we have a local maximum ending in the upper bound
               //or the lookup is constant in the current interval with the
               //value equal to the upper bound and thus the whole current interval
               //is valid
               SCIPInterval tmp;
               SCIPintervalUnify( &newargbounds, newargbounds, currentInterval );
            }

            if( SCIPintervalIsSubsetEQ( infinity, argbounds[0], newargbounds ) )
               return SCIP_OKAY;
         }

         //intersect the argbound interval with the valid interval
         SCIPintervalIntersect( argbounds, argbounds[0], newargbounds );

         if( SCIPintervalIsEmpty(infinity, argbounds[0] ) )
         {
            SCIPdebugMessage( "argbounds empty now -> cutoff\n" );
            *cutoff = true;
            return SCIP_OKAY;
         }
      }
   }

   SCIPdbgMsg( "argbounds after backwardprop [%.16g,%.16g]\n", argbounds->inf, argbounds->sup );
   if( sols_empty )
   {
      //if the solution is empty then the bounds either
      //can not be tightened or are infeasible
      SCIPInterval tmp;
      SCIP_Real p = pointInsideInterval( infinity, argbounds[0] );
      SCIPintervalSet( &tmp, data->lookup->operator()( p ) );
      SCIPdebugMessage( "test: f(%g) = %g\n", p, SCIPintervalGetInf( tmp ) );
      SCIPdebugMessage( "funcbounds: [%g,%g]\n", SCIPintervalGetInf( funcbounds ), SCIPintervalGetSup( funcbounds ) );

      //if the funcbounds do not contain the result of the evaluation at an arbitrary point
      //inside the argbounds the bounds are infeasible
      if( SCIPintervalAreDisjoint( tmp, funcbounds ) )
      {
         SCIPdebugMessage( "funcbounds dont contain lookup of value from argbounds -> cutoff\n" );
         *cutoff = true;
      }
   }

   return SCIP_OKAY;
}

SCIP_DECL_USEREXPRPRINT( lookupExprPrint)
{
   SCIPmessageFPrintInfo(messagehdlr, file, "smoothLoookup(");
}


SCIP_DECL_USEREXPRCOPYDATA( copyLookupExpr )
{
#if 1
   BMSallocBlockMemory( blkmem, datatarget );
   new( *datatarget ) SCIP_USEREXPRDATA( *datasource );
#else
   *datatarget = new SCIP_USEREXPRDATA( *datasource );
#endif
//  SCIPdbgMsg( "copied lookup expr data to address %p\n", ( void * ) *datatarget );
   return SCIP_OKAY;
}

SCIP_DECL_USEREXPRFREEDATA( freeLookupExpr )
{
   // SCIPdbgMsg( "freeing lookup expr data at address %p\n", ( void * )data );
#if 1
   data->~SCIP_USEREXPRDATA();
   BMSfreeBlockMemory( blkmem, &data );
#else
   delete data;
#endif
}


SCIP_RETCODE SCIPexprCreateLookup(
   BMS_BLKMEM*           blkmem,                 /**< block memory data structure */
   SCIP_EXPR**           expr,                   /**< pointer to buffer for expression address */
   SCIP_EXPR*            child,                  /**< child of lookup expression, i.e. argument to lookup */
   const shared_ptr< spline::BSplineCurve<3, SCIP_Real> > &spline /**< second derivate of piecewise cubic lookup */
)
{
   SCIP_USEREXPRDATA* data;
   BMSallocBlockMemory( blkmem, &data );

   new( data ) SCIP_USEREXPRDATA();
   data->lookup = spline;

   SCIP_CALL(
      SCIPexprCreateUser(
         blkmem,
         expr,
         1,
         &child,
         data,
         (SCIP_EXPRINTCAPABILITY_FUNCVALUE | SCIP_EXPRINTCAPABILITY_INTFUNCVALUE | SCIP_EXPRINTCAPABILITY_GRADIENT |
            SCIP_EXPRINTCAPABILITY_INTGRADIENT | SCIP_EXPRINTCAPABILITY_HESSIAN) ,
         evaluateLookup,
         intervalEvaluateLookup,
         checkLookupCurvature,
         propagateLookup,
         estimateLookup,
         copyLookupExpr,
         freeLookupExpr,
         lookupExprPrint
      )
   );

   return SCIP_OKAY;
}


void SCIPexprLookupSetEpsilon( SCIP_Real epsilon )
{
   EPSILON = epsilon;
}
