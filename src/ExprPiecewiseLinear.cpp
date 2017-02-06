/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 2012-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*    Copyright (C) 2016      Helmut-Schmidt University Hamburg              */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Lesser General Public License        */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.*/
/*                                                                           */
/*                                                                           */
/* Based on SCIP - Solving Constraint Integer Programs                       */
/* Copyright (C) 2002-2016 Zuse Institute Berlin                             */
/* SCIP is distributed under the terms of the SCIP Academic Licence,         */
/* see file COPYING in the SCIP distribution.                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    ExprPiecewiseLinear.cpp
 * @brief   User Expression for univariate piecewise linear functions
 * @author  Robert L. Gottwald
 * @author  Ingmar Vierhaus
 *
 */

/* Workaround: Feastol is not included in estimator callback */
#define SCIP_FEASTOL 1e-6

#define EXPR_PCW_LIN_TEST_ESTIMATIONS

#include "ExprPiecewiseLinear.h"
#include <nlpi/type_expr.h>
#include <nlpi/pub_expr.h>
#include <nlpi/intervalarithext.h>
#include <blockmemshell/memory.h>
#include <spline/BSplineCurve.hpp>
#include <spline/SimplePolynomial.hpp>
#include <cmath>
#include <scip/intervalarith.h>
#include <scip/pub_message.h>
#include <scip/cons_nonlinear.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <boost/lexical_cast.hpp>

using boost::shared_ptr;
using std::isfinite;

static SCIP_Real EPSILON = 1e-9;

inline static
bool is_equal( SCIP_Real a, SCIP_Real b )
{
   return EPSEQ(a, b, EPSILON);
}

SAFE_ESTIMATOR selectEstimator(SCIP_Bool overestimate, SCIP_Real lb, SCIP_Real ub, SCIP_Real argval, SCIP_Real x1, SCIP_Real x2, SCIP_Bool e5valid, SCIP_Bool e6valid)
{
   /* If only one class2 estimator is available, we use it */
   if ((e5valid || e6valid) & !(e5valid && e6valid) )
      return (e5valid ? SAFE_ESTIMATOR_TYPE_5 : SAFE_ESTIMATOR_TYPE_6);

   /* If we get here, e5valid = e6valid (both or none) */

   /* Pick the estimator by distinguishing between signs of lb and ub */
   if( lb >= 0)
   {
      if (ub >= 0)
      {
         /* lb >=0, ub >= 0 */
         if (e6valid)
            return SAFE_ESTIMATOR_TYPE_6;
         else
            return SAFE_ESTIMATOR_TYPE_4;
      }
      else
      {
         /* else lb >=0, ub < 0
          * this should not happen but the return avoids compiler warning */
         return SAFE_ESTIMATOR_TYPE_1;
      }
   }
   else
   {
      if (ub >= 0)
      {
         /* lb < 0, ub >= 0 */
         if( ub + lb  >= argval)
         {
            if( e6valid)
               return SAFE_ESTIMATOR_TYPE_6;
            else
               return SAFE_ESTIMATOR_TYPE_3;
         }
         else
         {
            if( e5valid)
               return SAFE_ESTIMATOR_TYPE_5;
            else
               return SAFE_ESTIMATOR_TYPE_1;
         }
      }
      else
      {
         /* lb < 0, ub < 0 */
         if (e5valid)
            return SAFE_ESTIMATOR_TYPE_5;
         else
            return SAFE_ESTIMATOR_TYPE_2;
      }
   }
}

SCIP_RETCODE setRoundingModeFromBool(SCIP_Bool mup)
{
   if (mup)
      SCIPintervalSetRoundingModeUpwards();
   else
      SCIPintervalSetRoundingModeDownwards();

   /*if (mup)
   {
      SCIPdbgMsg("Set rounding mode up\n");
   }
   else
   {
      SCIPdbgMsg("Set rounding mode down\n");
   }*/

   return SCIP_OKAY;
}

/** Computes the closest upwards (downwards) rounded representation of y - x*m
 *  when mup is true (false)
 */
#if 0
   if( mup)
   {
      if (std::signbit(m*x))
      {
         /* Round up for positive m*x */
         roundup = true;


      }
      else
      {
         /* Round up for negative m*x */
         roundup = false;

      }
   }
   else
   {
      if (std::signbit(m*x))
      {
         /* Round down for positive m*x */
         roundup = true;
      }
      else
      {
         /* Round down for negative m*x */
         roundup = false;
      }
   }
