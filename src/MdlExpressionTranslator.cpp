#include "MdlExpressionTranslator.h"
#include "ExprLookup.h"
#include "ExprPiecewiseLinear.h"
#include <boost/make_shared.hpp>

SCIP_RETCODE MdlExpressionTranslator::getScipExpr( sdo::ExpressionGraph::Node *root, SCIP_EXPR **expr, bool initial, bool allowrootvar )
{
   //works like a shift reduce parser
   std::stack<sdo::ExpressionGraph::Node *> node_stack;
   std::stack<SCIP_EXPR *> expr_stack;
   std::stack<int> expr_stack_offset;
   sdo::ExpressionGraph::Node *node = root;
   int offset = 0;

   auto pop_expr = [&]()
   {
      SCIP_EXPR *e = expr_stack.top();
      SCIP_EXPR* copy;
      SCIP_CALL_ABORT( SCIPexprCopyDeep(SCIPblkmem(scip), &copy, e) );
      expr_stack.pop();
      return copy;
   };

   auto pop_node = [&]()
   {
      if( node_stack.empty() )
      {
         return false;
      }

      node = node_stack.top();
      node_stack.pop();
      offset = expr_stack_offset.top();
      expr_stack_offset.pop();
      return true;
   };

   auto push_expr = [&]()
   {
      expr_stack.push( *expr );
      expressions[node] = *expr;
   };

   do
   {
      //if node is not the root and has a variable then use the variable expression
      if( node != root || allowrootvar )
      {
         auto i = vars.find( node );

         if( i != vars.end() )
         {
            *expr = i->second;
            expr_stack.push( *expr );
            continue;
         }
      }

      //if node expr is already translated use the known expression
      auto i = expressions.find( node );

      if( i != expressions.end() )
      {
         *expr = i->second;
         expr_stack.push( *expr );
         continue;
      }

      //else translate expression
      switch( node->type )
      {
      case sdo::ExpressionGraph::UNKNOWN:
         SCIPerrorMessage("unkown type of expression at ...");
         for( auto & usage : node->usages )
            std::cerr <<  "\t" << usage << "\n";
         return SCIP_READERROR;

      case sdo::ExpressionGraph::CONSTANT_NODE:
         //reduce with const value
         SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_CONST, node->value ) );
         push_expr();
         continue;

      case sdo::ExpressionGraph::STATIC_NODE:
      {
         if( initial )
         {
            SCIP_Real initial_time = exprGraph.getNode( sdo::Symbol( "INITIAL TIME" ) )->value;
            SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_CONST, exprGraph.evaluateNode( node, initial_time, true ) ) );
            push_expr();
            continue;
         }

         auto entry = parameters.find( node );
         int idx;

         if( entry == parameters.end() )
         {
            idx = parameters.size();
            parameters[node] = idx;
         }
         else
         {
            idx = entry->second;
         }

         SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_PARAM, idx ) );
         push_expr();
         //reduce with parameter
         continue;
      }
      case sdo::ExpressionGraph::DYNAMIC_NODE:

         //check if enough expressions are on the exprstack to reduce
         //  if yes -> reduce exprstack;
         //  if not -> shift node and then its childs on node_stack

         switch( node->op )
         {
         case sdo::ExpressionGraph::INTEG:
         {
            auto i = vars.find( node );

            if( i != vars.end() )
            {
               *expr = i->second;
               expr_stack.push( *expr );
            }
            else
            {
               assert(false); // integ node should have a symbol
            }

            continue;
         }

         case sdo::ExpressionGraph::ACTIVE_INITIAL:
            if( initial )
               node_stack.push( node->child2 );
            else
               node_stack.push( node->child1 );

            expr_stack_offset.push(offset);

            continue;

         case sdo::ExpressionGraph::ABS:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_ABS, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::COS:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_COS, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::EXP:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_EXP, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::LN:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_LOG, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::UMINUS:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_EXPR *child = pop_expr();
               double coeff = -1;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), expr, 1, &child, &coeff, 0.0 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::SIN:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_SIN, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::SQRT:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_SQRT, pop_expr() ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::TAN:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_TAN, pop_expr() ) );
               push_expr();
            }

            continue;


         case sdo::ExpressionGraph::DIV:
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_DIV, child1, child2 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::LOG:
         {
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_EXPR *arg;
               SCIP_EXPR *base;
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &arg, SCIP_EXPR_LOG, child1 ) );
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &base, SCIP_EXPR_LOG, child2 ) );
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_DIV, arg, base ) );
               expr_stack.push( *expr );
            }

            continue;
         }

         case sdo::ExpressionGraph::MAX:
         {
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MAX, child1, child2 ) );
               push_expr();
            }

            continue;
         }

         case sdo::ExpressionGraph::MIN:
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MIN, child1, child2 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::MINUS:
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MINUS, child1, child2 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::AND:
         case sdo::ExpressionGraph::MULT:
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();

               if( node->child1 == node->child2 )
               {
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_SQUARE, child1 ) );
               }
               else
               {
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MUL, child1, child2 ) );
               }

               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::PLUS:
            if( int(expr_stack.size()) - offset < 2 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_PLUS, child1, child2 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::POWER:
            if( node->child2->type != sdo::ExpressionGraph::CONSTANT_NODE )
            {
               return SCIP_ERROR;
            }

            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               //else reduce the expr stack with the corresponding scip expression
               SCIP_EXPR *base = pop_expr();
               double exponent = node->child2->value;
               double intpart;

               //if fractional part is zero and the value represent fits in an integer use INTPOWER else use REALPOWER
               if( SCIPisZero( scip, std::modf( exponent, &intpart ) ) && intpart <= std::numeric_limits<int>::max() )
               {
                  int intexp = static_cast<int>( intpart );

                  //simplify if exponent is 0,1 or 2 else use INTPOWER
                  switch( intexp )
                  {
                  case 0:
                     SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_CONST, 1.0 ) );
                     break;

                  case 1:
                     *expr = base;
                     break;

                  case 2:
                     SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_SQUARE, base ) );
                     break;

                  default:
                     SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_INTPOWER, base, intexp ) );
                  }
               }
               else
               {
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_REALPOWER, base, exponent ) );
               }

               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::IF:
            if( int(expr_stack.size()) - offset < 3 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 2);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child2 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child3 );
            }
            else
            {
               SCIP_EXPR *cond = pop_expr();
               SCIP_EXPR *then_val = pop_expr();
               SCIP_EXPR *else_val = pop_expr();
               SCIP_EXPR *not_cond;
               SCIP_Real coeff = -1;
               SCIP_EXPR *then_summand;
               SCIP_EXPR *else_summand;
               SCIP_EXPR* condcopy;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), &not_cond, 1, &cond, &coeff, 1 ) );
               SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &condcopy, cond) );
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &then_summand, SCIP_EXPR_MUL, condcopy, then_val ) );
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &else_summand, SCIP_EXPR_MUL, not_cond, else_val ) );
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_PLUS, then_summand, else_summand ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::G:
            if( int(expr_stack.size()) - offset < 2 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //    a > b
               //<=> !(a <= b)
               //<=> !(b-a >= 0)

               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_EXPR *diff;
               SCIP_EXPR *sign;

               //diff = b-a
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, child2, child1 ) );
               //sign = sign(b-a)
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
               //if b-a >= 0 <=> !(a > b) then sign is +1 and the value is  -0.5*1+0.5 = 0
               //if b-a < 0 <=> a > b then sign is -1 and the value is  -0.5*-1+0.5 = 1
               SCIP_Real coeff = -0.5;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  expr, 1, &sign, &coeff, 0.5 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::GE:
            if( int(expr_stack.size()) - offset < 2 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //    a >= b
               //<=> a-b >= 0

               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_EXPR *diff;
               SCIP_EXPR *sign;

               //diff = a-b
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, child1, child2 ) );
               //sign = sign(a-b)
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
               //if a-b >= 0 <=> a >= b then sign is +1 and the value is  0.5*1+0.5 = 1
               //if a-b < 0 <=> a < b then sign is -1 and the value is  0.5*-1+0.5 = 0
               SCIP_Real coeff = 0.5;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  expr, 1, &sign, &coeff, 0.5 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::L:
            if( int(expr_stack.size()) - offset < 2 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //    a < b
               //<=> !(a >= b)
               //<=> !(a-b >= 0)

               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_EXPR *diff;
               SCIP_EXPR *sign;

               //diff = a-b
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, child1, child2 ) );
               //sign = sign(a-b)
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
               //if a-b >= 0 <=> a >= b then sign is +1 and the value is  -0.5*1+0.5 = 0
               //if a-b < 0 <=> a < b then sign is -1 and the value is  -0.5*-1+0.5 = 1
               SCIP_Real coeff = -0.5;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  expr, 1, &sign, &coeff, 0.5 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::LE:
            if( int(expr_stack.size()) - offset < 2 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size() + 1);
               node_stack.push( node->child1 );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               //    a <= b
               //<=> b-a >= 0

               SCIP_EXPR *child1 = pop_expr();
               SCIP_EXPR *child2 = pop_expr();
               SCIP_EXPR *diff;
               SCIP_EXPR *sign;

               //diff = b-a
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, child2, child1 ) );
               //sign = sign(b-a)
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
               //if b-a >= 0 <=> a <= b then sign is +1 and the value is 0.5*1+0.5 = 1
               //if b-a < 0 <=> a > b then sign is -1 and the value is 0.5*-1+0.5 = 0
               SCIP_Real coeff = 0.5;
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), expr, 1, &sign, &coeff, 0.5 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::OR:
            if( int(expr_stack.size()) - offset < 2 )
            {
               expr_stack_offset.push( offset );
               node_stack.push( node );
               expr_stack_offset.push( expr_stack.size() + 1 );
               node_stack.push( node->child1 );
               expr_stack_offset.push( expr_stack.size() );
               node_stack.push( node->child2 );
            }
            else
            {
               //    a || b
               //<=> ! ( !a && !b )
               //<=> 1 - ( (1-a) * (1-b) )
               //<=> 1 - ( (1-a) * (1-b) )
               //<=> a + b - ab

               SCIP_EXPR *array[3];
               array[0] = pop_expr();
               array[1] = pop_expr();
               SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &array[2], SCIP_EXPR_MUL, array[0], array[1] ) );

               SCIP_Real coeffs[] = {1.0, 1.0, -1.0};
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), expr, 3, array, coeffs, 0.0 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::NOT:
            if( int(expr_stack.size()) - offset < 1 )
            {
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child1 );
            }
            else
            {
               SCIP_EXPR *child = pop_expr();
               SCIP_Real coeff = -1;
               //1-child
               SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), expr, 1, &child, &coeff, 1 ) );
               push_expr();
            }

            continue;

         case sdo::ExpressionGraph::TIME:
            assert(false);
            continue;
         case sdo::ExpressionGraph::CONSTANT:
         {
            assert(false);
            continue;
         }

         case sdo::ExpressionGraph::EQ:
            SCIPerrorMessage("'=' comparison operator on dynamic arguments not implemented yet. Used at ...\n");
            for( auto & usage : node->usages )
               std::cerr <<  "\t" << usage << "\n";
            return SCIP_READERROR;

         case sdo::ExpressionGraph::NEQ:
            SCIPerrorMessage("'<>' comparison operator on dynamic arguments not implemented yet. Used at ...\n");
            for( auto & usage : node->usages )
               std::cerr <<  "\t" << usage << "\n";
            return SCIP_READERROR;

         case sdo::ExpressionGraph::STEP:
            if( true )
            {
               SCIPerrorMessage( "'STEP' function on dynamic arguments not implemented yet. Used at ...\n" );

               for( auto & usage : node->usages )
                  std::cerr <<  "\t" << usage << "\n";

               return SCIP_READERROR;
            }
            else
            {
               if( int( expr_stack.size() ) - offset < 2 )
               {
                  expr_stack_offset.push( offset );
                  node_stack.push( node );
                  expr_stack_offset.push( expr_stack.size() + 1 );
                  node_stack.push( node->child1 );
                  expr_stack_offset.push( expr_stack.size() );
                  node_stack.push( node->child2 );
               }
               else
               {
                  //    a > b
                  //<=> !(a <= b)
                  //<=> !(b-a >= 0)
                  SCIP_EXPR *array[2];
                  SCIP_Real coeffs[] = {1.0, 0.5};
                  SCIP_EXPR *time_plus;
                  SCIP_EXPR *height = pop_expr();
                  SCIP_EXPR *step_time = pop_expr();
                  SCIP_EXPR *diff;
                  SCIP_EXPR *sign;
                  SCIP_EXPR *step;

                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &array[0], SCIP_EXPR_PARAM, 0 ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &array[1], SCIP_EXPR_PARAM, 1 ) );

                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), &time_plus, 2, array, coeffs, 0.0 ) );
                  //diff = b-a
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, step_time, time_plus ) );
                  //sign = sign(b-a)
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
                  //if b-a >= 0 <=> !(a > b) then sign is +1 and the value is  -0.5*1+0.5 = 0
                  //if b-a < 0 <=> a > b then sign is -1 and the value is  -0.5*-1+0.5 = 1
                  SCIP_Real coeff = -0.5;
                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  &step, 1, &sign, &coeff, 0.5 ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MUL, height, step ) );
                  push_expr();
               }

               continue;
            }

         case sdo::ExpressionGraph::RAMP:
            if( true )
            {
               SCIPerrorMessage( "'RAMP' function on dynamic arguments not implemented yet. Used at ...\n" );

               for( auto & usage : node->usages )
                  std::cerr <<  "\t" << usage << "\n";

               return SCIP_READERROR;
            }
            else
            {
               if( int( expr_stack.size() ) - offset < 3 )
               {
                  expr_stack_offset.push( offset );
                  node_stack.push( node );
                  expr_stack_offset.push( expr_stack.size() + 2 );
                  node_stack.push( node->child1 );
                  expr_stack_offset.push( expr_stack.size() + 1 );
                  node_stack.push( node->child2 );
                  expr_stack_offset.push( expr_stack.size() );
                  node_stack.push( node->child3 );
               }
               else
               {
                  //    a > b
                  //<=> !(a <= b)
                  //<=> !(b-a >= 0)

                  SCIP_EXPR *slope = pop_expr();
                  SCIP_EXPR *starttime = pop_expr();
                  SCIP_EXPR *endtime = pop_expr();

                  SCIP_EXPR *time;
                  SCIP_EXPR *mintimeendtime;
                  SCIP_EXPR *diff;
                  SCIP_EXPR *sign;
                  SCIP_EXPR *a;
                  SCIP_EXPR *val;
                  SCIP_EXPR *cond;
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &time, SCIP_EXPR_PARAM, 0 ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &mintimeendtime, SCIP_EXPR_MIN, time, endtime ) );

                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &a, SCIP_EXPR_MINUS, mintimeendtime, starttime ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &val, SCIP_EXPR_MUL, slope, a ) );

                  //diff = b-a
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, starttime, time ) );
                  //sign = sign(b-a)
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
                  //if b-a >= 0 <=> !(a > b) then sign is +1 and the value is  -0.5*1+0.5 = 0
                  //if b-a < 0 <=> a > b then sign is -1 and the value is  -0.5*-1+0.5 = 1
                  SCIP_Real coeff = -0.5;
                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), &cond, 1, &sign, &coeff, 0.5 ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MUL, val, cond ) );
                  push_expr();
               }

               continue;
            }

         case sdo::ExpressionGraph::PULSE:
            if( true )
            {
               SCIPerrorMessage( "'PULSE' function on dynamic arguments not implemented yet. Used at ...\n" );

               for( auto & usage : node->usages )
                  std::cerr <<  "\t" << usage << "\n";

               return SCIP_READERROR;
            }
            else
            {
               if( int( expr_stack.size() ) - offset < 2 )
               {
                  expr_stack_offset.push( offset );
                  node_stack.push( node );
                  expr_stack_offset.push( expr_stack.size() + 1 );
                  node_stack.push( node->child1 );
                  expr_stack_offset.push( expr_stack.size() );
                  node_stack.push( node->child2 );
               }
               else
               {
                  //    a > b
                  //<=> !(a <= b)
                  //<=> !(b-a >= 0)
                  SCIP_EXPR *array[2];
                  SCIP_Real coeffs[] = {1.0, 0.5};
                  SCIP_EXPR *time_plus;
                  SCIP_EXPR *start = pop_expr();
                  SCIP_EXPR *width = pop_expr();
                  SCIP_EXPR *diff;
                  SCIP_EXPR *sign;
                  SCIP_EXPR *startpluswidth;
                  SCIP_EXPR *tpgtstart;
                  SCIP_EXPR *tpltstartpluswidth;

                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &startpluswidth, SCIP_EXPR_PLUS, start, width ) );

                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &array[0], SCIP_EXPR_PARAM, 0 ) );
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &array[1], SCIP_EXPR_PARAM, 1 ) );

                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ), &time_plus, 2, array, coeffs, 0.0 ) );
                  //diff = b-a
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, start, time_plus ) );
                  //sign = sign(b-a)
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
                  //if b-a >= 0 <=> !(a > b) then sign is +1 and the value is  -0.5*1+0.5 = 0
                  //if b-a < 0 <=> a > b then sign is -1 and the value is  -0.5*-1+0.5 = 1
                  SCIP_Real coeff = -0.5;
                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  &tpgtstart, 1, &sign, &coeff, 0.5 ) );

                  //diff = b-a
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &diff, SCIP_EXPR_MINUS, time_plus, startpluswidth ) );
                  //sign = sign(b-a)
                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &sign, SCIP_EXPR_SIGN, diff ) );
                  //if b-a >= 0 <=> !(a > b) then sign is +1 and the value is  -0.5*1+0.5 = 0
                  //if b-a < 0 <=> a > b then sign is -1 and the value is  -0.5*-1+0.5 = 1
                  SCIP_CALL( SCIPexprCreateLinear( SCIPblkmem( scip ),  &tpltstartpluswidth, 1, &sign, &coeff, 0.5 ) );

                  SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), expr, SCIP_EXPR_MUL, tpltstartpluswidth, tpgtstart ) );
                  push_expr();
               }

               continue;
            }

         case sdo::ExpressionGraph::PULSE_TRAIN:
            SCIPerrorMessage("'PULSE TRAIN' function on dynamic arguments not implemented yet. Used at ...\n");
            for( auto & usage : node->usages )
               std::cerr <<  "\t" << usage << "\n";
            return SCIP_READERROR;

         case sdo::ExpressionGraph::APPLY_LOOKUP:
            if( int(expr_stack.size()) - offset < 1 )
            {
               //if not enough nodes are on the expr stack then shift the childs on the node_stack
               expr_stack_offset.push(offset);
               node_stack.push( node );
               expr_stack_offset.push(expr_stack.size());
               node_stack.push( node->child2 );
            }
            else
            {
               auto it = lkpMap.find( node->child1 );

               if( it == lkpMap.end() )
               {
                  /* Create an identifier form first usage */
                  assert(node->usages.size() >= 1);

                  std::string identifier = std::to_string(node->usages[0].second.first_line) + std::string(":") + std::to_string(node->usages[0].second.first_column);
                  SCIPdbgMsg("identifier is %s\n", identifier.c_str());
                  auto pcwlin = boost::make_shared<spline::BSplineCurve<1, SCIP_Real>>(
                     node->child1->lookup_table->getXvals(), node->child1->lookup_table->getYvals());
                  SCIP_CALL( SCIPexprCreatePiecewiseLinear( SCIPblkmem( scip ), expr, pop_expr(), pcwlin , identifier) );
               }
               else
               {
                  SCIP_CALL( SCIPexprCreateLookup( SCIPblkmem( scip ), expr, pop_expr(), it->second ) );
               }
               push_expr();
            }

            continue;

         default:
            SCIPerrorMessage("function/operator (id:%d) not implemented yet. Used at ...\n", node->op);
            for( auto & usage : node->usages )
               std::cerr <<  "\t" << usage << "\n";
            return SCIP_READERROR;

         } //end switch node op

         //end case dynamic node
      } //end switch node type

   }
   while( pop_node() );


   assert( expr_stack.size() == 1 );
   *expr = pop_expr(); //return a copy
   return SCIP_OKAY;
}

