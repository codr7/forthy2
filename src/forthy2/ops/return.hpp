#ifndef FORTHY2_OP_RETURN_HPP
#define FORTHY2_OP_RETURN_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct ReturnOp: Op {
    ReturnOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
