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

/**@file    LookupConsHdlr.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "LookupConsHdlr.h"
#include <boost/concept_check.hpp>

struct SCIP_ConsData {
     SCIP_VAR *forwardVar;
     SCIP_VAR *arg;
     bool propagated;
     boost::shared_ptr<spline::PiecewisePolynomial<3> > lookup;
     boost::shared_ptr<spline::PiecewisePolynomial<2> > derivate;
     boost::shared_ptr<spline::PiecewiseLinear> linearModel;
};

struct SCIP_EventData {
     SCIP_CONSDATA *consdata;
     int filterpos;
};


SCIP_RETCODE checkCons ( SCIP *scip, SCIP_CONS *cons, SCIP_SOL *sol, bool *violated )
{
     SCIP_CONSDATA *consdata;
     consdata = SCIPconsGetData ( cons );
     assert ( consdata != NULL );

     double solY = SCIPgetSolVal ( scip, sol, consdata->forwardVar );
     double expectedSolY = ( * ( consdata->lookup ) ) ( SCIPgetSolVal ( scip, sol, consdata->arg ) );
     *violated = !SCIPisFeasEQ ( scip,solY,expectedSolY );
     return SCIP_OKAY;
}

enum Side {
     UPPER   ,
     LOWER
};


/**
 * Computs determinant to check whether the point C is left/right/on the
 * line segment that starts in A and goes to B denoted by AB.
 * The result is:
 *  < 0    if C is right of AB
 *  = 0    if C lies on AB
 *  > 0    if C is left of AB
 */
inline double determinant ( std::pair<double,double> &A, std::pair<double,double> &B, std::pair<double,double> &C )
{
     return ( B.first-A.first )  * ( C.second-A.second )- ( C.first-A.first ) * ( B.second-A.second );
}

/**
 * Checks for the last three points of a convex set of points if the second last point has to be removed
 * for convexity. The template parameter is used to check convexity from top and from below.
 */
template<Side side>
void grahamScanCheck ( std::vector<std::pair<double,double> > &convexHull )
{
     bool check = true;
     while ( check && convexHull.size() > 2 ) {
          //determine left/right turn by determinant
          double T = determinant ( convexHull[convexHull.size()-3], convexHull[convexHull.size()-2], convexHull.back() );
          if ( ( side == UPPER && T >= 0.0 ) || ( side == LOWER && T <= 0.0 ) ) {
               convexHull.erase ( convexHull.end()-2 );
          } else {
               check = false;
          }
     }
}

/**
 * Computes the convex upper/lower hull on the linear model of the given
 * consdata using graham scan algorithm.
 */
template<Side side>
bool computeConvexHull ( SCIP *scip, SCIP_CONSDATA *consdata, std::vector<std::pair<double,double> > &out )
{
     double lb = SCIPvarGetLbLocal ( consdata->arg );
     double ub = SCIPvarGetUbLocal ( consdata->arg );
     if ( SCIPisInfinity ( scip,lb ) || SCIPisInfinity ( scip,ub ) ) {
          return false;
     }
     spline::PiecewiseLinear &linear = * ( consdata->linearModel );

     const int begin = std::upper_bound ( linear.breakPoints(), linear.breakPoints() +linear.numberOfBreakPoints(), lb )-linear.breakPoints();
     const int end = std::upper_bound ( linear.breakPoints() +begin, linear.breakPoints() +linear.numberOfBreakPoints(), ub )-linear.breakPoints();

     std::vector<std::pair<double,double> > convexHull;
     convexHull.push_back ( std::make_pair ( lb, linear ( lb ) ) );
     convexHull.push_back ( std::make_pair ( linear.breakPoint ( begin ), linear.breakValue ( begin ) ) );

     for ( int i = begin+1; i < end; ++i ) {
          convexHull.push_back ( std::make_pair ( linear.breakPoint ( i ), linear.breakValue ( i ) ) );
          grahamScanCheck<side> ( convexHull );
     }

     convexHull.push_back ( std::make_pair ( ub, linear ( ub ) ) );
     grahamScanCheck<side> ( convexHull );

     out.swap ( convexHull );
     return true;
}

/**
 * Tries to separate the given constraint by computing the convex hull on its linear model.
 * If a side of the convex hull separates the solutions value its slope is used to compute
 * the offsets for the piecewsie polynomial function. If it still separates the solution
 * a row is set up and added as cut. The success flag is set to true if the solution was
 * succesfully separated. If sol is NULL then the current LP/pseudo solution is used.
 */
