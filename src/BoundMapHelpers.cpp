/*
 * BoundMapHelpers.cpp
 *
 *  Created on: 15.10.2015
 *      Author: bzfvierh
 */

#ifndef BOUNDMAPHELPERS_CPP
#define BOUNDMAPHELPERS_CPP

#include "scip/scip.h"
#include "SDproblemStructureInterface.h"
#include <iomanip>      // std::setprecision

using namespace sdscip;

using BoundMap = SDproblemStructureInterface::BoundMap;
using BoundKey = SDproblemStructureInterface::BoundKey;


/*
 * Returns a BoundMap that contains the Union of the two given maps
 * If the BoundMap is missing an entry, there is no bound, i.e. the interval reaches to +/- infinity
 * -> only if a bound for the same exists in map1 and map2 there will be a bound in the result
 * */
inline BoundMap getUnion(const BoundMap& map1, const BoundMap& map2)
{
   BoundMap result;
   /* We iterate the smaller map to save time
    * assign mapA, mapB so that mapA.size() <= mapB.size() */
   bool keepOrder = ( map1.size() <= map2.size() ? true : false );
   auto mapA = ( keepOrder ? map1 : map2);
   auto mapB = ( keepOrder ? map2 : map1);

   /* Iterate mapA and add worse bounds if key exists in both maps */
   for( auto it2 = mapA.begin(); it2 != mapA.end(); ++it2)
   {
      BoundKey key = it2->first;
      SCIP_BOUNDTYPE type = it2->first.second;

      auto it1 = mapB.find(key);
      if (it1 != mapB.end())
      {
         result[key] = (type == SCIP_BOUNDTYPE_LOWER
                              ? std::min(it1->second, it2->second)
                              : std::max(it1->second, it2->second) );
      }
   }
   return result;
}

/* Returns a BoundMap that contains the Intersection of the two given maps */
 inline BoundMap getIntersection(const BoundMap& map1, const BoundMap& map2)
{
   BoundMap result(map1);
   for( auto it2 = map2.begin(); it2 != map2.end(); ++it2)
   {
      BoundKey key = it2->first;
      SCIP_BOUNDTYPE type = it2->first.second;

      auto it1 = result.find(key);
      if( it1!= result.end())
      {
         result[key] = (type == SCIP_BOUNDTYPE_LOWER
                              ? std::max(it1->second, it2->second)
                              : std::min(it1->second, it2->second) );
      }
      else
         result[key] = it2->second;
   }
   return result;
}

inline void printBoundMap(const BoundMap& map)
{
   printf("Printing BoundMap with %lu entries\n",map.size());
   for (auto it = map.begin(); it != map.end(); ++it)
   {
      SCIP_Real bound = it->second;
      BoundKey key = it->first;
      int stateId = key.first;
      SCIP_BOUNDTYPE bndtype = key.second;
      printf("state %i has %s bound: %f\n", stateId, (bndtype == SCIP_BOUNDTYPE_LOWER ? "lower" : "upper"), bound);
   }
}

inline std::string intervalVecToString(const std::vector<SCIP_Interval> vec)
{
   std::ostringstream s;
   s.precision(5);
   for (auto it = vec.begin(); it != vec.end(); ++it)
   {
      s <<  "[" << std::fixed << it->inf << "," << std::fixed << it->sup << "] (" << std::scientific << (it->sup - it->inf) << "), " ;
   }
   s << std::endl;
   return s.str();
}

inline std::string valVecToString(const std::vector<SCIP_Real> vec)
{
   std::ostringstream s;
   for (auto it = vec.begin(); it != vec.end(); ++it)
   {
      s << *it << ", ";
   }
   return s.str();
}


#endif
