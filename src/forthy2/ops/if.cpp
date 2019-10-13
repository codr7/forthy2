#include "forthy2/cx.hpp"
#include "forthy2/ops/if.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  IfOp::IfOp(Form &form, Node<Op> &prev): Op(form, prev), pc(nullptr) {}

  void IfOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.if_op.put(*this);
  }

  void IfOp::dump(ostream &out) { out << "if " << pc->get(); }

  Node<Op> &IfOp::eval(Cx &cx) {
    if (cx.peek() == neg) {
      if (pop_jump) { cx.pop(); }
      return *pc->next;
    }
    
    if (pop_exit) { cx.pop(); }
    return *Node<Op>::next;
  }
}
