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

/**@file    SDCons.cpp
 * @brief   class representing sd constraint
 * @author  Robert L. Gottwald
 *
 */


#include "SDCons.h"
#include <scip/cons_linear.h>
#include <scip/cons_nonlinear.h>

SCIP_RETCODE CreateMinMaxCons( SCIP* scip, SDCons* sdcons, SDConsType type, SCIP_VAR* forward_var, SCIP_VAR* arg0, SCIP_VAR* arg1 )
{
   assert(type == SDConsType::MIN || type == SDConsType::MAX);
   *sdcons = SDCons();
   SDMinMax* minmax = new SDMinMax;
   sdcons->cons_minmax_ = minmax;
   sdcons->type_ = type;
   //init vars
   minmax->arg0 = arg0;
   minmax->arg1 = arg1;
   SCIP_CALL( SCIPcreateVarBasic(scip, &(minmax->select), nullptr, 0.0, 1.0, 0.0, SCIP_VARTYPE_BINARY) );
   SCIP_CALL( SCIPcreateVarBasic(scip, &(minmax->pos0), nullptr, 0.0, SCIPinfinity(scip), 0.0, SCIP_VARTYPE_CONTINUOUS) );
   SCIP_CALL( SCIPcreateVarBasic(scip, &(minmax->neg0), nullptr, 0.0, SCIPinfinity(scip), 0.0, SCIP_VARTYPE_CONTINUOUS) );
   SCIP_CALL( SCIPcreateVarBasic(scip, &(minmax->pos1), nullptr, 0.0, SCIPinfinity(scip), 0.0, SCIP_VARTYPE_CONTINUOUS) );
   SCIP_CALL( SCIPcreateVarBasic(scip, &(minmax->neg1), nullptr, 0.0, SCIPinfinity(scip), 0.0, SCIP_VARTYPE_CONTINUOUS) );

   { //split in pos and neg
      double c[] = {1.0, -1.0, -1.0};
      SCIP_VAR* split_vars_arg0[] = {minmax->pos0, minmax->neg0, arg0};
      SCIP_CALL( SCIPcreateConsBasicLinear(scip, &(minmax->split0), nullptr, 3, split_vars_arg0, c, 0.0, 0.0) );
      SCIP_VAR* split_vars_arg1[] = {minmax->pos1, minmax->neg1, arg1};
      SCIP_CALL( SCIPcreateConsBasicLinear(scip, &(minmax->split1), nullptr, 3, split_vars_arg1, c, 0.0, 0.0) );
   }

   double nonlincoeff = 1.0;
   SCIP_EXPR* one;

   { 
      SCIP_EXPR* select0;
      SCIP_EXPR* select1;
      SCIP_EXPR* V0PlusV1;
      SCIP_EXPR* V3PlusV4;
      SCIP_EXPR* vars[5];
      SCIP_EXPR* oneMinusV2;

      for(int i=0; i<5; ++i)
      {
         SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &vars[i], SCIP_EXPR_VARIDX, i ) );
      }

      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &V0PlusV1, SCIP_EXPR_PLUS, vars[0], vars[1]) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &V3PlusV4, SCIP_EXPR_PLUS, vars[3], vars[4]) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &one, SCIP_EXPR_CONST, 1.0) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &oneMinusV2, SCIP_EXPR_MINUS, one, vars[2]) );

      {
         SCIP_EXPR* tmp;
         SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &tmp, SCIP_EXPR_MUL, oneMinusV2, V3PlusV4) );
         SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &select0, SCIP_EXPR_MINUS, V0PlusV1, tmp) );

         SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &tmp, SCIP_EXPR_MUL, vars[2], V3PlusV4) );
         SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &select1, SCIP_EXPR_MINUS, V0PlusV1, tmp) );
      }

      SCIP_EXPRTREE* expr_tree_s0;
      SCIP_EXPRTREE* expr_tree_s1;
      SCIP_CALL( SCIPexprtreeCreate( SCIPblkmem( scip ), &expr_tree_s0, select0, 5, 0, nullptr ) );
      SCIP_CALL( SCIPexprtreeCreate( SCIPblkmem( scip ), &expr_tree_s1, select1, 5, 0, nullptr ) );

      //this variable assignment for the expression tree yields the constraint arg0 <= arg1:
      //      arg0 <= arg1
      // <->  pos0-neg0 <= pos1-neg1
      // <->  pos0+neg1 <= pos1+neg0
      // <->  0 <= pos1+neg0 - (pos0+neg1) <= inf
      // and now with the binary variable select:
      //      0 <= pos1+neg0 - select*(pos0+neg1) <= inf
      // the constraint is always valid for select = 0 since
      // then we got
      //     0 <= pos1+neg0 <= inf
      // which is true since pos1 and neg0 are both positive variables.
      // but if select is one arg0 <= arg1 must hold.
      // Together with the constraint
      //  0 <= pos0+neg1 - (1-select)*(pos1+neg0) <= inf
      // select is constrained to 1 if arg0 <= arg1 and it is contrained to
      // 0 if arg1 <= arg0.

      SCIP_VAR* arg0_LE_arg1[] = {minmax->pos1, minmax->neg0, minmax->select, minmax->pos0, minmax->neg1};
      SCIP_VAR* arg1_LE_arg0[] = {minmax->pos0, minmax->neg1, minmax->select, minmax->pos1, minmax->neg0};

      if(type == SDConsType::MIN)
      { 
         //in case of minimum arg0 is selected if arg0 <= arg1
         SCIP_CALL( SCIPexprtreeSetVars(expr_tree_s0, 5, arg0_LE_arg1) );
         //and arg1 is selected if arg1 <= arg0
         SCIP_CALL( SCIPexprtreeSetVars(expr_tree_s1, 5, arg1_LE_arg0) );
      }
      else
      {
         SCIP_CALL( SCIPexprtreeSetVars(expr_tree_s0, 5, arg1_LE_arg0) );
         SCIP_CALL( SCIPexprtreeSetVars(expr_tree_s1, 5, arg0_LE_arg1) );
      }
      SCIP_CALL( SCIPcreateConsBasicNonlinear( scip, &(minmax->select0_cons), nullptr, 0, nullptr, nullptr, 1, &expr_tree_s0, &nonlincoeff, 0.0, SCIPinfinity(scip) ) );
      SCIP_CALL( SCIPcreateConsBasicNonlinear( scip, &(minmax->select1_cons), nullptr, 0, nullptr, nullptr, 1, &expr_tree_s1, &nonlincoeff, 0.0, SCIPinfinity(scip) ) );
   }

   { //now put together main constraint to set value of forward var to max(arg0,arg1) or min(arg0,arg1) respectively.
      SCIP_EXPR* expr_tmp;
      SCIP_EXPRTREE *tree_tmp;
      SCIP_EXPR* arg0expr;
      SCIP_EXPR* arg1expr;
      SCIP_EXPR* selectexpr;
      SCIP_EXPR* one_minus_selectexpr;
      SCIP_EXPR* arg0select;
      SCIP_EXPR* arg1select;
      //create expression for variables
      SCIP_VAR* exprvars[] = {minmax->arg0, minmax->arg1, minmax->select};
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &arg0expr, SCIP_EXPR_VARIDX, 0) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &arg1expr, SCIP_EXPR_VARIDX, 1) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &selectexpr, SCIP_EXPR_VARIDX, 2) );
      //create expr_tmp = arg0*(1-select) + arg1*select
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &one_minus_selectexpr, SCIP_EXPR_MINUS, one, selectexpr) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &arg0select, SCIP_EXPR_MUL, arg0, one_minus_selectexpr) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &arg1select, SCIP_EXPR_MUL, arg1, selectexpr) );
      SCIP_CALL( SCIPexprCreate(SCIPblkmem( scip ), &expr_tmp, SCIP_EXPR_PLUS, arg0select, arg1select) );
      SCIP_CALL( SCIPexprtreeCreate(SCIPblkmem( scip ), &tree_tmp, expr_tmp, 3, 0, nullptr) );
      //create expression tree
      SCIP_CALL( SCIPexprtreeSetVars(tree_tmp, 3, exprvars) );
      //create cons:    0 <=  1.0*tree_tmp  - 1.0*forward_var <= 0
      double lincoeff = -1.0;
      SCIP_CALL( SCIPcreateConsBasicNonlinear( scip, &(minmax->cons), nullptr, 1, &forward_var, &lincoeff, 1, &tree_tmp, &nonlincoeff, 0.0, 0.0 ) );
   }

   return SCIP_OKAY;
}
