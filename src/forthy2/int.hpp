#ifndef FORTHY2_INT_HPP
#define FORTHY2_INT_HPP

#include <cstdint>
#include <functional>

#include "forthy2/val.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Cx;
  
  struct Int: Val {
    using Imp = int64_t;
    Imp imp;

    Int(Imp imp): imp(imp) {}

    operator bool() override { return imp; }

    Cmp cmp(Val &other) override {
      return forthy2::cmp<Imp>(imp, dynamic_cast<Int &>(other).imp);
    }

    void dump(ostream &out) override;

    bool eq(Val &other) override {
      Int *v(dynamic_cast<Int *>(&other));
      return v ? v->imp == imp : false;
    }

    Iter &iter(Cx &cx, Pos pos) override;
    
    Len len() override { return (imp < 0) ? 0 : imp; }

    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  struct IntType: PoolType<Int> {    
    IntType(Cx &cx, Sym &id, vector<Type *> parents);
    Int &get(Cx &cx, Int::Imp imp);
  };
}

#endif
