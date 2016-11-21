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

/**@file    LookupConsHdlr.h
 * @brief   Constraint Handler for univariate lookup functions
 * @author  Robert L. Gottwald
 *
 */


#ifndef __LOOKUPCONSHDLR_H__
#define __LOOKUPCONSHDLR_H__

#include "objscip/objscip.h"
#include <boost/shared_ptr.hpp>
#include <spline/PiecewisePolynomial.hpp>

class LookupConsHdlr : public scip::ObjConshdlr , public scip::ObjEventhdlr {
public:
     LookupConsHdlr ( SCIP *scip ) : 
          ObjConshdlr (
               scip,                                              /**< SCIP data structure */
               "lookup",                                /**< name of constraint handler */
               "Lookup constraints",                              /**< description of constraint handler */
               1000000,                                           /**< priority of the constraint handler for separation */
               -2000000,                                          /**< priority of the constraint handler for constraint enforcing */
               2000000,                                          /**< priority of the constraint handler for checking infeasibility (and propagation) */
               1,                                                 /**< frequency for separating cuts; zero means to separate only in the root node */
               -1,                                                /**< frequency for propagating domains; zero means only preprocessing propagation */
               1,                                                 /**< frequency for using all instead of only the useful constraints in separation,
                                                            *   propagation and enforcement, -1 for no eager evaluations, 0 for first only */
               -1,                                                 /**< maximal number of presolving rounds the constraint handler participates in (-1: no limit) */
               true,                                             /**< should separation method be delayed, if other separators found cuts? */
               true,                                             /**< should propagation method be delayed, if other propagators found reductions? */
               true,                                             /**< should presolving method be delayed, if other presolvers found reductions? */
               true,                                             /**< should the constraint handler be skipped, if no constraints are available? */
               SCIP_PROPTIMING_ALWAYS                           /**< positions in the node solving loop where propagation method of constraint handler should be executed */
          ), ObjEventhdlr(
               scip,
               "lookup",
               "Bound change eventhandler for lookup constraints"
          ), propagated_(false) {
               
          }


     /** destructor */
     virtual ~LookupConsHdlr() {
     }
     
     virtual SCIP_DECL_EVENTEXEC ( scip_exec );

     /** frees specific constraint data
      *
      *  WARNING! There may exist unprocessed events. For example, a variable's bound may have been already changed, but
      *  the corresponding bound change event was not yet processed.
      */
     virtual SCIP_DECL_CONSDELETE ( scip_delete );

     /** transforms constraint data into data belonging to the transformed problem */
     virtual SCIP_DECL_CONSTRANS ( scip_trans );

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
     virtual SCIP_DECL_CONSSEPALP ( scip_sepalp );

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
     virtual SCIP_DECL_CONSSEPASOL ( scip_sepasol );

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
     virtual SCIP_DECL_CONSENFOLP ( scip_enfolp );

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
     virtual SCIP_DECL_CONSENFOPS ( scip_enfops );

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
     virtual SCIP_DECL_CONSCHECK ( scip_check );

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
     virtual SCIP_DECL_CONSPROP ( scip_prop );

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
     virtual SCIP_DECL_CONSLOCK ( scip_lock );

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
     virtual SCIP_DECL_CONSDELVARS ( scip_delvars );

     /** constraint display method of constraint handler
      *
      *  The constraint handler should store a representation of the constraint into the given text file.
      */
     virtual SCIP_DECL_CONSPRINT ( scip_print );

     /** returns whether the objective plugin is copyable */
     virtual SCIP_DECL_CONSHDLRISCLONEABLE ( iscloneable ) {
          return true;
     }

     /** clone method which will be used to copy a objective plugin */
     virtual SCIP_DECL_CONSHDLRCLONE ( scip::ObjProbCloneable* clone );

     /** constraint copying method of constraint handler
      *
      *  The constraint handler can provide a copy method, which copies a constraint from one SCIP data structure into a other
      *  SCIP data structure.
      */
     virtual SCIP_DECL_CONSCOPY ( scip_copy );

private:
     bool propagated_;

};

SCIP_RETCODE SCIPcreateConsLookup (
     SCIP*                 scip,               /**< SCIP data structure */
     SCIP_CONS**           cons,               /**< pointer to hold the created constraint */
     const char*           name,               /**< name of constraint */
     SCIP_VAR*             forwardVar,
     SCIP_VAR*             arg,
     const boost::shared_ptr<spline::PiecewiseLinear>      &linearModel,             /**< the piecewise linear function approximated by the smooth lookup */
     const boost::shared_ptr<spline::PiecewisePolynomial<3> >      &lookup,             /**< the lookup function */
     const boost::shared_ptr<spline::PiecewisePolynomial<2> >      &deriv             /**< the lookup functions derivate */
);

#endif
