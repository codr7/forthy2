#include "forthy2/cx.hpp"
#include "forthy2/ops/call.hpp"

namespace forthy2 {
  CallOp::CallOp(Form &form, Node<Op> &prev, Val *val, bool safe):
    Op(form, prev), val(val), safe(safe) {}
  
  void CallOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.call_op.put(*this);
  }

  void CallOp::dump(ostream &out) { out << (safe ? "call-unsafe" : "call"); }

  void CallOp::mark_vals(Cx &cx) {
    Op::mark_vals(cx);
    if (val) { val->mark(cx); }
  }
}