SCIP_RETCODE MdlExpressionTranslator::setVars( const std::vector< MdlScipVar > &vec )
{
   for( const MdlScipVar & var : vec )
   {
      SCIP_EXPR* expr;
      SCIP_CALL( SCIPexprCreate( SCIPblkmem( scip ), &expr, SCIP_EXPR_VARIDX, var.idx ) );

      auto it = vars.find(var.node);
      if( it != vars.end() )
         SCIPexprFreeDeep(SCIPblkmem(scip), &(it->second));

      vars[var.node] = expr;
   }

   for(std::pair<sdo::ExpressionGraph::Node*, SCIP_EXPR*> nodeexprpair : expressions )
       SCIPexprFreeDeep(SCIPblkmem(scip), &nodeexprpair.second);

   expressions.clear();
   return SCIP_OKAY;
}

SCIP_RETCODE MdlExpressionTranslator::setVars( const std::vector< MdlScipVar > &vec, const std::vector< SCIP_EXPR * > &varexpr )
{
   for( const MdlScipVar & var : vec )
   {
      SCIP_EXPR* copy;
      SCIP_CALL( SCIPexprCopyDeep(SCIPblkmem(scip), &copy, varexpr[var.idx]) );

      auto it = vars.find(var.node);
      if( it != vars.end() )
         SCIPexprFreeDeep(SCIPblkmem(scip), &(it->second));

      vars[var.node] = copy;
   }

   for(std::pair<sdo::ExpressionGraph::Node*, SCIP_EXPR*> nodeexprpair : expressions )
      SCIPexprFreeDeep(SCIPblkmem(scip), &nodeexprpair.second);

   expressions.clear();
   return SCIP_OKAY;
}

