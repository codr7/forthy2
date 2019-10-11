#ifndef FORTHY2_OP_CHECK_HPP
#define FORTHY2_OP_CHECK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct CheckOp: Op {
    Node<Op> &body_pc;
    
    CheckOp(Form &form, Node<Op> &prev, Node<Op> &body_pc);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