SCIP_RETCODE separateCons ( SCIP *scip, SCIP_CONS *cons, SCIP_SOL *sol, bool *success )
{
     SCIP_CONSDATA *consdata;
     consdata = SCIPconsGetData ( cons );
     assert ( consdata != NULL );
     spline::PiecewisePolynomial<3> &lkp = * ( consdata->lookup );
     std::pair<double,double> solPoint = std::make_pair ( SCIPgetSolVal ( scip, sol, consdata->arg ), SCIPgetSolVal ( scip, sol, consdata->forwardVar ) );
     *success = true;

     double expectedSolY = lkp ( solPoint.first );

     std::vector<std::pair<double, double> > convexHull;
     bool solutionBelow = ( solPoint.second <  expectedSolY );

     if ( solutionBelow )
          *success = computeConvexHull<LOWER> ( scip, consdata, convexHull );
     else
          *success = computeConvexHull<UPPER> ( scip, consdata, convexHull );

     if ( ! ( *success ) )
          return SCIP_OKAY;

     std::vector<std::pair<double, double> >::iterator candidateCut = std::lower_bound ( convexHull.begin(),convexHull.end(),solPoint );
     double T = determinant ( *candidateCut, * ( candidateCut+1 ), solPoint );

     if ( ( solutionBelow && T <= 0.0 ) || ( !solutionBelow && T >= 0.0 ) ) {
          double slope = ( ( candidateCut+1 )->second - candidateCut->second ) / ( ( candidateCut+1 )->first - candidateCut->first );

          double lb = SCIPvarGetLbLocal ( consdata->arg );
          double ub = SCIPvarGetUbLocal ( consdata->arg );
          std::vector<std::pair<double, double> > extremePoints;
          //computes extreme points of piecewise polynomial function with respect the given slope
          spline::lineDistanceExtremePoints ( lb,ub, slope,lkp,* ( consdata->derivate ), extremePoints );
          //compute offsets for cut from below and from top
          double upperOffset = lkp ( ub ) - slope*ub;
          double lowerOffset = lkp ( lb ) - slope*lb;
          if ( upperOffset < lowerOffset )
               std::swap ( lowerOffset, upperOffset );

          for ( std::vector<std::pair<double, double> >::iterator iter = extremePoints.begin(); iter != extremePoints.end(); ++iter ) {
               double newOffset = iter->second -slope * iter->first;
               lowerOffset = std::min ( lowerOffset, newOffset );
               upperOffset = std::max ( upperOffset, newOffset );
          }
          
          //If cut does not separate the solution using the computed offsets then we are done
          if ( SCIPisFeasLE ( scip, slope*solPoint.first+lowerOffset, solPoint.second )
                    && SCIPisFeasLE ( scip, solPoint.second, slope*solPoint.first+upperOffset ) ) {
               *success = false;
               return SCIP_OKAY;
          }

          /*
           * Cut separates the solution thus add it. Both the lhs and rhs are used although one side suffices
           * because the bounds are computed with no additional overhead (finding min/max in one iteration)
           * and might be valuable if the local bounds of the arg variable are inside one interval of the 
           * piecwise linear model since then the piecewise polynomial function should be tightly enclosed
           * by the cut.
           *       slope*arg+lowerOffset <= forwardVar           <= slope*arg+upperOffset
           *  <=>  lowerOffset           <= forwardVar-slope*arg <= upperOffset
           */
          SCIP_ROW *cut;
          SCIP_CALL ( SCIPcreateEmptyRowCons ( scip, &cut,SCIPfindConshdlr ( scip, "lookup" ), "lookup cut", lowerOffset, upperOffset, SCIPconsIsLocal ( cons ), SCIPconsIsModifiable ( cons ), SCIPconsIsRemovable ( cons ) ) );
          SCIP_CALL ( SCIPcacheRowExtensions ( scip, cut ) );
          SCIP_CALL ( SCIPaddVarToRow ( scip, cut, consdata->forwardVar, 1 ) );
          SCIP_CALL ( SCIPaddVarToRow ( scip, cut, consdata->arg, -slope ) );
          SCIP_CALL ( SCIPflushRowExtensions ( scip, cut ) );
          SCIP_Bool infeas;
          SCIP_CALL ( SCIPaddCut ( scip, sol, cut, false, &infeas ) );
          SCIP_CALL ( SCIPreleaseRow ( scip, &cut ) );
          assert ( !infeas );
          *success = true;
     } else {
          *success = false;
     }

     return SCIP_OKAY;
}