#endif


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

   )
{
   assert(x2 - x1 >= 1e-9);

   SCIPdebugMessage("%sestimating safe: (lb,ub) = (%f,%f)\n",
      (overestimate ? "over" : "under"), lb, ub);
   //SCIPdebugMessage("(x1,y1 = (%1.17e,%1.17e), (x2,y2) = (%1.17e,%1.17e), argval = %f, type: %i\n",
   SCIPdebugMessage("(x1,y1 = (%f,%f), (x2,y2) = (%f,%f), argval = %f, type: %i\n",
      x1, y1, x2, y2, argval, estimator);

   const SCIP_Interval y1i = {y1, y1};
   const SCIP_Interval y2i = {y2, y2};
   const SCIP_Interval x1i = {x1, x1};
   const SCIP_Interval x2i = {x2, x2};
   SCIP_Interval coefficienti = (y2i - y1i) / (x2i - x1i);
   SCIPdbgMsg("coefficienti = [%f, %f]\n", coefficienti.inf, coefficienti.sup);
   SCIP_ROUNDMODE oldmode = SCIPintervalGetRoundingMode();
   SCIP_Real merr = coefficienti.sup - coefficienti.inf;

   /* Decide how to round the slope */
   SCIP_Bool mup = true; /* If true, round the slope upwards, else round downwards */
   switch (estimator)
   {
      case SAFE_ESTIMATOR_TYPE_1:
      case SAFE_ESTIMATOR_TYPE_2:
      case SAFE_ESTIMATOR_TYPE_5:
         if( overestimate )
            mup = false;
         else
            mup = true;
         break;
      case SAFE_ESTIMATOR_TYPE_3:
      case SAFE_ESTIMATOR_TYPE_4:
      case SAFE_ESTIMATOR_TYPE_6:
         if( overestimate )
            mup = true;
         else
            mup = false;
         break;
   }

   /* Set slope (m) */
   *coefficient = mup ? coefficienti.sup : coefficienti.inf;

   /* Compute the intercept */
   SCIP_Interval intercepti = y1i - coefficienti*x1i;
   switch (estimator)
   {
      case SAFE_ESTIMATOR_TYPE_1:
      case SAFE_ESTIMATOR_TYPE_3:
         if (overestimate)
            SCIPintervalSetRoundingModeUpwards();
         else
            SCIPintervalSetRoundingModeDownwards();

         if( overestimate && estimator == SAFE_ESTIMATOR_TYPE_1)
            *intercept = intercepti.sup + merr*ub;
         else if (overestimate && estimator == SAFE_ESTIMATOR_TYPE_3)
            *intercept = intercepti.sup - merr*lb;
         else if (!overestimate && estimator == SAFE_ESTIMATOR_TYPE_1)
            *intercept = intercepti.inf- merr*ub;
         else if (!overestimate && estimator == SAFE_ESTIMATOR_TYPE_3)
            *intercept = intercepti.inf + merr*lb;
         break;
      case SAFE_ESTIMATOR_TYPE_2:
         intercepti = y2i - coefficienti*x2i;
         *intercept = overestimate ? intercepti.sup : intercepti.inf;
         break;
      case SAFE_ESTIMATOR_TYPE_4:
         *intercept = overestimate ? intercepti.sup : intercepti.inf;
         break;
      case SAFE_ESTIMATOR_TYPE_5:
            intercepti = y2i - coefficienti*x2i;
            *intercept = overestimate ? intercepti.sup : intercepti.inf;
            break;
      case SAFE_ESTIMATOR_TYPE_6:
         /* Compute intercept for E5 (E6) from x1 (x2) and y1 (y2) */
           *intercept = overestimate ? intercepti.sup : intercepti.inf;
         break;
   }

   SCIPdebugMessage("Computed safe estimation: y = %f x %+f\n", *coefficient, *intercept);

#ifdef EXPR_PCW_LIN_TEST_ESTIMATIONS
   /* Reset rounding mode for evaluation*/
   SCIPintervalSetRoundingModeToNearest();

   SCIPdbgMsg("Checking estimation at defining points\n");
   SCIP_Interval mi = {*coefficient, *coefficient};
   SCIP_Interval bi = {*intercept, *intercept};
   SCIP_Interval myy1 = mi *x1i + bi;
   SCIP_Interval myy2 = mi * x2i + bi;

   if (overestimate)
   {
      assert( myy1.sup >= y1  );
      assert( myy2.sup >= y2  );
   }
   else
   {
      assert( myy1.inf <= y1  );
      assert( myy2.inf <= y2  );
   }
   SCIPdbgMsg("estimation valid at (x1,y1) and (x2,y2) within in rounding error of evaluation \n");

   if (!(     (overestimate && ( myy2.sup >= y2  ) && ( myy1.sup >= y1  ))
          ||  (!overestimate && ( myy2.inf <= y2  ) && ( myy1.inf <= y1  ))
         ))
   {
      SCIPerrorMessage("Invalid estimation!\n");
   }
#endif

   /* Reset rounding mode */
   SCIPintervalSetRoundingMode(oldmode);

   return SCIP_OKAY;
}

struct SCIP_UserExprData
{
   shared_ptr< spline::BSplineCurve<1, SCIP_Real> > lookup;
   char identifier[10];
};

enum Side
{
   UPPER   ,
   LOWER
};


