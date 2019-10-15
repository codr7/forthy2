#ifndef FORTHY2_POOL_TYPE_HPP
#define FORTHY2_POOL_TYPE_HPP

#include "forthy2/pool.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  template <typename T>
  struct PoolType: ValType<T> {
    Pool<T> pool;

    PoolType(Cx &cx, Sym &id, vector<Type *> parents = {}):
      ValType<T>(cx, id, parents) {}

    template <typename...Args>
    T &get(Cx &cx, Args &&...args);
  };
}

#endif
