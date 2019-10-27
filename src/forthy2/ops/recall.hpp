#ifndef FORTHY2_OP_RECALL_HPP
#define FORTHY2_OP_RECALL_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct RecallOp: Op {
    Val &val;
    
    RecallOp(Form &form, Node<Op> &prev, Val &val);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
