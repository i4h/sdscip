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

/**@file    SDListBuilder.h
 * @brief   Listbuilder for problem structure used by sdscip
 * @author  Robert L. Gottwald
 *
 */


#ifndef __SD_LISTBUILDER_H__
#define __SD_LISTBUILDER_H__

#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <scip/scip.h>
#include <utility>
#include <type_traits>
#include "SDListTraits.h"

template<typename T, typename VAR_ID>
class SDListBuilder
{
   static_assert(!std::is_void<key_type<T, VAR_ID>>::value, "Type not supported for ListBuilder, specialization of SDListTraits required.");
public:
   /** adds variable to builder */
   template<typename... Args>
   void add( const VAR_ID& symb, Args && ... args )
   {
      //add new variable to deque
      vars_.emplace_back( std::forward<Args>( args )... );
      //get pointer to it
      updateList(symb, &(vars_.back()));
      //add variable with proper key to map
   }

   /* builds the SDProbVars structure containing all variables added so far.
    * The given probVars structure is overwritten with the contents of
    * this builder.
    */
   std::vector<T> build()
   {
      std::vector<T> sortedVars;
      sortedVars.reserve( vars_.size() );
      std::move( vars_.begin(), vars_.end(), std::back_inserter( sortedVars ) );
      //sort vector
      std::sort( sortedVars.begin(), sortedVars.end() );
      //clear builder contents
      decltype(varsMap_)().swap(varsMap_);
      decltype(vars_)().swap(vars_);
      return sortedVars;
   }

   void clear() {
      vars_.clear();
      varsMap_.clear();
   }
private:

   void updateList(const VAR_ID& symb, T* val)
   {
      key_type<T, VAR_ID> k = SDListTraits<T, VAR_ID>::get_key(symb, *val);
      varsMap_.emplace( k, val );
      auto prev_iter = varsMap_.find( SDListTraits<T, VAR_ID>::get_prev_key( k ) );
      if( prev_iter != varsMap_.end() )
      {
         //add next pointer for previous time and prev pointer for the new variable
         T* prev_val = prev_iter->second;
         prev_val->setNext( val );
         val->setPrev( prev_val );
      }
      auto next_iter = varsMap_.find( SDListTraits<T, VAR_ID>::get_next_key( k ) );
      if( next_iter != varsMap_.end() )
      {
         //add next pointer for previous time and prev pointer for the new variable
         T* next_val = next_iter->second;
         next_val->setPrev( val );
         val->setNext( next_val );
      }
   }

   std::deque<T> vars_; //use a deque to avoid iterator/reference invalidation of pointers in map
   std::map<key_type<T, VAR_ID>, T*> varsMap_;
};


#endif
