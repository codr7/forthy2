#ifndef FORTHY2_OP_PUSH_HPP
#define FORTHY2_OP_PUSH_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct PushOp: Op {
    Val *val;
    
    PushOp(const Pos &pos, Val *val): Op(pos), val(val) {}
    void dump(ostream &out) override;
    Node<Op> *eval(Cx &cx) override;
  };
}

#endif
