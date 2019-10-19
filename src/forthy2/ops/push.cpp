#include "forthy2/cx.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  PushOp::PushOp(Form &form, Node<Op> &prev, Val &val):
    Op(form, prev), val(val) {}

  void PushOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.push_op.put(*this);
  }

  void PushOp::dump(ostream &out) { out << "push " << val; }

  void PushOp::mark_vals(Cx &cx) {
    Op::mark_vals(cx);
    val.mark(cx);
  }
}
