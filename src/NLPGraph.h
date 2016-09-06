#ifndef __NLPGRAPH_H__
#define __NLPGRAPH_H__


#include <assert.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <map>

#include<lemon/list_graph.h>
#include<lemon/math.h>
#include<lemon/maps.h>

#include "scip/type_cons.h"
#include "sdscip.h"
#include "scip/struct_var.h"

#include<iostream>
#include<fstream>


class NLPGraph
{

public:


   typedef lemon::ListGraph::Node VarNode;
   typedef lemon::ListGraph::Node ConsNode;
   typedef lemon::ListGraph::Edge Edge;

   typedef lemon::ListGraph::Node Node;
   typedef lemon::ListGraph::NodeIt NodeIt;

  NLPGraph()
  {
     //Create a graph
     g_ = new lemon::ListGraph;
     names_= new lemon::ListGraph::NodeMap<std::string>(*g_);
     positions_ = new lemon::ListGraph::NodeMap<int>(*g_);
     types_ = new lemon::ListGraph::NodeMap<int>(*g_);
     nonFixedOrders_= new lemon::ListGraph::NodeMap<int>(*g_);
//     orders_ = new lemon::ListGraph::NodeMap<int>(*g_);
     varPointers_ = new lemon::ListGraph::NodeMap<SCIP_VAR*>(*g_);
     consPointers_ = new lemon::ListGraph::NodeMap<SCIP_CONS*>(*g_);
     fixedEdges_ = new lemon::ListGraph::EdgeMap<bool>(*g_);
     propSequence_ = new lemon::ListGraph::EdgeMap<unsigned int>(*g_); //fixed Edges are Edges between a constraint and a fixed variable
     nIds_ = new lemon::IdMap<lemon::ListGraph,Node>(*g_);


  }

  ~NLPGraph()
  {
     delete g_;
     delete positions_;
     delete types_;
     delete nonFixedOrders_;
     delete varPointers_;
     delete consPointers_;
     delete names_;
//     delete orders_;
     delete fixedEdges_;
     delete propSequence_;
     delete nIds_;

  }

  void calcConsOrders() const  {
     //Iterate over Constraints and calculate orders
     //for(std::vector<Node>::iterator it = constraints_.begin(); it != constraints_.end(); ++it) {
         /* std::cout << *it; ... */
     //}
  }

  unsigned int order(Node) const ;

  unsigned int nonFixedOrder(Node n) const;

  void calcPropagationSequence();

  void calcFixedEdges();

  void calcNonFixedOrders();

  void fix(Node n);

  void fix(Node n,int step);

  bool isFixed(Node varNode) const {
     return (SCIPvarGetStatus((*varPointers_)[varNode]) == SCIP_VARSTATUS_FIXED);
     return false;
  }

  bool isFixed(Edge edge) const {
     //Get Variable on this edge
     return (*fixedEdges_)[edge];
  }




  Node addCons()
  {
     Node n;
     n = g_->addNode();
     (*types_)[n] = 1;
     constraints_.push_back(n);
     return n;
  }

  Node addCons(std::string _name,SCIP_CONS* _consPointer) {
     SCIPdbgMsg("Adding constraint %s to Graph\n",_name.c_str());
     Node n;
     n = addCons();
     (*names_)[n] = _name;
     (*consPointers_)[n] = _consPointer;

     return n;
  }


  Edge addEdge(Node _constraint, Node _variable) {
     assert((*types_)[_constraint] == 1);
     assert((*types_)[_variable] == 0);

     SCIPdbgMsg("Adding Edge from %s to %s\n",(*names_)[_constraint].c_str(),(*names_)[_variable].c_str());
     Edge e = g_->addEdge(_constraint,_variable);

     return e;
  }


  /**
   * We show a SCIP-Variable to the NLP-Graph. If the graph already has a node that corresponds to that variable,
   * that node is returned. If the variable is not already in the graph, a new node is created and that node is returned.
   * The Variable Index (varPointer->index in struct_var.h) is used to determine if the variable already exists in the node.
   * I expect this to hold at least inside of one execution of the presolver.
   *
   * This function is the only function that should be used to add variables to the graph.
   *
   * @param SCIP_VAR* _varPointer The Pointer to the SCIP-Variable
   *
   */
  Node showVar(SCIP_VAR* _varPointer) {
     //Get number of this variable
     unsigned int index = _varPointer->index;
     Node varNode;

     std::string name(SCIPvarGetName(_varPointer));
     if (variables_.count(index) == 0 ) {
        //Variable with that index is not yet in the Graph
        //Add Node
        varNode = addVar(name,_varPointer);
        //Add node to variables map
        variables_[index] = varNode;
        //SCIPdbgMsg("added Variables %s to variables_\n",(*names_)[varNode].c_str());
     } else
     {
        varNode = variables_[index];
     }

     return varNode;
  }


  void printNodes() const {
     for (lemon::ListGraph::NodeIt n(*g_); n != lemon::INVALID; ++n) {
       int cnt = 0;
       for (lemon::ListGraph::IncEdgeIt e(*g_, n); e != lemon::INVALID; ++e) {
         cnt++;
       }
       std::cout << (*names_)[n] << " (deg(" << g_->id(n) << ") = " << cnt << ")"<< std::endl;
     }

  }

  void writeGraph(std::string filename) const ;

private:

  Node addVar()
  {
     Node n;
     n = g_->addNode();
     (*types_)[n] = 0;
     return n;
  }

  Node addVar(std::string _name,SCIP_VAR* _varPointer) {
     SCIPdbgMsg("Adding Variable %s to Graph -\n",_name.c_str());
     Node n;
     n = addVar();
     (*names_)[n] = _name;
     (*varPointers_)[n] = _varPointer;
     return n;
  }

  //Graph and its maps
  lemon::ListGraph *g_;
  lemon::ListGraph::NodeMap<std::string> *names_;
  lemon::ListGraph::NodeMap<int> *positions_;
  lemon::ListGraph::NodeMap<int> *types_; //Is Node variable or constraint (0: variable, 1: constraint)
  lemon::ListGraph::NodeMap<int> *nonFixedOrders_; //Is Node variable or constraint (0: variable, 1: constraint)
//  lemon::ListGraph::NodeMap<int> *orders_; //Orders of Nodes
  lemon::ListGraph::NodeMap<SCIP_VAR*> *varPointers_; //Pointers to constraints
  lemon::ListGraph::NodeMap<SCIP_CONS*> *consPointers_; //Pointers to Variables
  lemon::ListGraph::EdgeMap<bool> *fixedEdges_; //fixed Edges are Edges between a constraint and a fixed variable
  lemon::ListGraph::EdgeMap<unsigned int> *propSequence_; //fixed Edges are Edges between a constraint and a fixed variable

  std::map<int,Node> variables_; //Map connecting variable indices to Nodes
  std::vector<Node> constraints_; //Vector containing all Constraint Nodes

  lemon::IdMap<lemon::ListGraph,Node> *nIds_;   //IdMap for Nodes


};

#endif
