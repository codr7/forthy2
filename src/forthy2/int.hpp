#ifndef FORTHY2_INT_HPP
#define FORTHY2_INT_HPP

#include <cstdint>

#include "forthy2/val.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Cx;
  
  struct Int: Val {
    using Imp = int64_t;
    Imp imp;

    Int(Imp imp);
    operator bool() override { return imp; }
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  struct IntType: PoolType<Int> {    
    IntType(Cx &cx, Sym &id, vector<Type *> parents = {});
    Int &get(Cx &cx, Int::Imp imp);
  };
}

#endif
