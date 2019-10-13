#ifndef FORTHY2_OP_IF_HPP
#define FORTHY2_OP_IF_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct IfOp: Op {
    Node<Op> *pc;
    bool neg;
    
    IfOp(Form &form, Node<Op> &prev, bool neg = false);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
