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

/**@file    NLPGraph.cpp
 * @brief   Class for visual representation of nlp constraint dependencies
 * @author  Ingmar Vierhaus
 *
 */


#include "NLPGraph.h"

#include <sstream>

unsigned int NLPGraph::order(Node n) const {
   int cnt = 0;
   for (lemon::ListGraph::IncEdgeIt e(*g_, n); e != lemon::INVALID; ++e) {
     cnt++;
   }
   return cnt;
}

unsigned int NLPGraph::nonFixedOrder(Node n) const {
   assert((*types_)[n] == 1); //Only makes sense for Variables

   int cnt = 0;
   for (lemon::ListGraph::IncEdgeIt e(*g_, n); e != lemon::INVALID; ++e) {
      if (!isFixed(e))
         ++cnt;
   }
   return cnt;
}

void NLPGraph::fix(Node n) {
   for (lemon::ListGraph::IncEdgeIt e(*g_, n); e != lemon::INVALID; ++e) {
     (*fixedEdges_)[e] = true;
   }
}

void NLPGraph::fix(Node n,int step) {
   for (lemon::ListGraph::IncEdgeIt e(*g_, n); e != lemon::INVALID; ++e) {
      (*fixedEdges_)[e] = true;
      (*propSequence_)[e] = step;
   }
}


void NLPGraph::calcPropagationSequence() {
   //Initialize
   calcFixedEdges();
   calcNonFixedOrders();

   //Create bookkeeping of nonFixedOrders
   std::map<int,std::map<int, Node> > nFOrdersConstraints;

   lemon::ListGraph::EdgeIt e((*g_));
   unsigned int lowestNonFixedOrder;

   for(std::vector<Node>::const_iterator it = constraints_.begin(); it != constraints_.end(); ++it) {
      if (it == constraints_.begin())
         lowestNonFixedOrder = nonFixedOrder(*it);

      if (nonFixedOrder(*it) > 0 && nonFixedOrder(*it) < lowestNonFixedOrder)
         lowestNonFixedOrder = nonFixedOrder(*it);
      nFOrdersConstraints[nonFixedOrder(*it)][(*nIds_)[*it]] = (*it);
   }

   //Iterate over Map to see if everything worked
   {
      std::map<int, std::map<int, Node> >::iterator nFOrdersIt = nFOrdersConstraints.begin();
      for( ; nFOrdersIt != nFOrdersConstraints.end(); ++nFOrdersIt ) {
         SCIPdbgMsg("looking at constraints with nonfixedOrder %i\n",nFOrdersIt->first);
         std::map<int, Node>::iterator consNodesIt = nFOrdersIt->second.begin();
         for( ; consNodesIt != nFOrdersIt->second.end(); ++consNodesIt ) {
            SCIPdbgMsg("have one with Id %i by the name of %s\n",consNodesIt->first,(*names_)[consNodesIt->second].c_str());
            //SCIPdbgMsg("have one with Id %i \n",consNodesIt->first)  ;

         }
      }
      SCIPdbgMsg("minimum nonFixedOrder is %i\n",lowestNonFixedOrder);
   }


   unsigned int step = 0;
   //Get a constraint with minimum fixed Order, propagate and move inside the map

   std::map<int, Node>::iterator consNodesIt;

   while (nFOrdersConstraints[lowestNonFixedOrder].size() > 0) {
      ++step;
      SCIPdbgMsg("step is %i\n",step);
      //SCIPdbgMsg("size is %i\n",nFOrdersConstraints[lowestNonFixedOrder].size());
      consNodesIt = nFOrdersConstraints[lowestNonFixedOrder].begin();
      SCIPdbgMsg("grabbed %s\n",(*names_)[consNodesIt->second].c_str());
      //Find nonfixed Edges and fix Nodes at the Ends
      {
         for (lemon::ListGraph::IncEdgeIt e(*g_, consNodesIt->second); e != lemon::INVALID; ++e) {
            std::cout << "Got Edge \"" << (*names_)[(*g_).u(e)] << "\""
                     << " -- "
                     << "{\"" <<  (*names_)[(*g_).v(e)] << "\"}" << std::endl;

           if(!isFixed(e)) {
              (*propSequence_)[e] = step;
              fix((*g_).v(e),step);
              //Refresh nFixedOrder of all Variables connected to that Constraint and update nFOrdersConstraints
              for (lemon::ListGraph::IncEdgeIt varEdgeIt(*g_, (*g_).v(e)); varEdgeIt != lemon::INVALID; ++varEdgeIt) {
                 Node consToRefresh = (*g_).u(varEdgeIt);
                 SCIPdbgMsg("refreshing Edge to %s\n",(*names_)[(*g_).u(varEdgeIt)].c_str());

                 if (consToRefresh != consNodesIt->second) {
                    SCIPdbgMsg("found refresh is necessary\n");
                    //Delete Constraint from bookkeeping
                    SCIPdbgMsg("deleting %i %i\n",(*nonFixedOrders_)[consToRefresh],(*nIds_)[consToRefresh]);
                    nFOrdersConstraints[(*nonFixedOrders_)[consToRefresh]].erase((*nIds_)[consToRefresh]);

                    //Refresh nonFixedOrder in map
                    (*nonFixedOrders_)[consToRefresh] = nonFixedOrder(consToRefresh);
                    //Add Constraint to bookkeeping in the right place
                    nFOrdersConstraints[(*nonFixedOrders_)[consToRefresh]][(*nIds_)[consToRefresh]] = consToRefresh;
                 }

              }
           }
         }
      }

      //Copy node to NonFixedOrder 0 in Map
      nFOrdersConstraints[0][consNodesIt->first] = consNodesIt->second;
      nFOrdersConstraints[lowestNonFixedOrder].erase(consNodesIt);
      //Delete NonFixedOrder from Vector
   //   nFOrdersConstraints[lowestNonFixedOrder].erase(nIt);

      //Find new lowest order size
      {
         std::map<int, std::map<int, Node> >::iterator nFOrdersIt = nFOrdersConstraints.begin();
         for( ; nFOrdersIt != nFOrdersConstraints.end(); ++nFOrdersIt ) {
            if (nFOrdersIt->second.size() > 0) {
               if (nFOrdersConstraints[lowestNonFixedOrder].size() == 0)
                  lowestNonFixedOrder = nFOrdersIt->first;
               else if ((int) nFOrdersIt->first > 0 && (int) nFOrdersIt->first < (int) lowestNonFixedOrder)
                  lowestNonFixedOrder = nFOrdersIt->first;
            }
         }
      }

      //Iterate over Map to see if everything worked
      {
         std::map<int, std::map<int, Node> >::iterator nFOrdersIt = nFOrdersConstraints.begin();
         for( ; nFOrdersIt != nFOrdersConstraints.end(); ++nFOrdersIt ) {
            SCIPdbgMsg("looking at constraints with nonfixedOrder %i\n",nFOrdersIt->first);
            std::map<int, Node>::iterator consNodesIt = nFOrdersIt->second.begin();
            for( ; consNodesIt != nFOrdersIt->second.end(); ++consNodesIt ) {
               SCIPdbgMsg("have one with Id %i by the name of %s\n",consNodesIt->first,(*names_)[consNodesIt->second].c_str());
               //SCIPdbgMsg("have one with Id %i \n",consNodesIt->first)  ;

            }
         }
         SCIPdbgMsg("minimum nonFixedOrder is %i\n",lowestNonFixedOrder);
      }

      //Write this step to file
      std::ostringstream filename;
      filename << "ramsey" << step;
      writeGraph(filename.str());



   }
   SCIPdbgMsg("left while\n");


}

