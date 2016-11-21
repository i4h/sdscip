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

/**@file    SDVariable.h
 * @brief   Class representing SD variable
 * @author  Robert L. Gottwald
 *
 */


#ifndef __SD_VARIABLE_H__
#define __SD_VARIABLE_H__

#include <scip/scip.h>
#include "ListNode.h"
#include "SDCons.h"

class SDVariable : public ListNode<SDVariable>
{
public:
   SDVariable( int time, int level, SCIP_VAR* var, SDCons cons ) :
      time_( time ), level_( level ), var_( var ), cons_( std::move(cons) ) {}

   const SCIP_VAR* getScipVariable() const
   {
      return var_;
   }

   SCIP_VAR* getScipVariable()
   {
      return var_;
   }

   const SCIP_CONS* getScipConstraint() const
   {
      return cons_.getScipTopLevelCons();
   }

   SCIP_CONS* getScipConstraint()
   {
      return cons_.getScipTopLevelCons();
   }

   const SDCons& getConstraint() const
   {
      return cons_;
   }

   SDCons& getConstraint()
   {
      return cons_;
   }

   int getTime() const
   {
      return time_;
   }

   int getLevel() const
   {
      return level_;
   }

   /* Define order by time and level */
   bool operator< ( const SDVariable& other ) const
   {
      return time_ < other.time_ || ( time_ == other.time_ && level_ < other.level_ );
   }

   /* for convenient comparison with time only */
   bool operator< ( int time ) const
   {
      return time_ < time;
   }

   friend bool operator<( const int time, const SDVariable& var )
   {
      return time <  var.time_;
   }

private:
   int time_;
   int level_;
   SCIP_VAR* var_;
   SDCons cons_;
};

#endif