/**
 * Propagates the bounds of the arg variable to the forward variable for the given lookup constraint by
 * computing the maximum/minimum attained value in the interval.
 */
SCIP_RETCODE propagateCons ( SCIP *scip, SCIP_CONS *cons, SCIP_RESULT *result )
{
     SCIP_CONSDATA *consdata;
     consdata = SCIPconsGetData ( cons );
     assert ( consdata != NULL );
     if ( consdata->propagated ) {
          *result = SCIP_DIDNOTRUN;
          return SCIP_OKAY;
     }
     *result = SCIP_DIDNOTFIND;

     spline::PiecewisePolynomial<3> &lkp = * ( consdata->lookup );

     double lb = SCIPisInfinity ( scip, SCIPvarGetLbLocal ( consdata->arg ) ) ? lkp.breakPoint ( 0 ) : SCIPvarGetLbLocal ( consdata->arg );
     double ub = SCIPisInfinity ( scip, SCIPvarGetUbLocal ( consdata->arg ) ) ? lkp.breakPoint ( lkp.numberOfBreakPoints()-1 ) : SCIPvarGetUbLocal ( consdata->arg );
     if ( SCIPisEQ ( scip, lb, ub ) ) {
          SCIP_Bool infeasible,fixed;
          SCIP_CALL ( SCIPfixVar ( scip, consdata->forwardVar, lkp ( lb == ub ? lb : ( ub+lb ) /2 ), &infeasible, &fixed ) );
          if ( infeasible ) {
               *result = SCIP_CUTOFF;
               return SCIP_OKAY;
          }
          if ( fixed )
               *result = SCIP_REDUCEDDOM;
          consdata->propagated = true;
          return SCIP_OKAY;
     }

     spline::PiecewisePolynomial<2> &deriv = * ( consdata->derivate );

     double propLb,propUb;
     {
          //Propagate bounds to forwardVar by computing extremepoints of lookup function inside bounds of arg variable
          std::vector<std::pair<double,double> > extremePoints;

          spline::lineDistanceExtremePoints ( lb, ub, 0.0, lkp, deriv, extremePoints );

          int i = lkp.findInterval ( lb );
          propLb = lkp ( lb, i );
          i = lkp.findInterval ( ub, i );
          propUb = lkp ( ub, i );

          if ( propUb < propLb )
               std::swap ( propLb, propUb );

          for ( std::vector<std::pair<double,double> >::iterator iter = extremePoints.begin(); iter != extremePoints.end(); ++iter ) {
               propLb = std::min ( propLb, iter->second );
               propUb = std::max ( propUb, iter->second );
          }
     }
     
     SCIP_Bool infeasible, tightened;
     //try to fix var
     if(SCIPisEQ(scip, propLb, propUb) ) {
          SCIP_CALL( SCIPfixVar(scip, consdata->forwardVar, propLb == propUb ? propLb : ( propUb+propLb ) /2, &infeasible, &tightened) );
          if ( infeasible ) {
               *result = SCIP_CUTOFF;
          } else if ( tightened ) {
               consdata->propagated = true;
               *result = SCIP_REDUCEDDOM;
          }
          return SCIP_OKAY;
     }
     
     //else tighten
     SCIP_CALL ( SCIPtightenVarLb ( scip, consdata->forwardVar, propLb, false, &infeasible, &tightened ) );
     if ( infeasible ) {
          *result = SCIP_CUTOFF;
          return SCIP_OKAY;
     }
     if ( tightened )
          *result = SCIP_REDUCEDDOM;
     SCIP_CALL ( SCIPtightenVarUb ( scip, consdata->forwardVar, propUb, false, &infeasible, &tightened ) );
     if ( infeasible ) {
          *result = SCIP_CUTOFF;
          return SCIP_OKAY;
     }
     if ( tightened )
          *result = SCIP_REDUCEDDOM;
     consdata->propagated = true;
     return SCIP_OKAY;
}

SCIP_DECL_EVENTEXEC ( LookupConsHdlr::scip_exec )
{
     eventdata->consdata->propagated = false;
     propagated_ = false;
}


/** frees specific constraint data
 *
 *  WARNING! There may exist unprocessed events. For example, a variable's bound may have been already changed, but
 *  the corresponding bound change event was not yet processed.
 */
SCIP_DECL_CONSDELETE ( LookupConsHdlr::scip_delete )
{
     assert ( consdata != NULL );

     ( *consdata )->lookup.reset();
     ( *consdata )->derivate.reset();
     ( *consdata )->linearModel.reset();

     SCIPfreeMemory ( scip, consdata );

     return SCIP_OKAY;
}

