#include "forthy2/cx.hpp"
#include "forthy2/ops/call.hpp"

namespace forthy2 {
  CallOp::CallOp(Form &form, Node<Op> &prev, bool safe): Op(form, prev), safe(safe) {}
  
  void CallOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.call_op.put(*this);
  }

  void CallOp::dump(ostream &out) { out << (safe ? "call-unsafe" : "call"); }

  Node<Op> &CallOp::eval(Cx &cx) {
    return cx.pop(form.pos).call(cx, *this, *this, safe);
  }
}
