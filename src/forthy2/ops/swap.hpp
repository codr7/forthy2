#ifndef FORTHY2_OP_SWAP_HPP
#define FORTHY2_OP_SWAP_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct SwapOp: Op {
    bool stash;
    
    SwapOp(Form &form, Node<Op> &prev, bool stash);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
