#ifndef _MDL_EXPRESSION_TRANSLATOR_H_
#define _MDL_EXPRESSION_TRANSLATOR_H_

#include <sdo/ExpressionGraph.hpp>
#include <sdo/Objective.hpp>
#include <scip/scip.h>
#include <nlpi/type_expr.h>
#include <stack>
#include <spline/BSplineCurve.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

//#include
/**
 * Small class that represents a node in a sdo::ExpressionGraph
 * that gets a variable in the formulation of the problem within scip.
 * Every relevant information that is required to create the SCIP_VAR
 * is stored in here.
 */
struct MdlScipVar
{
   sdo::ExpressionGraph::Node *node;
   std::string name;
   int idx;
   SCIP_VARTYPE type = SCIP_VARTYPE_CONTINUOUS;
   SCIP_Real mayer_coeff = 0;
   SCIP_Real lagrange_coeff = 0;
   bool negative = false;
   bool positive = false;

   SCIP_Real getLb(SCIP* scip) const
   {
      SCIP_Real lb = node->lb.is_initialized() ? node->lb.get() : -SCIPinfinity(scip);
      switch(type)
      {
         case SCIP_VARTYPE_BINARY:
            lb = 0;
            break;
         case SCIP_VARTYPE_CONTINUOUS:
            if(positive)
               lb = SCIPfeastol(scip);
         default:
            break;
      }
      if(node->op == sdo::ExpressionGraph::CONTROL && node->child1)
         lb = std::max(node->child1->value, lb);

      return lb;
   }

   SCIP_Real getUb(SCIP* scip) const
   {
      SCIP_Real ub = node->ub.is_initialized() ? node->ub.get() : SCIPinfinity(scip);
      switch(type)
      {
         case SCIP_VARTYPE_BINARY:
            ub = 1;
            break;
         case SCIP_VARTYPE_CONTINUOUS:
            if(negative)
               ub = -SCIPfeastol(scip);
         default:
            break;
      }
      if(node->op == sdo::ExpressionGraph::CONTROL && node->child3)
         ub = std::min(node->child3->value, ub);
      return ub;
   }
};

using SplinePtr = boost::shared_ptr< spline::BSplineCurve<3, SCIP_Real> >;
using LookupMap = boost::unordered_map<sdo::ExpressionGraph::Node*, SplinePtr >;

//specialze std hash and equal_to to use unordered_set/map bases on the node in the ExpressionGraph of the MdlScipVar
namespace std
{

template<>
struct hash<MdlScipVar>
{
   size_t operator()(const MdlScipVar &v) const
   {
      return  hash<sdo::ExpressionGraph::Node *>()(v.node);
   }
};


template<>
struct equal_to<MdlScipVar>
{
   bool operator()(const MdlScipVar &a, const MdlScipVar &b) const
   {
      return a.node == b.node;
   }
};

}

/**
 * Class that handles the conversion of epxressions stored inside
 * a sdo::ExpressionGraph into an expression represented as SCIP_EXPR*
 */
class MdlExpressionTranslator
{
public:
   /**
    * Create a MdlExpressionTranslator object
    *
    * \param scip         pointer to scip
    * \param exprGraph    reference to expression graph where the nodes belong to
    * \param lkpMap       reference to a map storing an approximation for the lookup functions
    *                     in the expression graph. If an entry in this map is empty then a
    *                     piecewise linear expression will be created from the lookup directly
    */
   MdlExpressionTranslator( SCIP *_scip,  sdo::ExpressionGraph &_exprGraph, const LookupMap &_lkpMap ) : scip(_scip), exprGraph(_exprGraph), lkpMap(_lkpMap) {}

   /* Disable copying of expression translator */
   MdlExpressionTranslator( const MdlExpressionTranslator& ) = delete;

   /* move constructor is the default one */
   MdlExpressionTranslator( MdlExpressionTranslator&& ) = default;

   /**
    * the destructor of the expression translator which frees all cached SCIP_EXPR
    */
   ~MdlExpressionTranslator();

   /**
    * Create a SCIP_EXPR* from a sdo::ExpressionGraph::Node
    *
    * @param root         the sdo::ExpressionGraph::Node for which an expression will be created
    * @param expr         a pointer to store the expression that is created
    * @param initial      whether to create an expression for the initial value of the given node
    * @param allowrootvar whether the root node itself may be represented as a variable expression
    */
   SCIP_RETCODE getScipExpr( sdo::ExpressionGraph::Node *root, SCIP_EXPR **expr, bool initial = false, bool allowrootvar = false  );

   /**
    * Get the expression of a sdo::ExpressionGraph::Node that has a variable in this MdlExpressionTranslator
    *
    * @param varnode      the node
    * @return  the expression for the variable of the node
    */
   SCIP_EXPR *getVarExpr( sdo::ExpressionGraph::Node *varnode );

   /**
    * Get the values of the parameters used in the expressions for a given time
    *
    * @param time      the time for which the parameter values should be created
    * @param initial   whether the parameters should represent the initial value
    * @return  vector with values for each parameter
    */
   std::vector<double> getParameterValues( double time, bool initial = false );

   /**
    * Get the values of the parameters used in the expressions for a given time
    *
    * @param time      the index of the time for which the parameter values should be created
    * @param initial   whether the parameters should represent the initial value
    * @return  vector with values for each parameter
    */
   std::vector<double> getParameterValues( int time, bool initial = false );

   /**
    * Get the nodes of the expression graph for which a parameter was created
    *
    * @return  vector with nodes for each parameter
    */
   std::vector<sdo::ExpressionGraph::Node *> getParameterNodes();

   /**
    * Set the expressions for the variables of the translator to the SCIP_EXPR
    * that represent the direct variable (i.e. with operator SCIP_EXPR_VARIDX)
    * for each variable in the given vector
    */
   SCIP_RETCODE setVars(const std::vector<MdlScipVar> &vec);

   /**
    * Set the expressions for the variables of the translator to the given SCIP_EXPR
    * for each variable in the given vector
    *
    * \param vec      vector of variables
    * \param varexpr  vector of expressions corresponding to the given variables
    */
   SCIP_RETCODE setVars(const std::vector<MdlScipVar> &vec, const std::vector<SCIP_EXPR *> &varexpr);

   /**
    * Create a mapping of expressiongraph nodes to variables
    *
    * \param objective       objective function of problem
    * \param minimal         whether variables in should only be created if necessary
    *                        or if all variables found in the expression graph should get one
    * \param cmpvar          whether additional variables that are required in the formulation of the problem
    *                        should be created.
    * \param ratealgebraic   whether the rates of the states should get a variable
    * \param isolatelookups  whether lookup expressions should be isolated as an expression,
    *                        i.e. the result and the argument of the lookup will get a variable
    */
   std::vector<MdlScipVar> createVariableMapping(const sdo::Objective &objective, bool minimal, bool cmpvar = true, bool ratealgebraic = false, bool isolatelookups = false);

private:
   SCIP *scip;
   sdo::ExpressionGraph &exprGraph;
   std::unordered_map<sdo::ExpressionGraph::Node *, SCIP_EXPR *> expressions;
   std::unordered_map<sdo::ExpressionGraph::Node *, SCIP_EXPR *> vars;
   std::unordered_map<sdo::ExpressionGraph::Node *, int> parameters;
   const LookupMap &lkpMap;
};


#endif
