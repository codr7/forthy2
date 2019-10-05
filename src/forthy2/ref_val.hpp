#ifndef FORTHY2_REF_VAL_HPP
#define FORTHY2_REF_VAL_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  template <typename T>
  struct RefVal: TVal<T> {
    template <typename...Args>
    RefVal(Args &&...args): TVal<T>(forward<Args>(args)...) {}

    Cmp cmp(Val &other) override {
      return forthy2::cmp<Val *>(this, &other);
    }

    bool is(Val &other) override { return this == &other; }
  };
}

#endif