/** transforms constraint data into data belonging to the transformed problem */
SCIP_DECL_CONSTRANS ( LookupConsHdlr::scip_trans )
{
     SCIP_CONSDATA* sourcedata = NULL;
     SCIP_CONSDATA* targetdata = NULL;

     sourcedata = SCIPconsGetData ( sourcecons );
     assert ( sourcedata != NULL );

     SCIP_CALL ( SCIPallocMemory ( scip, &targetdata ) );
     targetdata->lookup = sourcedata->lookup;
     targetdata->derivate = sourcedata->derivate;
     targetdata->linearModel = sourcedata->linearModel;

     /* create target constraint */
     SCIP_CALL ( SCIPcreateCons ( scip, targetcons, SCIPconsGetName ( sourcecons ), conshdlr, targetdata,
                                  SCIPconsIsInitial ( sourcecons ), SCIPconsIsSeparated ( sourcecons ), SCIPconsIsEnforced ( sourcecons ),
                                  SCIPconsIsChecked ( sourcecons ), SCIPconsIsPropagated ( sourcecons ),  SCIPconsIsLocal ( sourcecons ),
                                  SCIPconsIsModifiable ( sourcecons ), SCIPconsIsDynamic ( sourcecons ), SCIPconsIsRemovable ( sourcecons ),
                                  SCIPconsIsStickingAtNode ( sourcecons ) ) );

     return SCIP_OKAY;
}

/** separation method of constraint handler for LP solution
 *
 *  Separates all constraints of the constraint handler. The method is called in the LP solution loop,
 *  which means that a valid LP solution exists.
 *
 *  The first nusefulconss constraints are the ones, that are identified to likely be violated. The separation
 *  method should process only the useful constraints in most runs, and only occasionally the remaining
 *  nconss - nusefulconss constraints.
 *
 *  possible return values for *result (if more than one applies, the first in the list should be used):
 *  - SCIP_CUTOFF     : the node is infeasible in the variable's bounds and can be cut off
 *  - SCIP_CONSADDED  : an additional constraint was generated
 *  - SCIP_REDUCEDDOM : a variable's domain was reduced
 *  - SCIP_SEPARATED  : a cutting plane was generated
 *  - SCIP_DIDNOTFIND : the separator searched, but did not find domain reductions, cutting planes, or cut constraints
 *  - SCIP_DIDNOTRUN  : the separator was skipped
 *  - SCIP_DELAYED    : the separator was skipped, but should be called again
 */
SCIP_DECL_CONSSEPALP ( LookupConsHdlr::scip_sepalp )
{
     *result = SCIP_DIDNOTFIND;
     for ( int  i = 0; i< nusefulconss; ++i ) {


     }
     return SCIP_OKAY;
}

bool solutionIsExcluded ( SCIP *scip, SCIP_SOL *sol, SCIP_CONS *cons )
{
     SCIP_CONSDATA *consdata;
     consdata = SCIPconsGetData ( cons );
     assert ( consdata != NULL );
     double val = SCIPgetSolVal ( scip, sol, consdata->forwardVar );
     double bound = SCIPvarGetLbLocal ( consdata->forwardVar );
     if ( SCIPisLT ( scip, val, bound ) )
          return true;
     bound = SCIPvarGetUbLocal ( consdata->forwardVar );
     if ( SCIPisGT ( scip, val, bound ) )
          return true;
}


/** separation method of constraint handler for arbitrary primal solution
 *
 *  Separates all constraints of the constraint handler. The method is called outside the LP solution loop (e.g., by
 *  a relaxator or a primal heuristic), which means that there is no valid LP solution.
 *  Instead, the method should produce cuts that separate the given solution.
 *
 *  The first nusefulconss constraints are the ones, that are identified to likely be violated. The separation
 *  method should process only the useful constraints in most runs, and only occasionally the remaining
 *  nconss - nusefulconss constraints.
 *
 *  possible return values for *result (if more than one applies, the first in the list should be used):
 *  - SCIP_CUTOFF     : the node is infeasible in the variable's bounds and can be cut off
 *  - SCIP_CONSADDED  : an additional constraint was generated
 *  - SCIP_REDUCEDDOM : a variable's domain was reduced
 *  - SCIP_SEPARATED  : a cutting plane was generated
 *  - SCIP_DIDNOTFIND : the separator searched, but did not find domain reductions, cutting planes, or cut constraints
 *  - SCIP_DIDNOTRUN  : the separator was skipped
 *  - SCIP_DELAYED    : the separator was skipped, but should be called again
 */
