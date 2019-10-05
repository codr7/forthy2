#ifndef FORTHY2_TYPE_INT_HPP
#define FORTHY2_TYPE_INT_HPP

#include "forthy2/int.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/prim_val.hpp"

namespace forthy2 {
  struct IntVal: PrimVal<Int> {
    IntVal(Int v): PrimVal<Int>(v) {}
    Type &type() override;
  };

  struct IntType: PoolType<IntVal> {
    IntType(const string &id): PoolType(id) {}
  };

  extern IntType int_type;
}

#endif