/**
 * Computes determinant to check whether the point C is left/right/on the
 * line segment that starts in A and goes to B denoted by AB.
 * The result is:
 *  < 0    if C is right of AB
 *  = 0    if C lies on AB
 *  > 0    if C is left of AB
 */
inline static
SCIP_Real determinant(
   std::pair<SCIP_Real, SCIP_Real>& A, /**< Point A */
   std::pair<SCIP_Real, SCIP_Real>& B, /**< Point B */
   std::pair<SCIP_Real, SCIP_Real>& C  /**< Point C */
)
{
   SCIPdbgMsg("Computing determinante of points (%f,%f), (%f,%f), (%f,%f) = %f\n", A.first, A.second, B.first, B.second, C.first, C.second,
      ( B.first - A.first )  * ( C.second - A.second ) - ( C.first - A.first ) * ( B.second - A.second ));

   return ( B.first - A.first )  * ( C.second - A.second ) - ( C.first - A.first ) * ( B.second - A.second );
}

/**
 * Checks for the last three points of a convex set of points if the second to last point has to be removed
 * for convexity. If yes it removes it and repeats the check.
 * The template parameter is used to check convexity from top and from below.
 */
template<Side side>
static
void grahamScanCheck(
   std::vector<std::pair<SCIP_Real, SCIP_Real> >& convexHull /**< The current convex hull appended by one additional point */
)
{
   bool check = true;

   while( check && convexHull.size() > 2 )
   {
      //determine left/right turn by determinant
      SCIP_Real T = determinant( convexHull[convexHull.size() - 3], convexHull[convexHull.size() - 2], convexHull.back() );

      if( ( side == UPPER && T >= 0.0 ) || ( side == LOWER && T <= 0.0 ) )
      {
         SCIPdbgMsg("erasing point (%f, %f)\n", (convexHull.end()-2)->first, (convexHull.end()-2)->second);
         convexHull.erase( convexHull.end() - 2 );
      }
      else
      {
         check = false;
      }
   }
}

/**
 * Computes the convex upper/lower hull on the given linear model with the given
 * bounds of its argument. The given output vector's contents are swapped with
 * the computed convex hull and thus previous contents will be deleted.
 */
template<Side side>
static std::vector<std::pair<SCIP_Real, SCIP_Real> > computeConvexHull(
   SCIP_Real infinity,                                          /**< value of infinity */
   SCIP_INTERVAL argBounds,                                     /**< bounds of lookup argument */
   const spline::BSplineCurve<1, SCIP_Real>& linear             /**< Piecewise linear function that is approximated by this expression */
)
{
   SCIP_Real lb = SCIPintervalGetInf( argBounds );
   SCIP_Real ub = SCIPintervalGetSup( argBounds );
   
   assert( lb > -infinity );
   assert( ub < infinity );

   auto begin = linear.findInterval( lb );
   auto end = linear.findInterval( ub, begin );

   std::vector<std::pair<SCIP_Real, SCIP_Real> > convexHull;
   convexHull.push_back( std::make_pair( lb, linear(lb) ) );
   SCIPdbgMsg( "bounds are [%g,%g]\n", lb, ub );
   SCIPdbgMsg( "intervals for bounds are %li and %li\n", begin, end );
   SCIPdbgMsg( "intervals for upper bound is [%f, %f]\n", linear.getInfimum(end), linear.getSupremum(end));

   if( begin < end )
   {
      SCIPdbgMsg( "pushing into convex  hull: (%f, %f)\n",linear.getSupremum(begin), linear( linear.getSupremum(begin)));
      convexHull.push_back( std::make_pair( linear.getSupremum(begin), linear( linear.getSupremum(begin) ) ) );
   }

   SCIPdbgMsg( "Starting computation of convex hull with %li points (%g,%g) (%g,%g)\n", convexHull.size(), convexHull.front().first, convexHull.front().second, convexHull.back().first, convexHull.back().second );

   for( auto i = begin + 2; i <= end; ++i )
   {
      SCIPdbgMsg("considering interval %li\n",i);
      SCIPdbgMsg( "pushing into convex  hull: (%f, %f)\n",linear.getInfimum(i), linear( linear.getInfimum(i)));
      convexHull.push_back( std::make_pair( linear.getInfimum(i), linear( linear.getInfimum(i)) ) );
      grahamScanCheck<side> ( convexHull );
      std::ostringstream oss;
      for( auto point : convexHull)
      {
            oss << "(" << std::to_string(point.first) << "," << std::to_string(point.second) << ")";
      }
      SCIPdbgMsg("convex hull is %s\n", oss.str().c_str());
   }

   SCIPdbgMsg("last x val in hull is %1.16e\n", convexHull.back().first);
   /*
    * If ub and last point in hull are equal:
    *   exchange last point by point at ub to avoid coinciding points but still
    *   ensure that argval stays strictly in x range of hull
    *   no grahamcheck is needed because last point is already checked
    * else
    *   add ub and scan one last time
    * */
   if (is_equal(convexHull.back().first, ub))
   {
      convexHull.pop_back();
      convexHull.push_back( std::make_pair( ub, linear( ub ) ) );
   }
   else
   {
      convexHull.push_back( std::make_pair( ub, linear( ub ) ) );
      SCIPdbgMsg("evaluating pcwlin at %1.17e = %1.17e\n", ub, linear(ub));
      SCIPdbgMsg( "pushing into convex  hull: (%f, %f)\n",ub, linear( ub ));
      grahamScanCheck<side> ( convexHull );
   }

   SCIPdbgMsg( "Convex hull from inner points is:\n" );

   for( unsigned int i = 0; i < convexHull.size(); ++i )
   {
      SCIPdbgMsg( "(%1.17e,%1.17e)\n", convexHull[i].first, convexHull[i].second );
   }

   return convexHull;
}

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


