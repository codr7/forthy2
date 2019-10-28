#ifndef FORTHY2_OP_PEEK_HPP
#define FORTHY2_OP_PEEK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct PeekOp: Op {
    bool alt_src;
    size_t offs;
    
    PeekOp(Form &form, Node<Op> &prev, bool alt_src, int offs = 0);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
