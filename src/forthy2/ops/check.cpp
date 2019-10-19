#include "forthy2/cx.hpp"
#include "forthy2/ops/check.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  CheckOp::CheckOp(Form &form, Node<Op> &prev, Form &body):
    Op(form, prev), body(body) {}
  
  void CheckOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    body.deref(cx);
    cx.check_op.put(*this);
  }

  void CheckOp::dump(ostream &out) { out << "check " << body; }

  Node<Op> &CheckOp::eval(Cx &cx) {
    if (!cx.pop(form.pos)) { throw ESys(form.pos, "Check failed: ", body); }
    return *Node<Op>::next;
  }

  void CheckOp::mark_vals(Cx &cx) {
    Op::mark_vals(cx);
    body.mark_vals(cx);
  }
}
