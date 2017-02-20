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

/**@file   ReaderSDO.cpp
 * @brief  C++ file reader for sdo data files
 * @author Robert Lion Gottwald
 */

#include <unordered_set>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>

#include <sdo/VopFile.hpp>
#include <sdo/Parsers.hpp>
#include <sdo/ExpressionGraph.hpp>
#include <sdo/Objective.hpp>
#include <sdo/ButcherTableau.hpp>

#include <spline/PiecewisePolynomial.hpp>
#include <spline/SplineApproximation.hpp>

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/make_shared.hpp>

#include <scip/cons_nonlinear.h>
#include <scip/scip.h>
#include <scip/cons_linear.h>
#include <scip/cons_varbound.h>
#include <scip/cons_superindicator.h>

#include "ReaderSDO.h"
#include "SDList.h"
#include "ProbDataSD.h"
#include "MdlExpressionTranslator.h"


using boost::unordered_map;
using boost::hash;
using boost::shared_ptr;
using boost::make_shared;

/**
 * Compute a smooth approximation for given piecwise linear lookup
 * @param maxrelerr max allowed relative error on input. Actual max relative error on output
 */
static shared_ptr< spline::BSplineCurve<3, SCIP_Real> > getLookupApproximation(const sdo::LookupTable& lkp, SCIP_Real &maxrelerr, SCIP_Real epsilon)
{
   spline::BSplineCurve<1, SCIP_Real> pcws_lin(lkp.getXvals(), lkp.getYvals());

   SCIP_Real range = lkp.getXvals().back() - lkp.getXvals().front();

   auto spline = spline::ApproximatePiecewiseLinear(
                    pcws_lin,
                    lkp.getXvals().front() - range / 2,
                    lkp.getXvals().back() + range / 2,
                    maxrelerr, 1.0, epsilon, epsilon);

   return make_shared<decltype(spline)>(std::move(spline));
}

/** destructor of file reader to free user data (called when SCIP is exiting) */
SCIP_DECL_READERFREE(sdo::ReaderSDO::scip_free)
{
   return SCIP_OKAY;
}

/** problem reading method of reader
 *
 *  possible return values for *result:
 *  - SCIP_SUCCESS    : the reader read the file correctly and created an appropritate problem
 *  - SCIP_DIDNOTRUN  : the reader is not responsible for given input file
 *
 *  If the reader detected an error in the input file, it should return with RETCODE SCIP_READERR or SCIP_NOFILE.
 */
