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
