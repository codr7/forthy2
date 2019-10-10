#include "forthy2/cx.hpp"
#include "forthy2/ops/call.hpp"

namespace forthy2 {
  CallOp::CallOp(Form &form, Node<Op> &prev): Op(form, prev) {}
  
  void CallOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.call_op.put(this);
  }

  void CallOp::dump(ostream &out) { out << "call"; }

  Node<Op> &CallOp::eval(Cx &cx) {
    cx.stack->pop().call(cx, form.pos);
    return *Node<Op>::next;
  }
}
