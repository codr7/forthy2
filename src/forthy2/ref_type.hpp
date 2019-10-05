#ifndef FORTHY2_REF_TYPE_HPP
#define FORTHY2_REF_TYPE_HPP

#include "forthy2/cx.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  template <typename T>
  struct RefType: PoolType<T> {
    RefType(const string &id): PoolType<T>(id) {}

    Cmp cmp(const Val &other) override {
      return forthy2::cmp<const Val *>(this, &other);
    }

    bool is(const Val &other) override { return this == &other; }
  };
}

#endif
