#include "forthy2/cx.hpp"
#include "forthy2/ops/if.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  IfOp::IfOp(Form &form, Node<Op> &prev, bool neg):
    Op(form, prev), pc(nullptr), neg(neg) {}

  void IfOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.if_op.put(*this);
  }

  void IfOp::dump(ostream &out) { out << "if " << pc->get(); }

  Node<Op> &IfOp::eval(Cx &cx) {
    if (cx.peek() != neg) { return *pc->next; }
    cx.pop();
    return *Node<Op>::next;
  }
}
