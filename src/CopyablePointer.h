//#define SCIP_DBG
/*
 * ReduceODEintegrator.h
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
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
