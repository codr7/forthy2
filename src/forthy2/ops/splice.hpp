#ifndef FORTHY2_OP_SPLICE_HPP
#define FORTHY2_OP_SPLICE_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct SpliceOp: Op {
    SpliceOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
