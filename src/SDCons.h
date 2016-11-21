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

/**@file    SDCons.h
 * @brief   class representing sd constraint
 * @author  Robert L. Gottwald
 *
 */


#ifndef __SD_CONS_H__
#define __SD_CONS_H__

#include <scip/scip.h>

enum class SDConsType
{
   SIMPLE,MIN,MAX,CONST_MIN,CONST_MAX
};

struct SDMinMax
{
   SCIP_VAR* arg0 = nullptr;
   SCIP_VAR* pos0 = nullptr;
   SCIP_VAR* neg0 = nullptr;
   SCIP_CONS* split0 = nullptr;
   SCIP_VAR* arg1 = nullptr;
   SCIP_VAR* pos1 = nullptr;
   SCIP_VAR* neg1 = nullptr;
   SCIP_CONS* split1 = nullptr;
   SCIP_VAR* select = nullptr;
   SCIP_CONS* select0_cons = nullptr;
   SCIP_CONS* select1_cons = nullptr;
   SCIP_CONS* cons = nullptr;
};

struct SDConstMinMax {
   SCIP_VAR* var_pos = nullptr;
   SCIP_VAR* var_neg = nullptr;
   SCIP_VAR* var_bin = nullptr;
   SCIP_CONS* cons = nullptr;
   SCIP_CONS* splitter = nullptr;
   SCIP_CONS* max_cons = nullptr;//   varpos <= var_upperbound(var_bin)
   SCIP_CONS* min_cons = nullptr;//   varneg <= (offset + var_lowerbound)*(1 - varbin)
};

class SDCons
{
public:
   SDCons() : type_(SDConsType::SIMPLE), cons_simple_(nullptr) {}
   SDCons(SCIP_CONS* c) : type_(SDConsType::SIMPLE), cons_simple_(c) {}
   SDCons(SDConsType type, SDConstMinMax *c) : type_(type), cons_constminmax_(c) {}

   SDCons(const SDCons &other)
   {
      type_ = other.type_;
      switch(type_)
      {
         default:
            assert(false);
         case SDConsType::SIMPLE:
            cons_simple_ = other.cons_simple_;
            break;
         case SDConsType::MIN:
         case SDConsType::MAX:
            cons_minmax_ = new SDMinMax(*(other.cons_minmax_));
            break;
         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            cons_constminmax_ = new SDConstMinMax(*(other.cons_constminmax_));
      }
   }

   SDCons& operator=(const SDCons &other)
   {
      switch(type_)
      {
         default:
            assert(false);
         case SDConsType::SIMPLE:
            break;
         case SDConsType::MIN:
         case SDConsType::MAX:
            delete cons_minmax_;
            break;
         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            delete cons_constminmax_;
      }
      type_ = other.type_;
      switch(type_)
      {
         default:
            assert(false);
         case SDConsType::SIMPLE:
            cons_simple_ = other.cons_simple_;
            break;
         case SDConsType::MIN:
         case SDConsType::MAX:
            cons_minmax_ = new SDMinMax(*(other.cons_minmax_));
            break;
         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            cons_constminmax_ = new SDConstMinMax(*(other.cons_constminmax_));
      }
      return *this;
   }

   SDCons(SDCons &&other)
   {
      type_ = other.type_;
      //setting other type to simple will make it not free any resources
      other.type_ = SDConsType::SIMPLE;
      cons_simple_ = other.cons_simple_;
   }

   SDCons& operator=(SDCons &&other)
   {
      switch(type_)
      {
         default:
            assert(false);
         case SDConsType::SIMPLE:
            break;
         case SDConsType::MIN:
         case SDConsType::MAX:
            delete cons_minmax_;
            break;
         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            delete cons_constminmax_;
      }
      type_ = other.type_;
      other.type_ = SDConsType::SIMPLE;
      cons_simple_ = other.cons_simple_;
      return *this;
   }

   friend SCIP_RETCODE CreateMinMaxCons( SCIP* scip, SDCons* sdcons, SDConsType type, SCIP_VAR* forward_var, SCIP_VAR* arg0, SCIP_VAR* arg1);

//   friend SCIP_RETCODE CreateConstMinMaxCons( SCIP* scip, SDCons* sdcons, SDConsType type, SCIP_VAR* forward_var, SCIP_VAR* arg, SCIP_Real const_arg);

   static SDCons CreateConstMin() {
      return SDCons(SDConsType::CONST_MIN, new SDConstMinMax());
   }

   static SDCons CreateConstMax() {
      return SDCons(SDConsType::CONST_MAX, new SDConstMinMax());
   }

   SDConsType getType() const
   {
      return type_;
   }

   SCIP_CONS* getScipTopLevelCons() const
   {
      switch(type_)
      {
         case SDConsType::SIMPLE:
            return cons_simple_;
         case SDConsType::MIN:
         case SDConsType::MAX:
            return cons_minmax_->cons;
         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            return cons_constminmax_->cons;
         default:
            assert(false);
      }
   }

   SDMinMax* getSDMinMaxConsData() const
   {
      assert(type_ == SDConsType::MAX || type_ == SDConsType::MIN);
      return cons_minmax_;
   }

   SDConstMinMax* getSDConstMinMaxConsData() const
   {
      assert(type_ == SDConsType::CONST_MAX || type_ == SDConsType::CONST_MIN);
      return cons_constminmax_;
   }

   ~SDCons()
   {
      switch(type_)
      {
         case SDConsType::SIMPLE:
            break;
         case SDConsType::MAX:
         case SDConsType::MIN:
            delete cons_minmax_;
         case SDConsType::CONST_MAX:
         case SDConsType::CONST_MIN:
            delete cons_constminmax_;
      };
   }

private:
   SDConsType type_;
   union {
      SCIP_CONS* cons_simple_;
      SDMinMax*  cons_minmax_;
      SDConstMinMax* cons_constminmax_;
   };
};

#endif
