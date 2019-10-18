#ifndef FORTHY2_OP_LAMBDA_HPP
#define FORTHY2_OP_LAMBDA_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct LambdaOp: Op {
    Node<Op> *end_pc;
    optional<Lambda> val;
    
    LambdaOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
