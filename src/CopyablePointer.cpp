#include "CopyablePointer.h"


namespace sdscip
{
   template <typename T>
   std::ostream & operator<<(std::ostream & Str, CopyablePointer<T> const & v) {
      Str << v.p;
      return Str;
   }

   template <typename T>
   inline void swap(CopyablePointer<T> &lhs, CopyablePointer<T> &rhs) {
       lhs.swap(rhs);
   }

}