SCIP_DECL_CONSSEPASOL ( LookupConsHdlr::scip_sepasol )
{
     *result = SCIP_DIDNOTFIND;
     for ( int i=0; i< nconss; ++i ) {
          SCIP_RESULT propResult;
          SCIP_CALL ( propagateCons ( scip, conss[i], &propResult ) );

          if ( propResult == SCIP_CUTOFF || propResult == SCIP_REDUCEDDOM ) {

               *result = propResult;
               return SCIP_OKAY;
          }

          bool separated;

          SCIP_CALL ( separateCons ( scip, conss[i], NULL, &separated ) );
          if ( separated ) {
               *result = SCIP_SEPARATED;
               return SCIP_OKAY;
          }
     }
     return SCIP_OKAY;
}


/** constraint enforcing method of constraint handler for LP solutions
 *
 *  The method is called at the end of the node processing loop for a node where the LP was solved.
 *  The LP solution has to be checked for feasibility. If possible, an infeasibility should be resolved by
 *  branching, reducing a variable's domain to exclude the solution or separating the solution with a valid
 *  cutting plane.
 *
 *  The enforcing methods of the active constraint handlers are called in decreasing order of their enforcing
 *  priorities until the first constraint handler returned with the value SCIP_CUTOFF, SCIP_SEPARATED,
 *  SCIP_REDUCEDDOM, SCIP_CONSADDED, or SCIP_BRANCHED.
 *  The integrality constraint handler has an enforcing priority of zero. A constraint handler which can
 *  (or wants) to enforce its constraints only for integral solutions should have a negative enforcing priority
 *  (e.g. the alldiff-constraint can only operate on integral solutions).
 *  A constraint handler which wants to incorporate its own branching strategy even on non-integral
 *  solutions must have an enforcing priority greater than zero (e.g. the SOS-constraint incorporates
 *  SOS-branching on non-integral solutions).
 *
 *  The first nusefulconss constraints are the ones, that are identified to likely be violated. The enforcing
 *  method should process the useful constraints first. The other nconss - nusefulconss constraints should only
 *  be enforced, if no violation was found in the useful constraints.
 *
 *  possible return values for *result (if more than one applies, the first in the list should be used):
 *  - SCIP_CUTOFF     : the node is infeasible in the variable's bounds and can be cut off
 *  - SCIP_CONSADDED  : an additional constraint was generated
 *  - SCIP_REDUCEDDOM : a variable's domain was reduced
 *  - SCIP_SEPARATED  : a cutting plane was generated
 *  - SCIP_BRANCHED   : no changes were made to the problem, but a branching was applied to resolve an infeasibility
 *  - SCIP_INFEASIBLE : at least one constraint is infeasible, but it was not resolved
 *  - SCIP_FEASIBLE   : all constraints of the handler are feasible
 */
SCIP_DECL_CONSENFOLP ( LookupConsHdlr::scip_enfolp )
{

     *result = SCIP_FEASIBLE;

     for ( int i = 0; i < nconss; ++i ) {
          bool violated = false;
          SCIP_CALL ( checkCons ( scip, conss[i], NULL, &violated ) );
          if ( violated ) {
               SCIP_RESULT propResult;
               SCIP_CALL ( propagateCons ( scip, conss[i], &propResult ) );

               if ( propResult == SCIP_CUTOFF || propResult == SCIP_REDUCEDDOM ) {
                    *result = propResult;
                    return SCIP_OKAY;
               }

               bool separated;

               SCIP_CALL ( separateCons ( scip, conss[i], NULL, &separated ) );
               if ( separated ) {
                    *result = SCIP_SEPARATED;
                    return SCIP_OKAY;
               }

               *result = SCIP_INFEASIBLE;
          }
     }

     return SCIP_OKAY;

}