/**
 * Returns the minimum and maximum values, the lookup takes within the given interval
 * Also returns the corresponding arguments
  */
static SCIP_RETCODE findMinMaxPiecewiseLinear(
   const spline::BSplineCurve<1, SCIP_Real>& linear,
   const SCIP_INTERVAL* bounds,
   SCIP_Real &argmin,
   SCIP_Real &argmax,
   SCIP_Real &min,
   SCIP_Real &max
   )
{
   argmin = SCIPintervalGetInf( *bounds );
   argmax = SCIPintervalGetSup( *bounds );
   min = linear( argmin );
   max = linear( argmax );

   if( min > max )
   {
      std::swap( min, max );
      std::swap( argmin, argmax );
   }

   auto end = linear.findInterval(SCIPintervalGetSup( *bounds ));
   for( auto i = linear.findInterval(SCIPintervalGetInf( *bounds ))+1; i < end; ++i )
   {
      SCIP_Real val = linear.evaluate<0>( linear.getInfimum(i), i );

      if( val < min )
      {
         min = val;
         argmin = linear.getInfimum(i);
      }
      else if( val > max )
      {
         max = val;
         argmax = linear.getInfimum(i);
      }
   }

   return SCIP_OKAY;
   
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

static SCIP_DECL_USEREXPRPARSE( parseLookup )
{

   std::string dataString(str, length);
   std::vector<double> xvals;
   std::vector<double> yvals;

   SCIPdebugMessage("parsing \"%s\"\n", dataString.c_str());

   std::vector<std::string> pointStrings = split(dataString, ':');

   for (auto it : pointStrings)
   {
      std::string point = it;

      /* Remove paranthesis */
      point.erase(0,1).pop_back();
      std::vector<std::string> vals = split(point, ',');
      xvals.push_back(boost::lexical_cast<double>(vals[0]));
      yvals.push_back(boost::lexical_cast<double>(vals[1]));
   }
   SCIPdebugMessage("xvec: %s\n",sdscip::Vector::vec2string(xvals, std::string()).c_str());
   SCIPdebugMessage("yvec: %s\n",sdscip::Vector::vec2string(yvals, std::string()).c_str());

   auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(xvals, yvals);

   SCIP_CALL( SCIPexprCreatePiecewiseLinear( blkmem, expr, arg, pcwlin , identifier) );
   return SCIP_OKAY;

}


SCIP_RETCODE SCIPincludeUserExprParserPiecewiseLinear(SCIP* scip)
{
   SCIPincludeUserExprParser(scip, "lookup", "", parseLookup);
   return SCIP_OKAY;
}


static SCIP_DECL_USEREXPRESTIMATE( estimateLookup )
{
   assert( nargs == 1 );
   assert(argvals[0] + SCIP_FEASTOL >= SCIPintervalGetInf(argbounds[0]));
   assert(argvals[0] - SCIP_FEASTOL <= SCIPintervalGetSup(argbounds[0]));

   /* Bounds on the x-axis */
   SCIP_Real lb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real ub = SCIPintervalGetSup( argbounds[0] );

   *success = false;

   /* Argument values at maximum and minimum reached in interval */
   SCIP_Real argmin;
   SCIP_Real argmax;

   /* Minimum and maximum values of the function on the interval */
   SCIP_Real min;
   SCIP_Real max;

   /* If argval is within feastol smaller than lower argbound (because of feastol), move lower argbound to argval */
   if ( !(argvals[0] >= SCIPintervalGetInf(argbounds[0])) )
      lb = argvals[0];

   /* If argval is greater than upper argbound (because of feastol), move upper argbound to argval */
   if( !(argvals[0] <= SCIPintervalGetSup(argbounds[0])) )
      ub = argvals[0];
   
   SCIP_Interval newargbounds = {lb, ub};

   SCIP_CALL( findMinMaxPiecewiseLinear(*(data->lookup), &newargbounds, argmin, argmax, min, max) );


#if 0
/* Ingmar -> Robert: This seems to be invalid */
   if(lb <= -infinity)
   {
      if(ub >= infinity)
         return SCIP_OKAY;

      SCIP_Real val = overestimate ? argmin : argmax;

      if(argvals[0] <= val || val <= -infinity)
      {
         /* We can not compute an estimator that is valid below -infinity */
         return SCIP_OKAY;
      }
      /* We can move lb to the right to make estimation finite */
      lb = val;
   }
   else if(ub >= infinity)
   {
      SCIP_Real val = overestimate ? argmax : argmin;

      if(argvals[0] >= val || val >= infinity)
      {
         /* We can not compute an estimator that is valid above infinity */
         return SCIP_OKAY;
      }
      /* We can move ub to the left to make estimation finite */
      ub = val;
   }
#endif
   if (lb <= -infinity || ub >= infinity)
      return SCIP_OKAY;

   SCIPdebugMessage("%sestimating lookup %s with bounds [%g,%g], argval = %g\n", overestimate ? "over" : "under" , data->identifier, lb, ub, argvals[0]);

   if( is_equal( lb, ub ) )
   {
      /* Trivial case */
      SCIPdebugMessage("handling trivial case lb: %1.16e, ub %1.16e, delta: %1.16e", lb, ub, ub - lb);
      coeffs[0] = 0.0;
      *constant = overestimate ? max : min;
   }
   else
   {
      SCIP_Bool e5valid = FALSE; /* ub class2-estimator available? */
      SCIP_Bool e6valid = FALSE;/* lb class2-estimator available? */
      std::vector<std::pair<SCIP_Real, SCIP_Real>> cvxhull;

      if(overestimate)
         cvxhull = computeConvexHull<UPPER>(infinity, newargbounds, *(data->lookup));
      else
         cvxhull = computeConvexHull<LOWER>(infinity, newargbounds, *(data->lookup));

      assert(!cvxhull.empty());

      /* Loop over segments of convex hull to identify the segment that defines the estimator */
      for( auto it = cvxhull.begin(); it != cvxhull.end()-1; ++it)
      {
         SCIPdbgMsg("considering interval: (%f, %f) -> (%f, %f)\n", it->first, it->second, (it+1)->first, (it+1)->second);

         SCIP_Real x1 = it->first;
         SCIP_Real x2 = (it+1)->first;
         if( argvals[0] >= x1 && argvals[0] <= x2 ) /* Estimator is a secant to knots of this interval */
         {
            SCIP_Real y1 = it->second;
            SCIP_Real y2 = (it+1)->second;
            /* Check availability of class-2 estimators ( $\underline x = x1 or \bar x = x2$) */
            if (is_equal(x2, lb))
            {
               e5valid = TRUE;
               SCIPdbgMsg("(x2,y1) = (%e,%e), ub = %e, e5 available\n", x2, y2, ub);
            }

            if (is_equal(x1, lb))
            {
               e6valid = TRUE;
               SCIPdbgMsg("(x1,y1) = (%e,%e), lb = %e, e6 available\n", x1, y1, lb);
            }

            SAFE_ESTIMATOR estimator = selectEstimator(overestimate, lb, ub, argvals[0], x1, x2, e5valid, e6valid);
            SCIPdbgMsg("selected safe linear estimator %i\n", estimator);
            SCIP_CALL( estimateSafe(overestimate, lb, ub, argvals[0], x1, x2, y1, y2, estimator, coeffs, constant) );

            /* Check if we need a safeguard due to numerics */
            //SCIP_Real actualy1 = x1 * coeffs[0] + *constant;
            //SCIP_Real actualy2 = x2 * coeffs[0] + *constant;
            //SCIP_Real safeguard;
            //if (overestimate)
               //safeguard = MAX( );

            break;
         }
      }
   }
   /*
   SCIPdbgMsg( "argval=%.16g\n", argvals[0] );
   SCIPdbgMsg("cut is %.16g*x+%.16g\n", coeffs[0],*constant);
   SCIPdbgMsg("lookup at argval=%.16g\n", data->lookup->operator()(argvals[0]));
   SCIPdbgMsg("cut at argval=%.16g\n", *constant+coeffs[0]*argvals[0]);
   SCIPdbgMsg("bounds of arg = [%.16g,%.16g]\n", SCIPintervalGetInf(argbounds[0]), SCIPintervalGetSup(argbounds[0]));
   */

   /* Use TestExprPiecewiseLinear to check the estimation by sampling the interval */
#ifdef EXPR_PCW_LIN_TEST_ESTIMATIONS
   SCIPdbgMsg("Verifying computed estimation\n");
   EstimationData estimation;
   estimation.coefficient = coeffs[0];
   estimation.constant = *constant;
   estimation.overestimate = overestimate;
   int nerrors(0);
   if ( !TestExprPiecewiseLinear::sampleEstimationAtKnots(data->lookup, estimation, std::make_pair(lb, ub), nerrors, 1e-13))
   {
      SCIPdbgMsg("Invalid estimation:\n");
      SCIPdbgMsg("Estimation: %1.17e * x + %1.17e\n", coeffs[0], *constant);

      /* Print lookup points */
      auto coeffs = data->lookup->getCoefficients();
      std::ostringstream oss;

      for (auto it = coeffs.begin(); it < coeffs.end(); ++it) {
         int i = it - coeffs.begin();
         if (i  >= 1)
            oss << ", ";
         oss << std::string("(") << std::to_string(data->lookup->getKnot(i)) << std::string(", ") << std::to_string(*it) << std::string(")");
      }
      SCIPdbgMsg("Points: %s\n", oss.str().c_str());
      SCIPdbgMsg("original argbounds: [%1.17e, %1.17e]\n",SCIPintervalGetInf( argbounds[0] ), SCIPintervalGetSup( argbounds[0] ));
      SCIPdbgMsg("lb/ub: [%1.17e, %1.17e]\n",lb, ub);
      SCIPdbgMsg("argval: %1.17e\n", argvals[0]);

      assert(false);
   }

#endif

   *success = true;
   return SCIP_OKAY;
}


static SCIP_DECL_USEREXPREVAL( evaluateLookup )
{
   assert( nargs == 1 );
   assert(!hessian);
   // SCIPdbgMsg("evluating lookup at x=%.16g\n", *argvals);

   if( ! isfinite( *argvals ) )
   {
      *funcvalue = *argvals;
   }
   else
   {
      spline::BSplineCurve<1, SCIP_Real>::interval_t interval = data->lookup->findInterval( *argvals );
      *funcvalue = data->lookup->template evaluate<0>( *argvals, interval );

      if( gradient )
         *gradient = data->lookup->template evaluate<1>( *argvals, interval );

   }

   /*if (*funcvalue > 0.865188826328 && *funcvalue < 0.86518882633)
   {
      SCIPdbgMsg("this might be it\n");
   }*/


   return SCIP_OKAY;
}

static SCIP_DECL_USEREXPRINTEVAL( intervalEvaluateLookup )
{
   assert( nargs == 1 );
   assert( hessian == NULL );
   SCIP_Real argmin;
   SCIP_Real argmax;
   SCIP_Real min;
   SCIP_Real max;
   auto& linear = *(data->lookup);
   SCIP_CALL( findMinMaxPiecewiseLinear(linear, argvals, argmin, argmax, min, max) );
   SCIPintervalSetBounds(funcvalue, min, max);
   SCIPdbgMsg("interval [%g, %g] evaluated to [%g, %g]\n", SCIPintervalGetInf(argvals[0]), SCIPintervalGetSup(argvals[0]), funcvalue->inf, funcvalue->sup);
   if( gradient )
   {

      SCIP_Real gmin = linear.derivative( argmin );
      SCIP_Real gmax = linear.derivative( argmax );

      if( gmin > gmax )
      {
         std::swap( gmin, gmax );
      }

      auto end = linear.findInterval(SCIPintervalGetSup( argvals[0] ));
      for( auto i = linear.findInterval(SCIPintervalGetInf( argvals[0] ))+1; i < end; ++i )
      {
         SCIP_Real val = linear.evaluate<1>( linear.getInfimum(i), i );

         if( val < gmin )
         {
            gmin = val;
         }
         else if( val > gmax )
         {
            gmax = val;
         }
      }
      SCIPintervalSetBounds(gradient, gmin, gmax);
   }

   return SCIP_OKAY;
}

static SCIP_DECL_USEREXPRCURV( checkLookupCurvature )
{
   assert( nargs == 1 );
   *result = SCIP_EXPRCURV_UNKNOWN;
   if(argcurv[0] == SCIP_EXPRCURV_UNKNOWN)
      return SCIP_OKAY;
   SCIP_Real lb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real ub = SCIPintervalGetSup( argbounds[0] );
   auto l = data->lookup->findInterval(lb);
   auto r = data->lookup->findInterval(ub);
   SCIP_EXPRCURV lookupExprCurv = SCIP_EXPRCURV_LINEAR;

   if( l < r )
   {
      std::pair<SCIP_Real,SCIP_Real> point1;
      std::pair<SCIP_Real,SCIP_Real> point2;
      std::pair<SCIP_Real,SCIP_Real> point3;
      point1.first = data->lookup->getInfimum(l);
      point1.second = (*data->lookup)(point1.first);
      point2.first = data->lookup->getSupremum(l);
      point2.second = (*data->lookup)(point2.first);

      auto p1 = &point1;
      auto p2 = &point2;
      auto p3 = &point3;
      do {
         p3->first = data->lookup->getSupremum(++l);
         p3->second = (*data->lookup)(p3->first);

         SCIP_Real det = determinant(*p1, *p2, *p3);
         if( det < 0.0 )  // no more convex
            lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv ^ (SCIP_EXPRCURV_CONVEX & lookupExprCurv));
         if( det > 0.0 )  // no more concave
            lookupExprCurv = SCIP_EXPRCURV(lookupExprCurv ^ (SCIP_EXPRCURV_CONCAVE & lookupExprCurv));
         if(lookupExprCurv == SCIP_EXPRCURV_UNKNOWN)
            return SCIP_OKAY;

         auto tmp = p1;
         p1 = p2;
         p2 = p3;
         p3 = tmp;

      } while(l < r);
   }

   //if argument linear curvature of lookup is preserved
   if( *argcurv == SCIP_EXPRCURV_LINEAR )
   {
      *result = lookupExprCurv;
      return SCIP_OKAY;
   }

   //ifargument nonlinear but convex or concave we need to check whether the lookup is non-increasing or non-decreasing
   //in order to conclude that the whole expression is convex/concave

   SCIP_Real val = data->lookup->derivative( lb );
   bool increasing = val < 0.0;
   bool decreasing = val > 0.0;

   for( l = data->lookup->findInterval(lb); l <= r; ++l )
   {
      val = data->lookup->derivative( data->lookup->getSupremum(l) );
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

static SCIP_DECL_USEREXPRPROP( propagateLookup )
{
   assert( nargs == 1 );
   *cutoff = false;

   SCIP_Real arglb = SCIPintervalGetInf( argbounds[0] );
   SCIP_Real argub = SCIPintervalGetSup( argbounds[0] );
   SCIP_Real funclb = SCIPintervalGetInf( funcbounds );
   SCIP_Real funcub = SCIPintervalGetSup( funcbounds );

   SCIPdebugMessage( "propagating lookup %s with bound [%g,%g] and argbounds [%g,%g]\n", data->identifier,
                     funclb, funcub, arglb, argub );

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
            SCIPdbgMsg( "found intersection with funcbound inf: %.16g\n", *iter );
            SCIPInterval currentInterval;
            SCIPintervalSetBounds(
               &currentInterval,
               iter == solution.begin() ? arglb : * ( iter - 1 ),
               iter + 1 == solution.end() ? argub : * ( iter + 1 )
            );
            SCIP_Real gleft = derivative1( (*iter)-EPSILON );
            SCIP_Real gright = derivative1( (*iter)+EPSILON );

            if( gleft > 0.0 && gright > 0.0 )
            {

               //first derivative is positive at the point where the lookup
               //has the value of the lower bound. Thus right of this point
               //it is above the lower bound and left it is below.
               SCIPdbgMsg( "deriv positive. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, *iter, currentInterval.sup );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdbgMsg( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( gleft < 0.0 && gright < 0.0 )
            {
               SCIPdbgMsg( "deriv negative. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               //first derivative is negative and thus the valid
               //interval that is above the lower bound is to the left
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, currentInterval.inf, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdbgMsg( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( gleft > 0.0 && gright < 0.0 )
            {
               SCIPdbgMsg( "deriv zero at intersection and second deriv negative\n" );
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
            SCIPdbgMsg( "argbounds empty now -> cutoff\n" );
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
            SCIPdbgMsg( "found intersection with funcbound sup: %.16g\n", *iter );
            SCIPInterval currentInterval;
            SCIPintervalSetBounds(
               &currentInterval,
               iter == solution.begin() ? arglb : * ( iter - 1 ),
               iter + 1 == solution.end() ? argub : * ( iter + 1 )
            );
            SCIP_Real gleft = derivative1( (*iter)-EPSILON );
            SCIP_Real gright = derivative1( (*iter)+EPSILON );

            if( gleft > 0.0 && gright > 0.0 )
            {
               SCIPdbgMsg( "deriv positive. updated valid interval to  [%.16g,%.16g] \n", newargbounds.inf, newargbounds.sup );
               //first derivative is positive at the point where the lookup
               //has the value of the upper bound. Thus left of this point
               //it was below the upper bound and right it is above.
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, currentInterval.inf, *iter );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdbgMsg( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( gleft < 0.0 && gright < 0.0 )
            {
               SCIPdbgMsg( "deriv negative. updated valid interval [%.16g,%.16g] to ", newargbounds.inf, newargbounds.sup );
               //first derivative is negative and thus the valid
               //interval that is below the upper bound is to the right
               SCIPInterval tmp;
               SCIPintervalSetBounds( &tmp, *iter, currentInterval.sup );
               SCIPintervalUnify( &newargbounds, newargbounds, tmp );
               SCIPdbgMsg( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );
            }
            else if( gleft < 0.0 && gright > 0.0 )
            {
               SCIPdbgMsg( "deriv zero at intersection and second deriv positive\n" );
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
               SCIPdbgMsg( "[%.16g,%.16g]\n", newargbounds.inf, newargbounds.sup );

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
            SCIPdbgMsg( "argbounds empty now -> cutoff\n" );
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
      /* Be sure before returning cutoff (SCIPintervalAreDisjoint has no tolerance) */
      tmp.inf = tmp.inf - EPSILON;
      tmp.sup = tmp.sup + EPSILON;
      SCIPdbgMsg( "test: f(%g) = %g\n", p, SCIPintervalGetInf( tmp ) );
      SCIPdbgMsg( "funcbounds: [%g,%g]\n", SCIPintervalGetInf( funcbounds ), SCIPintervalGetSup( funcbounds ) );

      //if the funcbounds do not contain the result of the evaluation at an arbitrary point
      //inside the argbounds the bounds are infeasible
      if( SCIPintervalAreDisjoint( tmp, funcbounds ) )
      {
         if( !(funclb + EPSILON < funcub) )
         {
            SCIPdebugMessage("Returning cutoff after propagating degenerate interval when propagating\n"
               "propagating lookup %s with bound [%1.16e,%1.16e] and argbounds [%1.16e,%1.16e]\n",
               data->identifier, funclb, funcub, arglb, argub );
         }
         SCIPdbgMsg( "funcbounds dont contain lookup of value from argbounds -> cutoff\n" );
         *cutoff = true;
      }
   }

   return SCIP_OKAY;
}



static SCIP_DECL_USEREXPRCOPYDATA( copyLookupExpr )
{
#if 1
   BMSallocBlockMemory( blkmem, datatarget );
   new( *datatarget ) SCIP_USEREXPRDATA( *datasource );
#else
   *datatarget = new SCIP_USEREXPRDATA( *datasource );
#endif
   strncpy((*datatarget)->identifier, datasource->identifier, sizeof(datasource->identifier));

  return SCIP_OKAY;
}

static SCIP_DECL_USEREXPRFREEDATA( freeLookupExpr )
{
   // SCIPdbgMsg( "freeing lookup expr data at address %p\n", ( void * )data );
#if 1
   data->~SCIP_USEREXPRDATA();
   BMSfreeBlockMemory( blkmem, &data );
#else
   delete data;
#endif
}

static SCIP_DECL_USEREXPRPRINT( lookupExprPrint)
{

   /* Print user expression identifier */
   SCIPmessageFPrintInfo(messagehdlr, file, "[lookup]");

   /* Print identifier */
   SCIPmessageFPrintInfo(messagehdlr, file, "[%s]", data->identifier);

   /* Print points */
   SCIPmessageFPrintInfo(messagehdlr, file, "[");
   SCIPexprPiecewiseLinearPrintPoints(data, messagehdlr, file);
   SCIPmessageFPrintInfo(messagehdlr, file, "]");

}

SCIP_RETCODE SCIPexprCreatePiecewiseLinear(
   BMS_BLKMEM*           blkmem,                 /**< block memory data structure */
   SCIP_EXPR**           expr,                   /**< pointer to buffer for expression address */
   SCIP_EXPR*            child,                  /**< child of lookup expression, i.e. argument to lookup */
   const shared_ptr< spline::BSplineCurve<1, SCIP_Real> > &pcwlin, /**< second derivate of piecewise cubic lookup */
   std::string           identifier               /**< string that can be used to identify the expression */

)
{
   SCIP_USEREXPRDATA* data;
   BMSallocBlockMemory( blkmem, &data );

   new( data ) SCIP_USEREXPRDATA();
   data->lookup = pcwlin;

   assert(identifier.size() <= 10);
   strncpy(data->identifier, identifier.c_str(), identifier.size());
   //SCIPdbgMsg("data is now %s\n", data->identifier);


   SCIP_CALL(
      SCIPexprCreateUser(
         blkmem,
         expr,
         1,
         &child,
         data,
         (SCIP_EXPRINTCAPABILITY_FUNCVALUE | SCIP_EXPRINTCAPABILITY_INTFUNCVALUE | SCIP_EXPRINTCAPABILITY_GRADIENT |
            SCIP_EXPRINTCAPABILITY_INTGRADIENT ) ,
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


void SCIPexprPiecewiseLinearSetEpsilon( SCIP_Real epsilon )
{
   EPSILON = epsilon;
}

/**
 * Print the data points defining the piecewise linear expressions
 * */
void SCIPexprPiecewiseLinearPrintPoints(SCIP_USEREXPRDATA* data, SCIP_MESSAGEHDLR*  messagehdlr, FILE* file)
{
   auto coeffs = data->lookup->getCoefficients();
   for (auto it = coeffs.begin(); it < coeffs.end(); ++it) {
      int i = it - coeffs.begin();
      if (i  >= 1)
         SCIPmessageFPrintInfo(messagehdlr, file, ":");
      SCIPmessageFPrintInfo(messagehdlr, file, "(%f,%f)",data->lookup->getKnot(i), *it);
   }
}


boost::shared_ptr< spline::BSplineCurve<1, SCIP_Real> > SCIPexprPiecewiseLinearGetSpline(SCIP_USEREXPRDATA* data)
{
   return data->lookup;
}
