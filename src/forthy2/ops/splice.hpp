#ifndef FORTHY2_OP_SPLICE_HPP
#define FORTHY2_OP_SPLICE_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct SpliceOp: Op {
    Form &vals;

    SpliceOp(Form &form, Node<Op> &prev, Form &vals);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
    void mark_vals(Cx &cx) override; 
  };
}

#endif
