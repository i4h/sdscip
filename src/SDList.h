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

/**@file    SDList.h
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#ifndef __SDPROBVARS_H__
#define __SDPROBVARS_H__

#include "SDVariable.h"
#include "SDListBuilder.h"

template<typename T>
class SDList
{
public:
   template<typename VAR_ID>
   SDList( SDListBuilder<T, VAR_ID>& builder ) : vars_( builder.build() ) {}
   SDList() = default;
   using iterator = typename std::vector<T>::iterator;
   using const_iterator = typename std::vector<T>::const_iterator;
   using reverse_iterator = typename std::vector<T>::reverse_iterator;
   using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

   std::size_t size() const
   {
      return vars_.size();
   }

   /* iterate over variables at given time the order at a given
    * time is determined by the variables levels.
    */
   iterator begin( int time )
   {
      return std::lower_bound( vars_.begin(), vars_.end(), time );
   }

   iterator end( int time )
   {
      return std::upper_bound( vars_.begin(), vars_.end(), time );
   }

   const_iterator begin( int time ) const
   {
      return std::lower_bound( vars_.begin(), vars_.end(), time );
   }

   const_iterator end( int time ) const
   {
      return std::upper_bound( vars_.begin(), vars_.end(), time );
   }

   /* iterate over all variables */
   iterator begin()
   {
      return vars_.begin();
   }

   iterator end()
   {
      return vars_.end();
   }

   const_iterator begin() const
   {
      return vars_.begin();
   }

   const_iterator end() const
   {
      return vars_.end();
   }

   void clear() {
      vars_.clear();
   }

private:
   std::vector<T> vars_;
};

template<>
inline
SDList<SDControl>::iterator SDList<SDControl>::end( int time )
{
   return std::upper_bound( vars_.begin(), vars_.end(), time, SDControl::CompareStartTime() );
}

template<>
inline
SDList<SDControl>::const_iterator SDList<SDControl>::end( int time ) const
{
   return std::upper_bound( vars_.begin(), vars_.end(), time, SDControl::CompareStartTime() );
}

#endif