SCIP_EXPR *MdlExpressionTranslator::getVarExpr( sdo::ExpressionGraph::Node *node )
{
   return vars[node];
}

std::vector<MdlScipVar> MdlExpressionTranslator::createVariableMapping( const sdo::Objective &objective, bool minimal, bool cmpvar, bool ratealgebraic, bool isolatelookups )
{
   using namespace sdo;

   std::unordered_set<MdlScipVar> states;
   std::unordered_set<MdlScipVar> controls;
   std::unordered_set<MdlScipVar> comparisons;
   std::unordered_set<MdlScipVar> algebraic;
   std::unordered_set<sdo::ExpressionGraph::Node*> positive;

   //for each symbol walk in the expression graph to find possibly hidden states
   for( auto & entry : exprGraph.getSymbolTable() )
   {
      std::stack<ExpressionGraph::Node *> stack;
      std::stack<ExpressionGraph::Node *> state_stack;
      stack.emplace( entry.second );

      SCIP_Real mayer_coeff = 0.0;
      SCIP_Real lagrange_coeff = 0.0;

      for( const Objective::Summand & s : objective.getSummands() )
      {
         if( s.variable == entry.first )
         {
            if( s.type == Objective::Summand::LAGRANGE )
               lagrange_coeff += s.coefficient;
            else if( s.type == Objective::Summand::MAYER )
               mayer_coeff += s.coefficient;
         }
      }

      int cmp = 0;
      int lkp = 0;
      int lkparg = 0;
      int pos = 0;
      bool isSelf = (entry.second == stack.top());
      while( !stack.empty() )
      {
         ExpressionGraph::Node *node = stack.top();
         stack.pop();

         //if the node is not the root node of the current entry and has a symbol then
         //skip this subtree as it will have an own entry in the symbol table
         if( !isSelf && !exprGraph.getSymbol( node ).empty() && positive.find(node) == positive.end() )
            continue;
         isSelf = false;

         //now walk expression graph from the current node
         switch( node->op )
         {
         case ExpressionGraph::INTEG:
            //if a state is found then add it to the state_stack
            //and walk its child nodes to find states that have no symbols
            //coming from smooth or delay operands.
            state_stack.emplace( node );
            stack.emplace( node->child2 );
            stack.emplace( node->child1 );
            continue;

         case ExpressionGraph::G:
         case ExpressionGraph::GE:
         case ExpressionGraph::L:
         case ExpressionGraph::LE:
         case ExpressionGraph::EQ:
         case ExpressionGraph::NEQ:
         {
            if(cmpvar && node->type == ExpressionGraph::DYNAMIC_NODE)
            {
               //should not have a symbol and thus cannot be in objective
               MdlScipVar msvar;
               msvar.node = node;
               auto n = comparisons.find( msvar );

               if( n != comparisons.end() )
               {
                  auto& name = const_cast<std::string &>(n->name);
                  name += " ";
                  name += entry.first;
               }
               else
               {
                  std::ostringstream str;
                  str << "CMP " << ++cmp << ' ' << entry.first;
                  msvar.name = str.str();
                  msvar.type = SCIP_VARTYPE_BINARY;
                  comparisons.emplace( std::move( msvar ) );
               }
            }

            stack.emplace( node->child2 );
            stack.emplace( node->child1 );
            continue;
         }

         case ExpressionGraph::IF:
         case ExpressionGraph::DELAY_FIXED:
         case ExpressionGraph::PULSE_TRAIN:
         case ExpressionGraph::RAMP:
            stack.emplace( node->child3 );

         case ExpressionGraph::APPLY_LOOKUP:
         case ExpressionGraph::PULSE:
         case ExpressionGraph::ACTIVE_INITIAL:
         case ExpressionGraph::STEP:
         case ExpressionGraph::RANDOM_UNIFORM:
         case ExpressionGraph::PLUS:
         case ExpressionGraph::MINUS:
         case ExpressionGraph::MULT:
         case ExpressionGraph::DIV:
         case ExpressionGraph::AND:
         case ExpressionGraph::OR:
         case ExpressionGraph::POWER:
         case ExpressionGraph::LOG:
         case ExpressionGraph::MIN:
         case ExpressionGraph::MAX:
         case ExpressionGraph::MODULO:
            stack.emplace( node->child2 );

         case ExpressionGraph::INITIAL:
         case ExpressionGraph::UMINUS:
         case ExpressionGraph::SQRT:
         case ExpressionGraph::EXP:
         case ExpressionGraph::LN:
         case ExpressionGraph::ABS:
         case ExpressionGraph::INTEGER:
         case ExpressionGraph::NOT:
         case ExpressionGraph::SIN:
         case ExpressionGraph::COS:
         case ExpressionGraph::TAN:
         case ExpressionGraph::ARCSIN:
         case ExpressionGraph::ARCCOS:
         case ExpressionGraph::ARCTAN:
         case ExpressionGraph::SINH:
         case ExpressionGraph::COSH:
         case ExpressionGraph::TANH:
         {
            stack.emplace( node->child1 );
            //if the formulation is not set to minimal then
            //add a variable for all symbols
            bool lookup = false;
            if(cmpvar)
            {
               switch(node->op)
               {
                  case ExpressionGraph::DIV:
                     if(node->child2->type == ExpressionGraph::DYNAMIC_NODE)
                        positive.emplace(node->child2);
                     break;
                  case ExpressionGraph::LOG:
                     if(node->child1->type == ExpressionGraph::DYNAMIC_NODE)
                        positive.emplace(node->child1);
                     if(node->child2->type == ExpressionGraph::DYNAMIC_NODE)
                        positive.emplace(node->child2);
                     break;
                  case ExpressionGraph::SQRT:
                  case ExpressionGraph::LN:
                     if(node->child1->type == ExpressionGraph::DYNAMIC_NODE)
                        positive.emplace(node->child1);
                     break;
                  case ExpressionGraph::APPLY_LOOKUP:
                     if( isolatelookups &&
                         node->child2->type == ExpressionGraph::DYNAMIC_NODE &&
                         node->child2->op != ExpressionGraph::INTEG &&
                         node->child2->op != ExpressionGraph::CONTROL)
                     {
                        MdlScipVar msvar;
                        msvar.node = node->child2;
                        auto n = algebraic.find( msvar );

                        if( n == algebraic.end() )
                        {
                           auto symbols = exprGraph.getSymbol(node->child2);

                           if(symbols.empty())
                           {
                              std::ostringstream str;
                              str << "LKPARG " << ++lkparg << ' ' << entry.first;
                              msvar.name = str.str();
                           }
                           else
                           {
                              msvar.name = symbols.begin()->second.get();
                           }
                           algebraic.emplace( std::move( msvar ) );
                        }
                        lookup = true;
                     }
                  default:
                     break;
               }
            }
            bool posnode = positive.find(node) != positive.end();
            if( lookup || posnode || (
                 ( !minimal || mayer_coeff != 0 || lagrange_coeff != 0 ) &&
                 node == entry.second && node->type == ExpressionGraph::DYNAMIC_NODE )
              )
            {
               MdlScipVar msvar;
               msvar.node = node;
               auto n = algebraic.find( msvar );

               if( n != algebraic.end() )
               {
                  //node already has a variable -> add objective coeffs
                  //set iterator is defined as const_iterator to avoid changing the key
                  //in this set the key is based only on the node pointer so the following
                  //changes are ok
                  MdlScipVar &nonconst = const_cast<MdlScipVar &>( *n );
                  if(entry.second == node)
                  {
                     nonconst.lagrange_coeff += lagrange_coeff;
                     nonconst.mayer_coeff += mayer_coeff;
                     if(nonconst.name != entry.first)
                     {
                        nonconst.name += " ";
                        nonconst.name += entry.first;
                     }
                  }
                  nonconst.positive = posnode;
               }
               else
               {
                  //node has no var yet so add one
                  if(entry.second == node)
                  {
                     msvar.lagrange_coeff = lagrange_coeff;
                     msvar.mayer_coeff = mayer_coeff;
                     msvar.name = entry.first;
                  }
                  else
                  {
                     auto symbols = exprGraph.getSymbol(node);
                     if(symbols.empty())
                     {
                        std::ostringstream str;
                        if(posnode)
                           str << "POSEXPR " << ++pos;
                        else
                           str << "LKP "  << ++lkp;
                        str << ' ' << entry.first;
                        msvar.name = str.str();
                     }
                     else
                     {
                        msvar.name = symbols.begin()->second.get();
                     }
                  }
                  msvar.positive = posnode;
                  algebraic.emplace( std::move( msvar ) );
               }
            }

            continue;
         }

         case ExpressionGraph::CONTROL:
         {
            assert( node == entry.second ); //control should have symbol

            MdlScipVar msvar;
            msvar.node = node;

            assert( controls.find( msvar ) == controls.end() ); //and it should be unique
            msvar.lagrange_coeff = lagrange_coeff;
            msvar.mayer_coeff = mayer_coeff;
            msvar.name = entry.first;
            if(msvar.node->integer)
               msvar.type = SCIP_VARTYPE_INTEGER;
            controls.emplace( std::move( msvar ) );
            continue;
         }

         case ExpressionGraph::TIME:
         case ExpressionGraph::CONSTANT:
         case ExpressionGraph::LOOKUP_TABLE:
            continue;

         case ExpressionGraph::NIL:
            assert(false);
         };
      }

      //after the expression of the current symbol table entry
      //has been processed all states have to be added to the state
      //vector
      int state_lvl = 0;

      while( !state_stack.empty() )
      {
         MdlScipVar msvar;
         msvar.node = state_stack.top();
         state_stack.pop();

         auto range = exprGraph.getSymbol( msvar.node );

         if( range.empty() )
         {
            //if the state has no symbol then it comes from
            //smooth or delay operands and will get the name
            //of the symbol where it appeared appended by
            // _LVx where x is 1 for the state that appears
            //lowest in the expression graph and thus is
            //highest on the state_stack.
            std::ostringstream stream;
            stream << entry.first << " LV" << ( ++state_lvl );
            msvar.name = stream.str();
         }
         else
         {
            msvar.name = "";

            //sum up objective coefficients and append symbol names to var name
            for( const std::pair<ExpressionGraph::Node *, Symbol> &symb : range )
            {
               if( !msvar.name.empty() )
                  msvar.name += " ";

               msvar.name += symb.second;

               for( const Objective::Summand & s : objective.getSummands() )
               {
                  if( s.variable == symb.second )
                  {
                     if( s.type == Objective::Summand::LAGRANGE )
                        msvar.lagrange_coeff += s.coefficient;
                     else if( s.type == Objective::Summand::MAYER )
                        msvar.mayer_coeff += s.coefficient;
                  }
               }
            }
         }

         if( ratealgebraic )
         {
            MdlScipVar rate_msvar;
            rate_msvar.node = msvar.node->child1;

            if( algebraic.find(msvar) == algebraic.end() &&
                states.find(msvar)    == states.end()    &&
                controls.find(msvar)  == controls.end()
              )
            {
               //node has no var yet so add one
               rate_msvar.name = "RATE OF ";
               rate_msvar.name += msvar.name;
               algebraic.emplace( std::move( rate_msvar ) );
            }
         }

         //add var to states
         states.emplace( std::move( msvar ) );
      }
   }

   //insert all vars into vector with proper order
   std::vector<MdlScipVar> vars;
   vars.insert( vars.end(), states.begin(), states.end() );
   std::sort(
      vars.begin(), vars.end(),
      []( const MdlScipVar & a, const MdlScipVar & b )
   {
      return a.name < b.name;
   }
   );

   if( controls.size() != 0)
   {
      std::vector<MdlScipVar> controlVec;
      controlVec.insert(controlVec.end(), controls.begin(), controls.end());
      std::sort(
         controlVec.begin(), controlVec.end(),
         []( const MdlScipVar & a, const MdlScipVar & b )
      {
         return a.name < b.name;
      }
      );
      vars.insert(vars.end(), controlVec.begin(), controlVec.end());
   }

   auto pos = vars.size();

   vars.insert( vars.end(), comparisons.begin(), comparisons.end() );
   vars.insert( vars.end(), algebraic.begin(), algebraic.end() );

   std::sort(
      vars.begin()+pos, vars.end(),
      []( const MdlScipVar & a, const MdlScipVar & b )
   {
      return a.node->level < b.node->level;
   }
   );

   vars.shrink_to_fit();
   //then set the indexes in this order
   int val = 0;

   for( MdlScipVar & var : vars )
   {
      var.idx = val++;
      var.positive = positive.find(var.node) != positive.end();
   }

   return vars;
}

