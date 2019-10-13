#include "forthy2/cx.hpp"
#include "forthy2/ops/branch.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  BranchOp::BranchOp(Form &form, Node<Op> &prev): Op(form, prev), pc(nullptr) {}

  void BranchOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.branch_op.put(*this);
  }

  void BranchOp::dump(ostream &out) { out << "branch " << pc->get(); }

  Node<Op> &BranchOp::eval(Cx &cx) {
    if (cx.peek() == neg) {
      if (pop_jump) { cx.pop(); }
      return *pc->next;
    }
    
    if (pop_exit) { cx.pop(); }
    return *Node<Op>::next;
  }
}
