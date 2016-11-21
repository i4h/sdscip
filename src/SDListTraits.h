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

/**@file    SDListTraits.h
 * @brief   Traits for SDList
 * @author  Robert L. Gottwald
 *
 */


#ifndef __SD_LIST_TRAITS_H__
#define __SD_LIST_TRAITS_H__

#include "SDVariable.h"
#include "SDControl.h"

template<typename T, typename VAR_ID>
struct SDListTraits
{
   using key_t = void;
/*
   static key_t get_key(const mdl::Symbol &s, T&& val);
   static key_t get_prev_key(key_t);
   static key_t get_next_key(key_t);
*/
};

template<typename T, typename VAR_ID>
using key_type = typename SDListTraits<T, VAR_ID>::key_t;

template<typename VAR_ID>
struct SDListTraits<SDVariable, VAR_ID>
{
   using key_t = std::tuple<VAR_ID, int, int>;

   static key_t get_key(const VAR_ID &s, const SDVariable &val)
   {
      return key_t{s, val.getTime(), val.getLevel()};
   }

   static key_t get_prev_key(const key_t &k)
   {
      return key_t{std::get<0>(k), std::get<1>(k)-1, std::get<2>(k)};
   }
   
   static key_t get_next_key(const key_t &k)
   {
      return key_t{std::get<0>(k), std::get<1>(k)+1, std::get<2>(k)};
   }
};

template<typename VAR_ID>
struct SDListTraits<SDControl, VAR_ID>
{
   using key_t = std::tuple<VAR_ID, int, int>;

   static key_t get_key(const VAR_ID &s, const SDControl &val)
   {
      return key_t{s, val.getTimeBegin(), val.getTimeEnd()};
   }

   static key_t get_prev_key(const key_t &k)
   {
      int t0 = std::get<1>(k);
      int t1 = std::get<2>(k);
      int width = t1-t0;
      return key_t{std::get<0>(k), t0-width, t1-width};
   }

   static key_t get_next_key(const key_t &k)
   {
      int t0 = std::get<1>(k);
      int t1 = std::get<2>(k);
      int width = t1-t0;
      return key_t{std::get<0>(k), t0+width, t1+width};
   }
};


#endif