std::vector< double > MdlExpressionTranslator::getParameterValues( double time, bool initial )
{
   std::vector<double> paramVals( parameters.size() );

   for( auto & param : parameters )
   {
      paramVals[param.second] = exprGraph.evaluateNode( param.first, time, initial );
   }

   return paramVals;
}

std::vector< double > MdlExpressionTranslator::getParameterValues( int time, bool initial )
{
   double initial_time = exprGraph.getNode( sdo::Symbol( "INITIAL TIME" ) )->value;
   double time_step = exprGraph.getNode( sdo::Symbol( "TIME STEP" ) )->value;
   return getParameterValues( initial_time + time * time_step, initial );
}

std::vector< sdo::ExpressionGraph::Node * > MdlExpressionTranslator::getParameterNodes()
{
   std::vector< sdo::ExpressionGraph::Node * > params( parameters.size() );

   for( auto & param : parameters )
   {
      //type of param is pair<Node,int> where second part is param_idx
      params[param.second] = param.first;
   }

   return params;
}

MdlExpressionTranslator::~MdlExpressionTranslator()
{
   for(std::pair<sdo::ExpressionGraph::Node*, SCIP_EXPR*> nodeexprpair : expressions )
      SCIPexprFreeDeep(SCIPblkmem(scip), &nodeexprpair.second);

   for(std::pair<sdo::ExpressionGraph::Node*, SCIP_EXPR*> nodeexprpair : vars )
      SCIPexprFreeDeep(SCIPblkmem(scip), &nodeexprpair.second);
}