void NLPGraph::calcFixedEdges() {
   for(lemon::ListGraph::EdgeIt a((*g_));a!=lemon::INVALID;++a)
      if (isFixed((*g_).v(a)))
         (*fixedEdges_)[a] = true;
      else
         (*fixedEdges_)[a] = false;
}

void NLPGraph::calcNonFixedOrders() {
   for(std::vector<Node>::const_iterator it = constraints_.begin(); it != constraints_.end(); ++it)
      (*nonFixedOrders_)[*it] = nonFixedOrder(*it);
}


void NLPGraph::writeGraph(std::string filename) const {
   // Write .dot file
    std::ofstream dotFile;
    dotFile.open(filename.c_str());


   dotFile << "graph G {" << std::endl;
   dotFile << "edge [len=4, penwidth=3]" << std::endl;
   //graph [overlap=false];" << std::endl;

   //List of all variables, attributes line by line
   {
      std::map<int, Node>::const_iterator i = variables_.begin();
      for( ; i != variables_.end(); ++i ) {
         if (isFixed(i->second)) {
            dotFile << "\"" <<  (*names_)[i->second] << "\"" <<
               " [shape=box, color=green, style=filled, fillcolor=blue, fontcolor=white, fontsize=20, label=\"" << (*names_)[i->second] << " o" << order(i->second) << "\"]; " <<  std::endl;
         } else {
            dotFile << "\"" <<  (*names_)[i->second] << "\"" <<
               " [shape=box, color=blue, style=filled, fillcolor=blue, fontcolor=white, fontsize=20, label=\"" << (*names_)[i->second] << " o" << order(i->second) << "\"]; " <<  std::endl;
         }
      }
   }

   //Constraint list, attributes line by line
   {
      for(std::vector<Node>::const_iterator it = constraints_.begin(); it != constraints_.end(); ++it)
         dotFile << "\"" << (*names_)[*it] << "\""
            << " [shape=ellipse, color=red, style=filled, fillcolor=red, fontcolor=white, fontsize=20, label = \"" << (*names_)[*it] << " nfo" << nonFixedOrder(*it) << "\"]; " << std::endl;
   }

   //Add edges
   for(lemon::ListGraph::EdgeIt a((*g_));a!=lemon::INVALID;++a) {
      dotFile << "\"" << (*names_)[(*g_).u(a)] << "\""
         << " -- "
         << "{\"" <<  (*names_)[(*g_).v(a)] << "\"}"
         << "[label=\"s" << (*propSequence_)[a] << "\"";
      if ((*fixedEdges_)[a])
         dotFile << ",color=green ";
      dotFile << "]; " << std::endl;
   }
   dotFile << "}" << std::endl;

   dotFile.close();

}