/** constraint enforcing method of constraint handler for pseudo solutions
 *
 *  The method is called at the end of the node processing loop for a node where the LP was not solved.
 *  The pseudo solution has to be checked for feasibility. If possible, an infeasibility should be resolved by
 *  branching, reducing a variable's domain to exclude the solution or adding an additional constraint.
 *  Separation is not possible, since the LP is not processed at the current node. All LP informations like
 *  LP solution, slack values, or reduced costs are invalid and must not be accessed.
 *
 *  Like in the enforcing method for LP solutions, the enforcing methods of the active constraint handlers are
 *  called in decreasing order of their enforcing priorities until the first constraint handler returned with
 *  the value SCIP_CUTOFF, SCIP_REDUCEDDOM, SCIP_CONSADDED, SCIP_BRANCHED, or SCIP_SOLVELP.
 *
 *  The first nusefulconss constraints are the ones, that are identified to likely be violated. The enforcing
 *  method should process the useful constraints first. The other nconss - nusefulconss constraints should only
 *  be enforced, if no violation was found in the useful constraints.
 *
 *  If the pseudo solution's objective value is lower than the lower bound of the node, it cannot be feasible
 *  and the enforcing method may skip it's check and set *result to SCIP_DIDNOTRUN. However, it can also process
 *  its constraints and return any other possible result code.
 *
 *  possible return values for *result (if more than one applies, the first in the list should be used):
 *  - SCIP_CUTOFF     : the node is infeasible in the variable's bounds and can be cut off
 *  - SCIP_CONSADDED  : an additional constraint was generated
 *  - SCIP_REDUCEDDOM : a variable's domain was reduced
 *  - SCIP_BRANCHED   : no changes were made to the problem, but a branching was applied to resolve an infeasibility
 *  - SCIP_SOLVELP    : at least one constraint is infeasible, and this can only be resolved by solving the SCIP_LP
 *  - SCIP_INFEASIBLE : at least one constraint is infeasible, but it was not resolved
 *  - SCIP_FEASIBLE   : all constraints of the handler are feasible
 *  - SCIP_DIDNOTRUN  : the enforcement was skipped (only possible, if objinfeasible is true)
 */
SCIP_DECL_CONSENFOPS ( LookupConsHdlr::scip_enfops )
{
     *result = SCIP_FEASIBLE;

     for ( int i = 0; i < nconss; ++i ) {
          bool violated = false;
          SCIP_CALL ( checkCons ( scip, conss[i], NULL, &violated ) );
          if ( violated ) {
               SCIP_RESULT propResult;
               SCIP_CALL ( propagateCons ( scip, conss[i], &propResult ) );

               if ( propResult == SCIP_CUTOFF ) {
                    *result = propResult;
                    return SCIP_OKAY;
               }

               if ( propResult == SCIP_REDUCEDDOM ) {
                    *result = propResult;
                    if ( solutionIsExcluded ( scip, NULL, conss[i] ) )
                         return SCIP_OKAY;
               }

               *result = SCIP_INFEASIBLE;
          }
     }

     return SCIP_OKAY;
}

/** feasibility check method of constraint handler for primal solutions
 *
 *  The given solution has to be checked for feasibility.
 *
 *  The check methods of the active constraint handlers are called in decreasing order of their check
 *  priorities until the first constraint handler returned with the result SCIP_INFEASIBLE.
 *  The integrality constraint handler has a check priority of zero. A constraint handler which can
 *  (or wants) to check its constraints only for integral solutions should have a negative check priority
 *  (e.g. the alldiff-constraint can only operate on integral solutions).
 *  A constraint handler which wants to check feasibility even on non-integral solutions must have a
 *  check priority greater than zero (e.g. if the check is much faster than testing all variables for
 *  integrality).
 *
 *  In some cases, integrality conditions or rows of the current LP don't have to be checked, because their
 *  feasibility is already checked or implicitly given. In these cases, 'checkintegrality' or
 *  'checklprows' is FALSE.
 *
 *  possible return values for *result:
 *  - SCIP_INFEASIBLE : at least one constraint of the handler is infeasible
 *  - SCIP_FEASIBLE   : all constraints of the handler are feasible
 */
SCIP_DECL_CONSCHECK ( LookupConsHdlr::scip_check )
{
     *result = SCIP_FEASIBLE;

     for ( int i = 0; i < nconss; ++i ) {
          bool violated = false;
          SCIP_CALL ( checkCons ( scip, conss[i], sol, &violated ) );
          if ( violated ) {
               *result = SCIP_INFEASIBLE;
               return SCIP_OKAY;
          }
     }

     return SCIP_OKAY;
}

