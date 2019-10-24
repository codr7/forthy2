#ifndef FORTHY2_OP_REPEAT_HPP
#define FORTHY2_OP_REPEAT_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct RepeatOp: Op {
    Node<Op> *end_pc;
    
    RepeatOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
