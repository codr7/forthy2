#ifndef FORTHY2_OP_ROTL_HPP
#define FORTHY2_OP_ROTL_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct RotlOp: Op {
    bool stash;
    
    RotlOp(Form &form, Node<Op> &prev, bool stash);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
