#ifndef FORTHY2_POOL_TYPE_HPP
#define FORTHY2_POOL_TYPE_HPP

#include "forthy2/pool.hpp"
#include "forthy2/type.hpp"

namespace forthy2 {
  template <typename T>
  struct PoolType: Type {
    Pool<T> pool;

    PoolType(Cx &cx, const Sym *id, vector<Type *> parents = {}):
      Type(cx, id, parents) {}

    template <typename...Args>
    T &get(Cx &cx, Args &&...args);
  };
}

#endif
