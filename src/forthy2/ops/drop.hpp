#ifndef FORTHY2_OP_DROP_HPP
#define FORTHY2_OP_DROP_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct DropOp: Op {
    bool stash;
    int offs, n;
    
    DropOp(Form &form, Node<Op> &prev, bool stash, int offs = 0, int n = 1);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
