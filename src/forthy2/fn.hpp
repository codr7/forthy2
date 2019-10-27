#ifndef FORTHY2_FN_HPP
#define FORTHY2_FN_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Fn: Val {
    Node<Op> ops;
    
    Node<Op> &call(Cx &cx,
                   Pos pos,
                   Node<Op> &return_pc,
                   bool safe,
                   bool now) override;
    
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;    
    Type &type(Cx &cx) override;
  };

  using FnType = ValType<Fn>;
}

#endif
