#ifndef FORTHY2_OP_TRUFFLE_HPP
#define FORTHY2_OP_TRUFFLE_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct TruffleOp: Op {
    Int::Imp in_len;
    bool stash;
    Node<Op> *end_pc;
    
    TruffleOp(Form &form, Node<Op> &prev, Int::Imp in_len, bool stash);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
    void eval_imp(Cx &cx);
  };
}

#endif
