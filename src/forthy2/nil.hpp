#ifndef FORTHY2_NIL_HPP
#define FORTHY2_NIL_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Nil: Val {
    operator bool() override { return false; }
    Node<Op> &call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe) override;
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  using NilType = ValType<Nil>;
}

#endif
