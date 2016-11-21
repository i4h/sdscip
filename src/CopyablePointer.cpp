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

/**@file    CopyablePointer.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


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
