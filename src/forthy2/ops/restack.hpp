#ifndef FORTHY2_OP_RESTACK_HPP
#define FORTHY2_OP_RESTACK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct RestackOp: Op {
    Int::Imp in_len;
    Node<Op> *end_pc;
    
    RestackOp(Form &form, Node<Op> &prev, Int::Imp in_len);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
