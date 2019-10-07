#ifndef FORTHY2_PRIM_VAL_HPP
#define FORTHY2_PRIM_VAL_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  template <typename T>
  struct PrimVal: TVal<T> {
    using TVal<T>::val;
    
    template <typename...Args>
    PrimVal(Args &&...args): TVal<T>(forward<Args>(args)...) {}

    virtual Cmp cmp(Val &other) override {
      return forthy2::cmp<T>(val, dynamic_cast<TVal<T> &>(other).val);
    }

    virtual bool is(Val &other) override {
      return dynamic_cast<TVal<T> &>(other).val == val;
    }
  };
}

#endif
