#ifndef FORTHY2_OP_CHECK_HPP
#define FORTHY2_OP_CHECK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct CheckOp: Op {
    Form &body;
    
    CheckOp(Form &form, Node<Op> &prev, Form &body);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
    void mark_vals(Cx &cx) override; 
  };
}

#endif
