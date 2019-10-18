#ifndef FORTHY2_FN_HPP
#define FORTHY2_FN_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Fn: Val {
    Node<Op> &beg_pc, &end_pc;
    
    Fn(Node<Op> &beg_pc, Node<Op> &end_pc);
    Node<Op> &call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) override;
    void dump(ostream &out) override;
    Type &type(Cx &cx) override;
  };

  using FnType = ValType<Fn>;
}

#endif
