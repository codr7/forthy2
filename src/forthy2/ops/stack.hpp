#ifndef FORTHY2_OP_STACK_HPP
#define FORTHY2_OP_STACK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct StackOp: Op {
    Node<Op> *end_pc;

    StackOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
