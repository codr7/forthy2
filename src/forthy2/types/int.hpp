#ifndef FORTHY2_TYPE_INT_HPP
#define FORTHY2_TYPE_INT_HPP

#include "forthy2/int.hpp"
#include "forthy2/prim_val.hpp"

namespace forthy2 {
  struct IntVal: PrimVal<Int> {
    IntVal(Int v): PrimVal<Int>(v) {}
    void dump(ostream &out) override { out << v; }
    Type &get_type(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
