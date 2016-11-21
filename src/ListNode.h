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
