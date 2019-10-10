#ifndef FORTHY2_OP_BIND_HPP
#define FORTHY2_OP_BIND_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct BindOp: Op {
    BindOp(Form &form, Node<Op> &prev): Op(form, prev) {}
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
