#ifndef FORTHY2_OP_BRANCH_HPP
#define FORTHY2_OP_BRANCH_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct BranchOp: Op {
    Node<Op> *pc;
    bool neg = false, pop_jump = false, pop_exit = false;
    
    BranchOp(Form &form, Node<Op> &prev);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
  };
}

#endif
