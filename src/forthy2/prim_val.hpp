#ifndef FORTHY2_PRIM_VAL_HPP
#define FORTHY2_PRIM_VAL_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  template <typename T>
  struct PrimVal: TVal<T> {
    using TVal<T>::v;
    
    template <typename...Args>
    PrimVal(Args &&...args): TVal<T>(forward<Args>(args)...) {}

    Cmp cmp(Val &other) override {
      return forthy2::cmp<T>(v, dynamic_cast<TVal<T> &>(other).v);
    }

    bool is(Val &other) override {
      return dynamic_cast<TVal<T> &>(other).v == v;
    }
  };
}

#endif