/** domain propagation method of constraint handler
 *
 *  The first nusefulconss constraints are the ones, that are identified to likely be violated. The propagation
 *  method should process only the useful constraints in most runs, and only occasionally the remaining
 *  nconss - nusefulconss constraints.
 *
 *  possible return values for *result:
 *  - SCIP_CUTOFF     : the node is infeasible in the variable's bounds and can be cut off
 *  - SCIP_REDUCEDDOM : at least one domain reduction was found
 *  - SCIP_DIDNOTFIND : the propagator searched, but did not find any domain reductions
 *  - SCIP_DIDNOTRUN  : the propagator was skipped
 *  - SCIP_DELAYED    : the propagator was skipped, but should be called again
 */
SCIP_DECL_CONSPROP ( LookupConsHdlr::scip_prop )
{
     if ( propagated_ ) {
          *result = SCIP_DIDNOTRUN;
          return SCIP_OKAY;
     }
     *result = SCIP_DIDNOTFIND;
     for ( int i=0; i<nconss; ++i ) {
          SCIP_RESULT propResult;
          SCIP_CALL ( propagateCons ( scip, conss[i], &propResult ) );
          switch ( propResult ) {
          case SCIP_CUTOFF:
               *result = SCIP_CUTOFF;
               return SCIP_OKAY;
          case SCIP_REDUCEDDOM:
               *result = SCIP_REDUCEDDOM;
          }
     }
     propagated_ = true;
     return SCIP_OKAY;
}

/** variable rounding lock method of constraint handler
 *
 *  This method is called, after a constraint is added or removed from the transformed problem.
 *  It should update the rounding locks of all associated variables with calls to SCIPaddVarLocks(),
 *  depending on the way, the variable is involved in the constraint:
 *  - If the constraint may get violated by decreasing the value of a variable, it should call
 *    SCIPaddVarLocks(scip, var, nlockspos, nlocksneg), saying that rounding down is potentially rendering the
 *    (positive) constraint infeasible and rounding up is potentially rendering the negation of the constraint
 *    infeasible.
 *  - If the constraint may get violated by increasing the value of a variable, it should call
 *    SCIPaddVarLocks(scip, var, nlocksneg, nlockspos), saying that rounding down is potentially rendering the
 *    constraint's negation infeasible and rounding up is potentially rendering the constraint itself
 *    infeasible.
 *  - If the constraint may get violated by changing the variable in any direction, it should call
 *    SCIPaddVarLocks(scip, var, nlockspos + nlocksneg, nlockspos + nlocksneg).
 *
 *  Consider the linear constraint "3x -5y +2z <= 7" as an example. The variable rounding lock method of the
 *  linear constraint handler should call SCIPaddVarLocks(scip, x, nlocksneg, nlockspos),
 *  SCIPaddVarLocks(scip, y, nlockspos, nlocksneg) and SCIPaddVarLocks(scip, z, nlocksneg, nlockspos) to tell SCIP,
 *  that rounding up of x and z and rounding down of y can destroy the feasibility of the constraint, while rounding
 *  down of x and z and rounding up of y can destroy the feasibility of the constraint's negation "3x -5y +2z > 7".
 *  A linear constraint "2 <= 3x -5y +2z <= 7" should call
 *  SCIPaddVarLocks(scip, ..., nlockspos + nlocksneg, nlockspos + nlocksneg) on all variables, since rounding in both
 *  directions of each variable can destroy both the feasibility of the constraint and it's negation
 *  "3x -5y +2z < 2  or  3x -5y +2z > 7".
 *
 *  If the constraint itself contains other constraints as sub constraints (e.g. the "or" constraint concatenation
 *  "c(x) or d(x)"), the rounding lock methods of these constraints should be called in a proper way.
 *  - If the constraint may get violated by the violation of the sub constraint c, it should call
 *    SCIPaddConsLocks(scip, c, nlockspos, nlocksneg), saying that infeasibility of c may lead to infeasibility of
 *    the (positive) constraint, and infeasibility of c's negation (i.e. feasibility of c) may lead to infeasibility
 *    of the constraint's negation (i.e. feasibility of the constraint).
 *  - If the constraint may get violated by the feasibility of the sub constraint c, it should call
 *    SCIPaddConsLocks(scip, c, nlocksneg, nlockspos), saying that infeasibility of c may lead to infeasibility of
 *    the constraint's negation (i.e. feasibility of the constraint), and infeasibility of c's negation (i.e. feasibility
 *    of c) may lead to infeasibility of the (positive) constraint.
 *  - If the constraint may get violated by any change in the feasibility of the sub constraint c, it should call
 *    SCIPaddConsLocks(scip, c, nlockspos + nlocksneg, nlockspos + nlocksneg).
 *
 *  Consider the or concatenation "c(x) or d(x)". The variable rounding lock method of the or constraint handler
 *  should call SCIPaddConsLocks(scip, c, nlockspos, nlocksneg) and SCIPaddConsLocks(scip, d, nlockspos, nlocksneg)
 *  to tell SCIP, that infeasibility of c and d can lead to infeasibility of "c(x) or d(x)".
 *
 *  As a second example, consider the equivalence constraint "y <-> c(x)" with variable y and constraint c. The
 *  constraint demands, that y == 1 if and only if c(x) is satisfied. The variable lock method of the corresponding
 *  constraint handler should call SCIPaddVarLocks(scip, y, nlockspos + nlocksneg, nlockspos + nlocksneg) and
 *  SCIPaddConsLocks(scip, c, nlockspos + nlocksneg, nlockspos + nlocksneg), because any modification to the
 *  value of y or to the feasibility of c can alter the feasibility of the equivalence constraint.
 */