SCIP_DECL_READERREAD(sdo::ReaderSDO::scip_read)
{
   /* Get parameters */
   ButcherTableau tableau(sdscip::SDproblemStructureInterface::getButcherTableau(scip, discretization));

   try
   {
      std::string fName(filename);
      sdo::VopFile sdoFile;
      sdo::ExpressionGraph exprGraph;
      sdo::Objective objective;

      try
      {
          sdoFile = sdo::parse_vop_file(fName);
      }
      catch(const std::ios_base::failure& err)
      {
         SCIPerrorMessage("Failed opening file: %s\n", fName.c_str());
         return SCIP_NOFILE;
      }

      //parse objective from vpd file
      try
      {
         if( !sdoFile.getObjectiveFile().empty() )
            sdo::parse_vpd_file(sdoFile.getObjectiveFile(), objective);
      }
      catch(const std::ios_base::failure& err)
      {
         SCIPerrorMessage("Failed opening file: %s\n", sdoFile.getObjectiveFile().c_str());
         return SCIP_NOFILE;
      }

      //parse control into exprGraph from voc file (needs to be done before mdl)
      try
      {
         if( !sdoFile.getControlFile().empty() )
            sdo::parse_voc_file(sdoFile.getControlFile(), exprGraph);
      }
      catch(const std::ios_base::failure& err)
      {
         SCIPerrorMessage("Failed opening file: %s\n", sdoFile.getControlFile().c_str());
         return SCIP_NOFILE;
      }
      //parse model into exprGraph from mdl file
      try
      {
         if( !sdoFile.getModelFile().empty() )
            sdo::parse_mdl_file(sdoFile.getModelFile(), exprGraph);
         else
            return SCIP_ERROR;
      }
      catch(const std::ios_base::failure& err)
      {
         SCIPerrorMessage("Failed opening file: %s\n", sdoFile.getModelFile().c_str());
         return SCIP_NOFILE;
      }

      //analyze exprGraph to find static constant and dynamic nodes
      exprGraph.analyze();

      //map to store lookup approximation for each lookup_table
      LookupMap lkpMap;

      if(strcmp(lookuptype, "cubic") == 0)
      {
         boost::filesystem::path p(filename);
         std::string lookupsFile = p.stem().generic_string();
         lookupsFile += "_lookups.dat";
         std::ifstream ifs(lookupsFile, std::ios::binary);
         //for cubic lookups check if approximation is stored in file
         //and read them if so
         if( ifs.good() )
         {
            SCIPinfoMessage(scip, nullptr, "Reading lookup approximations from file '%s'\n", lookupsFile.c_str());
            std::vector<std::pair<std::string, SplinePtr>> lookupsVec;
            boost::archive::binary_iarchive ia(ifs);
            ia >> lookupsVec;

            for( auto & entry : lookupsVec )
            {
               sdo::ExpressionGraph::Node* node = exprGraph.getNode(sdo::Symbol(std::move(entry.first)));

               if( node->op == sdo::ExpressionGraph::APPLY_LOOKUP )
               {
                  lkpMap.emplace(node->child1, std::move(entry.second));
               }
               else
               {
                  assert(node->op == ExpressionGraph::LOOKUP_TABLE);
                  lkpMap.emplace(node, std::move(entry.second));
               }
            }
         }
         else
         {
            //otherwise compute the approximations
            std::vector<std::pair<std::string, SplinePtr>> lookupsVec;

            for(std::pair<const sdo::Symbol, sdo::ExpressionGraph::Node*>& entry : exprGraph.getSymbolTable())
            {
               SCIP_Real realErr = lookupMaxRelErr;

               if( entry.second->op == sdo::ExpressionGraph::APPLY_LOOKUP )
               {
                  SCIPinfoMessage(scip, nullptr, "Lookup in definition of '%s'\n", entry.first.get().c_str());

                  if( lkpMap.find(entry.second->child1) != lkpMap.end() )
                  {
                     SCIPinfoMessage(scip, nullptr, "-> already done... skipping\n");
                     continue;
                  }

                  SCIPinfoMessage(scip, nullptr, "-> computing approximation... ");
                  lkpMap[entry.second->child1] = getLookupApproximation(*(entry.second->child1->lookup_table), realErr, lookupAproxTol);
                  SCIPinfoMessage(scip, nullptr, "maximum relative error is %f\n ", realErr);

                  lookupsVec.emplace_back(entry.first, lkpMap[entry.second->child1]);
               }
               else if( entry.second->op == sdo::ExpressionGraph::LOOKUP_TABLE )
               {
                  SCIPinfoMessage(scip, nullptr, "Lookup '%s'\n", entry.first.get().c_str());
                  SCIPinfoMessage(scip, nullptr, "-> computing approximation... ");
                  lkpMap[entry.second] = getLookupApproximation(*(entry.second->lookup_table),  realErr, lookupAproxTol);
                  SCIPinfoMessage(scip, nullptr, "maximum relative error is %f\n ", realErr);
                  lookupsVec.emplace_back(entry.first, lkpMap[entry.second]);
               }
            }

            //if there were any lookups write the approximations to a file
            if( !lookupsVec.empty() )
            {
               SCIPinfoMessage(scip, nullptr, "Writing lookup approximations to file '%s'\n", lookupsFile.c_str());
               std::ofstream ofs(lookupsFile, std::ios::binary);
               boost::archive::binary_oarchive oa(ofs);
               oa << lookupsVec;
            }
         }
      }
      //now create the scip problem
      SCIP_CALL( SCIPcreateProbBasic(scip, fName.c_str()) );
      SCIP_CALL( SDinit(scip) );
      sdscip::SDproblemStructureInterface* structure = SDgetStructure(scip);

      //get start, end time, and size of time step
      const SCIP_Real initial_time = exprGraph.getNode(sdo::Symbol("INITIAL TIME"))->value;
      const SCIP_Real final_time = exprGraph.getNode(sdo::Symbol("FINAL TIME"))->value;
      const SCIP_Real time_step = exprGraph.getNode(sdo::Symbol("TIME STEP"))->value;
      //compute number of timesteps
      const int time_step_count = (final_time - initial_time) / time_step  + 1;

      //set up class to translate expressions in the expression graph of the mdl-file
      //into expressions of scip
      MdlExpressionTranslator expr_translator(scip, exprGraph, lkpMap);
      //decide for which nodes variables are created based on settings of reader
      std::vector<MdlScipVar> vars = expr_translator.createVariableMapping(objective,
                                                                           useMinVariableFormulation,
                                                                           true,
                                                                           (ratealgebraic || (multistep > 1)),
                                                                           isolatelookups);
      //vector of expressions that compute the value of states for next timestep and value of other variables for current timestep
      std::vector<SCIP_EXPR*> varexprs(vars.size());
      //set up a boundmap for strict bounds of variables (e.g. to avoid division by zero or negative roots)
      sdscip::SDproblemStructureInterface::BoundMap boundMap;

      std::size_t nstates = 0;
      for( const MdlScipVar & var : vars )
      {
         SCIP_CALL( SCIPexprCreate(SCIPblkmem(scip), &varexprs[var.idx], SCIP_EXPR_VARIDX, var.idx) );

         if( var.positive)
         {
            SCIPinfoMessage(scip, NULL, "Constrained variable '%s' to be positive only.\n", var.name.c_str() );
            boundMap.emplace(sdscip::SDproblemStructureInterface::BoundKey{var.idx, SCIP_BOUNDTYPE_LOWER}, var.getLb(scip));
         }
         if( var.negative)
         {
            SCIPinfoMessage(scip, NULL, "Constrained variable '%s' to be negative only.\n", var.name.c_str() );
            boundMap.emplace(sdscip::SDproblemStructureInterface::BoundKey{var.idx, SCIP_BOUNDTYPE_UPPER}, var.getUb(scip));
         }

         if( var.node->op == ExpressionGraph::INTEG )
         {
            ++nstates;
         }
      }
      //store boundmap in problem structure
      structure->setStrictBounds(std::move(boundMap));
      {
         //set up expressions to evaluate the rates for each state
         std::vector<SCIP_EXPR*> rate_expressions(nstates);
         std::vector<SCIP_EXPR*> rate_expressions_algebraic(nstates);
         std::vector<sdo::ExpressionGraph::Node*> rate_expr_params;
         {
            //rate expression translator will produce scip expressions using only variables for states
            MdlExpressionTranslator rate_expr_translator(scip, exprGraph, lkpMap);
            //create minimal mapping with empty objective, i.e. only state vars
            std::vector<MdlScipVar> state_vars = rate_expr_translator.createVariableMapping(sdo::Objective(), true, false);
            //set variable's expressions to just their values
            rate_expr_translator.setVars(state_vars);
            expr_translator.setVars(vars);

            //build rates expressions
            std::size_t i;
            for( i = 0; i < nstates; ++i )
            {
               assert(int(i) == state_vars[i].idx);
               SCIP_CALL( rate_expr_translator.getScipExpr(state_vars[i].node->child1, &rate_expressions[i]) );
               SCIP_CALL( expr_translator.getScipExpr(state_vars[i].node->child1, &rate_expressions_algebraic[i]) );
            }
            //store rate expression parameters
            rate_expr_params = rate_expr_translator.getParameterNodes();
         }

         //now build expression to compute the states value for the next timestep using the
         //discretitzation method that is set

         // for d == 0 state_exprs[state.idx][d] stores the states current value
         // for d > 0  state_exprs[state.idx][d] stores the states rate based on intermediate values
         std::vector<std::array<SCIP_EXPR*, ButcherTableau::MAX_ROWS()>> state_exprs(nstates);

         //setup state_exprs[i][0] with current state value
         for( std::size_t i = 0; i < nstates; ++i )
         {
            assert(int(i) == vars[i].idx);
            SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &state_exprs[i][0], varexprs[i]) );
         }

         //coeffs to setup linear expression that defines the next intermediate value
         SCIP_Real coeffs[ButcherTableau::MAX_ROWS()];
         coeffs[0] = 1;
         //next value is based on previous one with coeff 1
         //other coeffs are set to the current row of the butcher tableau
         //in the loop below but scaled by the value of time_step

         for( int d = 1; d < tableau.rows(); ++d )
         {
            //set variables to current varexprs (initially just the variable values)
            expr_translator.setVars(vars, varexprs);
            //update coefficients (row from butcher tableau scaled with time step size)
            for( int k = 0; k < d; ++k )
               coeffs[k + 1] = time_step * tableau[d][k];

            //build next states
            std::size_t i;
            for( i = 0; i < nstates; ++i )
            {
               assert(int(i) == vars[i].idx);
               SCIP_EXPR* rates[ButcherTableau::MAX_ROWS()];
               //evaluate rate of state at current state value and store into state_exprs
               SCIP_CALL( expr_translator.getScipExpr(vars[i].node->child1, &state_exprs[i][d], false, true) );
               //and compute new state value using current state values and rates
               //and the coefficients from the tableau
               for(int k = 0; k <= d; ++k)
                  SCIPexprCopyDeep(SCIPblkmem(scip), &rates[k], state_exprs[i][k]);

               SCIPexprFreeDeep(SCIPblkmem(scip), &varexprs[i]);
               SCIP_CALL( SCIPexprCreateLinear(SCIPblkmem(scip), &varexprs[i], d + 1, rates, coeffs, 0.0) );
            }
            //and now evaluate the other variable values based on new state values
            for( ; i < vars.size(); ++i )
            {
               //set expr translator variables to new values
               expr_translator.setVars(vars, varexprs);
               assert(int(i) == vars[i].idx);
               switch( vars[i].node->op )
               {
               case ExpressionGraph::INTEG:
                  assert(false); //states should not occur since i >= nstates
               case ExpressionGraph::CONTROL:
                  //controls do not have expressions
                  break;
               case ExpressionGraph::G:
               case ExpressionGraph::GE:
               case ExpressionGraph::L:
               case ExpressionGraph::LE:
               case ExpressionGraph::EQ:
               case ExpressionGraph::NEQ:
                  //TODO need multiple decision variables?
                  break;
               default:
                  //algebraic is evaluated with new state values and stored into var exprs
                  SCIPexprFreeDeep(SCIPblkmem(scip), &varexprs[i]);
                  SCIP_CALL( expr_translator.getScipExpr(vars[i].node, &varexprs[i]) );
               }
            }
         }

         //free the expressions that are not used anymore
         for( std::size_t i = 0; i < nstates; ++i )
         {
            for( int d = 0; d < tableau.rows(); ++d )
               SCIPexprFreeDeep(SCIPblkmem(scip), &state_exprs[i][d]);
         }

         //now algebraic variables contain expressions based on intermediate state values
         //so the expr_translator variables need to be set to the acutal variable values
         //and the algebraic expressions need to be rebuild
         expr_translator.setVars(vars);
         std::size_t algebraicStart = vars.size();
         for( std::size_t i = nstates; i < vars.size(); ++i )
         {
            assert(int(i) == vars[i].idx);
            switch( vars[i].node->op )
            {
            case ExpressionGraph::INTEG:
               assert(false); //states should not occur since i >= nstates
            case ExpressionGraph::CONTROL:
               //controls do not have expressions
               break;
            default:
               if(algebraicStart == vars.size())
                  algebraicStart = i;
               //algebraic is evaluated with state values and stored into var exprs
               SCIPexprFreeDeep(SCIPblkmem(scip), &varexprs[i]);
               SCIP_CALL( expr_translator.getScipExpr(vars[i].node, &varexprs[i]) );
            }
         }
         //now set up the expressions that are stored inside the structure
         std::vector<SCIP_EXPR*> xdot;
         std::vector<SCIP_EXPR*> xdotalgebraic;
         std::vector<std::string> stateVarNames;
         std::vector<std::string> controlVarNames;
         std::vector<std::string> algebraicVarNames;
         xdot.reserve(nstates);
         xdotalgebraic.reserve(nstates);
         stateVarNames.reserve(nstates);
         SCIP_Real simplifyeps = SCIPepsilon(scip)*SCIPepsilon(scip);
         for( const MdlScipVar & var : vars )
         {
            if(simplify)
            {
               SCIP_CALL( SCIPexprSimplify(SCIPblkmem(scip), SCIPgetMessagehdlr(scip),
                                           varexprs[var.idx], simplifyeps,
                                           0, vars.size(), nullptr, nullptr, nullptr) );
            }
            switch( var.node->op )
            {
            case ExpressionGraph::INTEG:
               stateVarNames.emplace_back(var.name);
               if(simplify)
               {
                  SCIP_CALL( SCIPexprSimplify(SCIPblkmem(scip), SCIPgetMessagehdlr(scip),
                                              rate_expressions[var.idx], simplifyeps,
                                              0, nstates, nullptr, nullptr, nullptr) );
               }
               xdot.emplace_back(rate_expressions[var.idx]);
               if(simplify)
               {
                  SCIP_CALL( SCIPexprSimplify(SCIPblkmem(scip), SCIPgetMessagehdlr(scip),
                                              rate_expressions_algebraic[var.idx], simplifyeps,
                                              0, vars.size(), nullptr, nullptr, nullptr) );
               }
               xdotalgebraic.emplace_back(rate_expressions_algebraic[var.idx]);
               break;
            case ExpressionGraph::CONTROL:
               controlVarNames.emplace_back(var.name);
               break;
            default:
               algebraicVarNames.emplace_back(var.name);
            }
         }
         //copy expressions for algebraic variables so that they are not freed when finished reading
         std::size_t nalgebraic = varexprs.size()-algebraicStart;
         std::vector<SCIP_EXPR*> algebraicExpr(nalgebraic);
         for( std::size_t i = 0; i < nalgebraic; ++i )
            SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &algebraicExpr[i], varexprs[i+algebraicStart]) );

         controlVarNames.shrink_to_fit();
         structure->setXdot(std::move(xdot));
         structure->setXdotAlgebraic(std::move(xdotalgebraic));
         structure->setAlgebraicExpressions(std::move(algebraicExpr));
         structure->setControlVarNames(std::move(controlVarNames));
         structure->setStateVarNames(std::move(stateVarNames));
         structure->setAlgebraicVarNames(std::move(algebraicVarNames));
         structure->setTinit(initial_time);
         structure->setTfinal(final_time);
         structure->setTstep(time_step);

         //evaluate parameters for each timestep and store the values in the structure
         std::vector<SCIP_Real> xdotParams;
         rate_expr_params = expr_translator.getParameterNodes();

         xdotParams.reserve(rate_expr_params.size()*time_step_count);
         for( int t = 0; t < time_step_count; ++t )
         {
            SCIP_Real time = initial_time + t * time_step;

            for( auto node : rate_expr_params )
               xdotParams.emplace_back(exprGraph.evaluateNode(node, time));
         }

         structure->setXdotParams(std::move(xdotParams), rate_expr_params.size());
      } // varexprs vector has been build

      //setup mapping of scip variables to the variables for their rates
      //this information is required for multistep methods
      std::vector<std::vector<SCIP_VAR*>> scipvars;
      std::vector<int> ratevars(nstates);
      for( std::size_t i = 0; i < nstates; ++i )
      {
         for( std::size_t j = nstates; j < vars.size(); ++j )
         {
            if( vars[j].node == vars[i].node->child1 )
               ratevars[i] = j;
         }
      }
      //setup coefficients for adams bashforth linear multistep methods
      //of order 2 to 5
      SCIP_Real multistepcoeffs[4][7];
      multistepcoeffs[0][0] = -1.0;
      multistepcoeffs[0][1] = 1.0;
      multistepcoeffs[0][2] = time_step*1.5;
      multistepcoeffs[0][3] = -time_step*0.5;

      multistepcoeffs[1][0] = -1.0;
      multistepcoeffs[1][1] = 1.0;
      multistepcoeffs[1][2] = time_step*23.0/12.0;
      multistepcoeffs[1][3] = -time_step*4.0/3.0;
      multistepcoeffs[1][4] = time_step*5.0/12.0;

      multistepcoeffs[2][0] = -1.0;
      multistepcoeffs[2][1] = 1.0;
      multistepcoeffs[2][2] = time_step*55.0/24.0;
      multistepcoeffs[2][3] = -time_step*59.0/24.0;
      multistepcoeffs[2][4] = time_step*37.0/24.0;
      multistepcoeffs[2][5] = -time_step*3.0/8.0;

      multistepcoeffs[3][0] = -1.0;
      multistepcoeffs[3][1] = 1.0;
      multistepcoeffs[3][2] = time_step*1901.0/720.0;
      multistepcoeffs[3][3] = -time_step*1387.0/360.0;
      multistepcoeffs[3][4] = time_step*109.0/30.0;
      multistepcoeffs[3][5] = -time_step*637.0/360.0;
      multistepcoeffs[3][6] = time_step*251.0/720.0;

      //now create variables and contraints for each timestep
      for( int t = 0; t < time_step_count; ++t )
      {
         double time = initial_time + t * time_step;
         //string to append to variable names
         std::string timeString;
         {
            std::ostringstream stream;
            stream << "(" << t <<  ")";
            timeString = stream.str();
         }

         //create variables for this time
         scipvars.emplace_back(vars.size());
         for( const MdlScipVar & var : vars )
         {
            SCIP_VAR* scipvar;
            SCIP_Real objCoeff = var.lagrange_coeff;
            if(t + 1 == time_step_count)   // only if in last time step
               objCoeff += var.mayer_coeff;
            SCIP_Real lo = var.getLb(scip);
            SCIP_Real up = var.getUb(scip);
            switch( var.node->op )
            {
            case ExpressionGraph::CONTROL:
            {
               std::string name = var.name;
               int start, end;
               if( var.node->control_size == 0 )
               {
                  if( t > 0 )
                  {
                     scipvars[t][var.idx] =  scipvars[t-1][var.idx];
                     continue;
                  }

                  start = 0;
                  end = time_step_count - 1;
               }
               else
               {
                  if(t % var.node->control_size != 0)
                  {
                     scipvars[t][var.idx] =  scipvars[t-1][var.idx];
                     continue;
                  }
                  name += timeString;
                  start = t;
                  end = std::min(time_step_count - 1, t + var.node->control_size - 1);
               }

               SCIP_CALL( SCIPcreateVarBasic(scip, &scipvar, name.c_str(), lo, up, objCoeff, var.type) );
               SCIP_CALL( SCIPaddVar(scip, scipvar) );
               SCIP_CALL( structure->addControlVar(scipvar, SCIPvarGetIndex(scipvar), start, end, var.idx) );

               scipvars[t][var.idx] = scipvar;

               break;
            }
            case ExpressionGraph::INTEG:
            {
               if(positiveStates)
                  lo = 0;

               if( t == 0 && var.node->init == ExpressionGraph::CONSTANT_INIT ) {
                  lo = var.node->value;
                  up = var.node->value;
               }

               std::string name = var.name;
               name += timeString;
               SCIP_CALL( SCIPcreateVarBasic(scip, &scipvar, name.c_str(), lo, up, objCoeff, var.type) );
               SCIP_CALL( SCIPaddVar(scip, scipvar) );
               //SCIPdbgMsg("created variable %s with lb %e\n", name.c_str(), lo);
               SCIP_CALL( structure->addVariable(SCIPvarGetIndex(scipvar), scipvar, t, sdscip::SDproblemStructureInterface::STATE, var.idx) );

               scipvars[t][var.idx] = scipvar;
               break;
            }
            default:
            {
               std::string name = var.name;

               name += timeString;
               SCIP_CALL( SCIPcreateVarBasic(scip, &scipvar, name.c_str(),
                                            lo, up, objCoeff, var.type) );
               SCIP_CALL( SCIPaddVar(scip, scipvar) );
               SCIP_CALL( structure->addVariable(SCIPvarGetIndex(scipvar), scipvar, t, sdscip::SDproblemStructureInterface::ALGEBRAIC, var.idx) );

               scipvars[t][var.idx] = scipvar;
            }
            }
         }

         std::vector<SCIP_Real> params = expr_translator.getParameterValues(time);

         if( t == 0 )
         {
            for( const MdlScipVar & var : vars )
            {
               if( var.node->op != ExpressionGraph::INTEG )
                  break;
               if( var.node->init == ExpressionGraph::CONSTANT_INIT )
               {
                  SCIP_CALL( structure->addExplicitDifferential(nullptr, scipvars[t][var.idx], SCIPvarGetIndex(scipvars[t][var.idx]), 0, var.idx) );

                  /* This part confused scip debug sol mechanism, setting lo, up when creating var instead */
                  /*SCIP_Bool infeas;
                  SCIP_Bool fixed;
                  SCIP_CALL( SCIPfixVar(scip, scipvars[t][var.idx], var.node->value, &infeas, &fixed) );


                  assert(!infeas);
                  assert(fixed); */
               }
               else
               {
                  assert(var.node->init == ExpressionGraph::CONTROLED_INIT);
                  SCIP_EXPR* init;
                  SCIP_CALL( expr_translator.getScipExpr(var.node->child2, &init, true) );

                  SCIP_EXPRTREE* exprtree;
                  SCIP_CALL( SCIPexprtreeCreate(SCIPblkmem(scip), &exprtree, init, scipvars[t].size(), params.size(), params.data()) );
                  SCIP_CALL( SCIPexprtreeSetVars(exprtree, scipvars[t].size(), scipvars[t].data()) );

                  double linCoeff = -1.0;
                  double nlinCoeff = 1.0;
                  SCIP_CONS* cons;
                  std::string consname = var.name;
                  consname += " initial value";
                  SCIP_CALL( SCIPcreateConsBasicNonlinear(scip, &cons, consname.c_str(), 1, &scipvars[t][var.idx], &linCoeff, 1, &exprtree, &nlinCoeff, 0.0, 0.0) );
                  SCIP_CALL( SCIPexprtreeFree(&exprtree) );
                  SCIP_CALL( structure->addExplicitDifferential(cons, scipvars[t][var.idx], SCIPvarGetIndex(scipvars[t][var.idx]), 0, var.idx) );
                  SCIP_CALL( SCIPaddCons(scip, cons) );
                  SCIP_CALL( SCIPreleaseCons(scip, &cons) );
               }
            }
         }

         //create constraints for current time
         for( const MdlScipVar & var : vars )
         {
            switch( var.node->op )
            {
            case ExpressionGraph::CONTROL:
               continue;
            case ExpressionGraph::INTEG:
               if( t > 0 )
               {
                  int ms = std::min(t, multistep);
                  if( ms == 1 || ( t <= nsinglesteps ) )
                  {
                     std::vector<SCIP_Real> integParams = expr_translator.getParameterValues(initial_time + (t-1) * time_step);
                     SCIP_EXPR* root;
                     SCIP_EXPRTREE* exprtree;

                     //the exprtree will take ownership of root expression
                     //so create a copy and free the expression tree after the contraint
                     //is created.
                     SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &root, varexprs[var.idx]) );
                     SCIP_CALL( SCIPexprtreeCreate(SCIPblkmem(scip), &exprtree, root, scipvars[t-1].size(), integParams.size(), integParams.data()) );
                     SCIP_CALL( SCIPexprtreeSetVars(exprtree, scipvars[t-1].size(), scipvars[t-1].data()) );

                     double linCoeff = -1.0;
                     double nlinCoeff = 1.0;
                     SCIP_CONS* cons;
                     std::string consname = var.name;
                     consname += timeString;
                     consname += " ";
                     consname += discretization;
                     consname += " step";
                     SCIP_CALL( SCIPcreateConsBasicNonlinear(scip, &cons, consname.c_str(), 1, &scipvars[t][var.idx], &linCoeff, 1, &exprtree, &nlinCoeff, 0.0, 0.0) );
                     SCIP_CALL( SCIPexprtreeFree(&exprtree) );
                     SCIP_CALL( structure->addExplicitDifferential(cons, scipvars[t][var.idx], SCIPvarGetIndex(scipvars[t][var.idx]), t, var.idx) );
                     SCIP_CALL( SCIPaddCons(scip, cons) );
                     SCIP_CALL( SCIPreleaseCons(scip, &cons) );
                  }
                  else
                  {
                     int rateidx = ratevars[var.idx];
                     SCIP_VAR* consvars[7];
                     consvars[0] = scipvars[t][var.idx];
                     consvars[1] = scipvars[t-1][var.idx];
                     for( int i = 1; i <= ms; ++i )
                        consvars[i+1] = scipvars[t-i][rateidx];

                     SCIP_CONS* cons;
                     std::string consname = var.name;
                     consname += timeString;
                     consname += " multistep";
                     SCIP_CALL( SCIPcreateConsBasicLinear(scip, &cons, consname.c_str(), 2+ms, consvars, &multistepcoeffs[ms-2][0], 0.0, 0.0) );
                     SCIP_CALL( structure->addExplicitDifferential(cons, scipvars[t][var.idx], SCIPvarGetIndex(scipvars[t][var.idx]), t, var.idx) );
                     SCIP_CALL( SCIPaddCons(scip, cons) );
                     SCIP_CALL( SCIPreleaseCons(scip, &cons) );
                  }
               }
               continue;
            case ExpressionGraph::L:
            case ExpressionGraph::LE:
            case ExpressionGraph::G:
            case ExpressionGraph::GE:
            {
               SCIP_VAR* negvar;
               SCIP_VAR* binvar = scipvars[t][var.idx];
               SCIP_CALL( SCIPgetNegatedVar(scip, binvar, &negvar) );

               SCIP_Real lhstrue;
               SCIP_Real rhstrue;
               SCIP_Real lhsfalse;
               SCIP_Real rhsfalse;

               switch(var.node->op)
               {
                  case ExpressionGraph::GE:
                     lhstrue = 0.0;
                     rhstrue = SCIPinfinity(scip);
                     lhsfalse = -SCIPinfinity(scip);
                     rhsfalse = -SCIPfeastol(scip);
                     break;
                  case ExpressionGraph::G:
                     lhstrue = SCIPfeastol(scip);
                     rhstrue = SCIPinfinity(scip);
                     lhsfalse = -SCIPinfinity(scip);
                     rhsfalse = 0.0;
                     break;
                  case ExpressionGraph::L:
                     lhstrue = -SCIPinfinity(scip);
                     rhstrue = -SCIPfeastol(scip);
                     lhsfalse = 0.0;
                     rhsfalse = SCIPinfinity(scip);
                     break;
                  case ExpressionGraph::LE:
                     lhstrue = -SCIPinfinity(scip);
                     rhstrue = 0.0;
                     lhsfalse = SCIPfeastol(scip);
                     rhsfalse = SCIPinfinity(scip);
                     break;
                  default:
                     assert(false);
               }

               std::string consname = var.name;
               consname += timeString;

               std::string construenameind = consname+" true indiciator";
               std::string consfalsenameind  = consname+" false indicator";
               std::string construename = consname+" true cons";
               std::string consfalsename  = consname+" false cons";

               SCIP_CONS* construe;
               SCIP_CONS* consfalse;

               SCIP_CONS* construeind;
               SCIP_CONS* consfalseind;

               SCIP_EXPRTREE* exprtree;
               SCIP_EXPR* root;
               SCIP_EXPR* a;
               SCIP_EXPR* b;
               SCIP_CALL( expr_translator.getScipExpr(var.node->child1, &a, false, true) );
               SCIP_CALL( expr_translator.getScipExpr(var.node->child2, &b, false, true) );
               SCIP_CALL( SCIPexprCreate(SCIPblkmem(scip), &root, SCIP_EXPR_MINUS, a, b ) );

               if(false && simplify)
               {
                  std::vector<int> linidx(vars.size());
                  std::vector<SCIP_Real> lincoeffs(vars.size());
                  int nlinvars;
                  SCIP_CALL( SCIPexprSimplify(SCIPblkmem(scip), SCIPgetMessagehdlr(scip),
                                           root, SCIPepsilon(scip)*SCIPepsilon(scip),
                                           1, vars.size(), &nlinvars, linidx.data(), lincoeffs.data()) );
                  int nvars = 0;
                  SCIPexprGetVarsUsage(root, &nvars);
                  SCIPinfoMessage(scip, NULL, "nvars:%i  expr:%s polyconst:%f\n", nvars, SCIPexpropGetName(SCIPexprGetOperator(root)), SCIPexprGetPolynomialConstant(root) );
               }

               SCIP_CALL( SCIPexprtreeCreate(SCIPblkmem(scip), &exprtree, root, scipvars[t].size(), params.size(), params.data()) );
               SCIP_CALL( SCIPexprtreeSetVars(exprtree, scipvars[t].size(), scipvars[t].data()) );
               SCIP_Real nlinCoeff = 1.0;

               SCIP_CALL( SCIPcreateConsBasicNonlinear(scip, &construe, construename.c_str(),
                                                       0, nullptr, nullptr, 1, &exprtree, &nlinCoeff,
                                                       lhstrue, rhstrue) );
               SCIP_CALL( SCIPcreateConsBasicNonlinear(scip, &consfalse, consfalsename.c_str(),
                                                       0, nullptr, nullptr, 1, &exprtree, &nlinCoeff,
                                                       lhsfalse, rhsfalse) );
               SCIP_CALL( SCIPexprtreeFree(&exprtree) );

               SCIP_CALL( SCIPcreateConsBasicSuperindicator(scip, &construeind, construenameind.c_str(), binvar, construe) );
               SCIP_CALL( SCIPcreateConsBasicSuperindicator(scip, &consfalseind, consfalsenameind.c_str(), negvar, consfalse) );

               SCIP_CALL( SCIPaddCons(scip, construeind) );
               SCIP_CALL( SCIPaddCons(scip, consfalseind) );

               SCIP_CALL( SCIPreleaseCons(scip, &construe) );
               SCIP_CALL( SCIPreleaseCons(scip, &consfalse) );
               SCIP_CALL( SCIPreleaseCons(scip, &construeind) );
               SCIP_CALL( SCIPreleaseCons(scip, &consfalseind) );
               continue;
            }
            default:
               SCIP_EXPR* root;
               SCIP_EXPRTREE* exprtree;

               //the exprtree will take ownership of root expression
               //so create a copy and free the expression tree after the contraint
               //is created.
               SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &root, varexprs[var.idx]) );
               SCIP_CALL( SCIPexprtreeCreate(SCIPblkmem(scip), &exprtree, root, scipvars[t].size(), params.size(), params.data()) );
               SCIP_CALL( SCIPexprtreeSetVars(exprtree, scipvars[t].size(), scipvars[t].data()) );

               double linCoeff = -1.0;
               double nlinCoeff = 1.0;
               SCIP_CONS* cons;
               std::string consname = var.name;
               consname += timeString;
               consname += " definition";
               SCIP_CALL( SCIPcreateConsBasicNonlinear(scip, &cons, consname.c_str(), 1, &scipvars[t][var.idx], &linCoeff, 1, &exprtree, &nlinCoeff, 0.0, 0.0) );
               SCIP_CALL( SCIPexprtreeFree(&exprtree) );
               SCIP_CALL( structure->addAlgebraicCons(cons, scipvars[t][var.idx], t, var.idx, sdscip::SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS, var.idx) );
               SCIP_CALL( SCIPaddCons(scip, cons) );
               SCIP_CALL( SCIPreleaseCons(scip, &cons) );
               break;
            }
         }

      }
      //now release all the variables that were created
      for( int t = 0; t < time_step_count; ++t )
      {
         for( size_t i = 0; i < scipvars[t].size(); ++i )
         {
            if( !scipvars[t][i] )
               continue;
            if( vars[i].node->op == ExpressionGraph::CONTROL )
            {
               if(vars[i].node->control_size == 0 && t > 0)
                  continue;
               if( t % vars[i].node->control_size != 0)
                  continue;
            }

            SCIP_CALL( SCIPreleaseVar(scip, &scipvars[t][i]) );
         }
      }
      //and free the expressions
      for( std::size_t i = 0; i < varexprs.size(); ++i )
         SCIPexprFreeDeep(SCIPblkmem(scip), &varexprs[i]);
      //set the objective sense as specified in vpd file
      SCIP_CALL( SCIPsetObjsense(scip, objective.isMaximized() ? SCIP_OBJSENSE_MAXIMIZE : SCIP_OBJSENSE_MINIMIZE) );
      //now inform structure that reading is down and check it if the parameter is set
      SCIP_CALL( structure->doneReading() );
      SCIP_Bool check;
      SCIP_CALL( SCIPgetBoolParam(scip , "reading/sdoreader/checkStructure", &check) );
      if( check )
      {
         SCIPinfoMessage(scip, NULL, "\n=== Performing structure checks ===\n");
         SCIP_CALL( SDcheckStructure(scip) );
      }

      SCIP_Bool printSummary(true);
      SCIP_CALL( SCIPgetBoolParam(scip ,"reading/sdoreader/printSummary", &printSummary) );
      if( printSummary)
      {
         SCIP_CALL( SDprintStructureSummary(scip) );
      }

      /* Read additional bounds into problem */
      try
      {
         if( !sdoFile.getBoundFile().empty() )
         {
            SCIPinfoMessage(scip, NULL, "Reading additional bounds from %s\n", sdoFile.getBoundFile().c_str());
            SCIPreadProb(scip, sdoFile.getBoundFile().c_str(), "bnd");
         }
      }
      catch(const std::ios_base::failure& err)
      {
         SCIPerrorMessage("Failed opening file: %s\n", sdoFile.getObjectiveFile().c_str());
         return SCIP_NOFILE;
      }

      *result = SCIP_SUCCESS;
      return SCIP_OKAY;
   }
   catch(const std::exception& err)
   {
      //could be some parse error or io error
      //parse errors will have a meaningful error message
      //so just print it
      SCIPerrorMessage(err.what());
      return SCIP_READERROR;
   }
}

SCIP_DECL_READERWRITE(sdo::ReaderSDO::scip_write)
{
   *result = SCIP_DIDNOTRUN;

   return SCIP_OKAY;
}



