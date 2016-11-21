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

/**@file    CopyablePointer.h
 * @brief   Smart pointer that copies the resource when pointer is copied
 * @author  Ingmar Vierhaus
 *
 */


#ifndef SDSCIP_COPYABLEPOINTER_H_
#define SDSCIP_COPYABLEPOINTER_H_

#include "sdscip.h"
#include <ostream>

namespace sdscip
{

template <typename T>
class CopyablePointer {
  public:
    CopyablePointer()
        : p(nullptr)
     { }

    explicit CopyablePointer(T *_p) : p(_p)
    { }

    /* Copy constructor */
    CopyablePointer(CopyablePointer const &rhs)
         : p(rhs.p->clone())
    {
       SCIPdbgMsg("copy constructor of CopyablePointer\n");
       SCIPdbgMsg("nStates is %i\n", rhs.p->nStates_);
       std::string name = rhs.p->getName();

       //SCIPdbgMsg("rhs is %s\n",rhs.p->getName().c_str());

    }

    /* Destructor */
    ~CopyablePointer() {
       if (p == nullptr) {
          SCIPdbgMsg("Deleting nullptr\n");
       } else {
          SCIPdbgMsg("deleting rateEvaluator %s\n",p->getName().c_str());
       }
       delete p;
    }


    /* Assignment operator */
    CopyablePointer& operator=(CopyablePointer rhs) {
       swap(rhs);
       return *this;
    }

    void swap(CopyablePointer &rhs) {
        using std::swap;
        swap(p, rhs.p);
    }

    /* Move operator */
    CopyablePointer(CopyablePointer &&rhs) : p(rhs.p) { rhs.p = nullptr; }


    /* Pointer semantics */
    T &operator*() const
    {
       return *p;
    }

    T* operator->() const
    {
       return &this->operator*();
    }


    /* String operator */
    operator std::string() const { return std::to_string((long int) p); }


    /* other members */
    int address() { return p; }

private:
    T* p;
};

}
#endif /* SDSCIP_COPYABLEPOINTER_H_ */
