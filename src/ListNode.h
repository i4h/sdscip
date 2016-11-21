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

/**@file    ListNode.h
 * @brief   Node in variable list
 * @author  Robert L. Gottwald
 *
 */


#ifndef __LISTNODE_H__
#define __LISTNODE_H__

#include <utility>

template<typename T>
class ListNode
{
public:
   //forbid copy
   ListNode( const ListNode& ) = delete;
   ListNode& operator=( const ListNode& ) = delete;

   const T* getNext() const
   {
      return next_;
   }

   T* getNext()
   {
      return next_;
   }

   const T* getPrev() const
   {
      return prev_;
   }

   T* getPrev()
   {
      return prev_;
   }

   void setNext( T* next )
   {
      next_ = next;
   }

   void setPrev( T* prev )
   {
      prev_ = prev;
   }

protected:
   ListNode() : prev_(nullptr), next_(nullptr)
   {
   }

   ~ListNode()
   {
      if(prev_)
         prev_->next_ = next_;
      if(next_)
         next_->prev_ = prev_;
   }

   ListNode( ListNode<T> && other )
   {
      prev_ = other.prev_;
      other.prev_ = nullptr;
      next_ = other.next_;
      other.next_ = nullptr;
      if(next_)
         next_->prev_ = static_cast<T*>(this);
      if(prev_)
         prev_->next_ = static_cast<T*>(this);
   }

   ListNode<T>& operator=( ListNode<T> && other )
   {
      prev_ = other.prev_;
      other.prev_ = nullptr;
      next_ = other.next_;
      other.next_ = nullptr;
      if(next_)
         next_->prev_ = static_cast<T*>(this);
      if(prev_)
         prev_->next_ = static_cast<T*>(this);
      return *this;
   }
private:
   T* prev_;
   T* next_;

};


#endif
