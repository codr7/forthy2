#ifndef FORTHY2_OP_FOR_HPP
#define FORTHY2_OP_FOR_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct ForOp: Op {
    Node<Op> *end_pc;
    
    ForOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
