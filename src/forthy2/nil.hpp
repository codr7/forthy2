#ifndef FORTHY2_NIL_HPP
#define FORTHY2_NIL_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Nil: Val {
    operator bool() override { return false; }
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  struct NilType: ValType<Nil> {    
    NilType(Cx &cx, Sym &id, vector<Type *> parents = {});
  };
}

#endif
