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
