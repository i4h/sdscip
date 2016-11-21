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

/**@file    SDControl.h
 * @brief   class representing sd control variable
 * @author  Robert L. Gottwald
 *
 */


#ifndef __SD_CONTROL_H__
#define __SD_CONTROL_H__

#include <scip/scip.h>
#include <string>
#include <iostream>
#include "ListNode.h"

class SDControl : public ListNode<SDControl>
{
public:
   SDControl( int time_begin, int time_end, SCIP_VAR* var ) :
      time_begin_( time_begin ), time_end_( time_end ), var_( var ) {}


   const SCIP_VAR* getScipVariable() const
   {
      return var_;
   }

   const std::string getScipVarName() const
   {
      return std::string(SCIPvarGetName(var_));
   }


   SCIP_VAR* getScipVariable()
   {
      return var_;
   }

   int getTimeBegin() const
   {
      return time_begin_;
   }

   int getTimeEnd() const
   {
      return time_end_;
   }

   /* Define order by end time  */
   bool operator< ( const SDControl& other ) const
   {
      return time_end_ < other.time_end_ || ( time_end_ == other.time_end_ && time_begin_ < other.time_begin_ );
   }

   /* for convenient comparison with time only */
   bool operator< ( int time ) const
   {
      return time_end_ < time;
   }

   friend bool operator<( const int time, const SDControl& var )
   {
      return time <  var.time_end_;
   }

   /* provide comparator for start time */
   struct CompareStartTime
   {
      bool operator()(int time, const SDControl &c) const
      {
         return time < c.time_begin_;
      }

      bool operator()(const SDControl &c, int time) const
      {
         return c.time_begin_ < time;
      }

      bool operator()(const SDControl &c1, const SDControl &c2) const
      {
         return c1.time_begin_ < c2.time_begin_ || (c1.time_begin_ == c2.time_begin_ && c1.time_end_ < c2.time_end_);
      }
   };

   struct CompareTime
   {
      bool operator()(int time, const SDControl &c) const
      {
         return time < c.time_begin_ && time < c.time_end_;
      }

      bool operator()(const SDControl &c, int time) const
      {
         return c.time_begin_ < time && c.time_end_ < time;
      }

      bool operator()(const SDControl &c1, const SDControl &c2) const
      {
         return c1.time_begin_ < c2.time_begin_ || (c1.time_begin_ == c2.time_begin_ && c1.time_end_ < c2.time_end_);
      }
   };

private:
   int time_begin_;
   int time_end_;
   SCIP_VAR* var_;
};

#endif