SCIP_DECL_CONSLOCK ( LookupConsHdlr::scip_lock )
{
     return SCIP_OKAY;
}

/** variable deletion method of constraint handler
 *
 *  This method should iterate over all constraints of the constraint handler and delete all variables
 *  that were marked for deletion by SCIPdelVar().
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - conshdlr        : the constraint handler itself
 *  - conss           : array of constraints in transformed problem
 *  - nconss          : number of constraints in transformed problem
 */
SCIP_DECL_CONSDELVARS ( LookupConsHdlr::scip_delvars )
{
     return SCIP_OKAY;
}

/** constraint display method of constraint handler
 *
 *  The constraint handler should store a representation of the constraint into the given text file.
 */
SCIP_DECL_CONSPRINT ( LookupConsHdlr::scip_print )
{
     return SCIP_OKAY;
}

/** clone method which will be used to copy a objective plugin */
SCIP_DECL_CONSHDLRCLONE ( scip::ObjProbCloneable* LookupConsHdlr::clone )
{

}

/** constraint copying method of constraint handler
 *
 *  The constraint handler can provide a copy method, which copies a constraint from one SCIP data structure into a other
 *  SCIP data structure.
 */
SCIP_DECL_CONSCOPY ( LookupConsHdlr::scip_copy )
{
     return SCIP_OKAY;
}

SCIP_RETCODE SCIPcreateConsLookup (
     SCIP*                 scip,               /**< SCIP data structure */
     SCIP_CONS**           cons,               /**< pointer to hold the created constraint */
     const char*           name,               /**< name of constraint */
     SCIP_VAR*             forwardVar,
     SCIP_VAR*             arg,
     const boost::shared_ptr<spline::PiecewiseLinear>      &linearModel,             /**< the lookup table */
     const boost::shared_ptr<spline::PiecewisePolynomial<3> >      &lookup,             /**< the lookup table */
     const boost::shared_ptr<spline::PiecewisePolynomial<2> >      &deriv             /**< the lookup table */
)
{
     /* find the lookup constraint handler */
     SCIP_CONSHDLR *conshdlr = SCIPfindConshdlr ( scip, "lookup" );
     if ( conshdlr == NULL ) {
          SCIPerrorMessage ( "lookup constraint handler not found\n" );
          return SCIP_PLUGINNOTFOUND;
     }
     /* find the lookup event handler */
     SCIP_EVENTHDLR *eventhdlr = SCIPfindEventhdlr ( scip, "lookup" );
     if ( eventhdlr == NULL ) {
          SCIPerrorMessage ( "lookup event handler not found\n" );
          return SCIP_PLUGINNOTFOUND;
     }

     SCIP_EVENTDATA *eventdata = NULL;
     SCIP_CONSDATA *consdata = NULL;

     /* create constraint data */
     SCIP_CALL ( SCIPallocMemory ( scip, &consdata ) );
     consdata->forwardVar = forwardVar;
     consdata->arg = arg;
     consdata->linearModel = linearModel;
     consdata->lookup = lookup;
     consdata->derivate = deriv;
     SCIP_CALL ( SCIPallocMemory ( scip, &eventdata ) );
     eventdata->consdata = consdata;
     SCIP_CALL ( SCIPcatchVarEvent ( scip, arg, SCIP_EVENTTYPE_BOUNDTIGHTENED | SCIP_EVENTTYPE_VARFIXED, eventhdlr, eventdata, & ( eventdata->filterpos ) ) );
     /* create constraint */
     SCIP_CALL ( SCIPcreateCons ( scip, cons, name, conshdlr, consdata, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE ) );

     return SCIP_OKAY;
}
