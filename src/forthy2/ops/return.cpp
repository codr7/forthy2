#include "forthy2/cx.hpp"
#include "forthy2/ops/return.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  ReturnOp::ReturnOp(Form &form, Node<Op> &prev): Op(form, prev) {}

  void ReturnOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.return_op.put(*this);
  }

  void ReturnOp::dump(ostream &out) { out << "return"; }

  Node<Op> &ReturnOp::eval(Cx &cx) { return *cx.pop_call().next; }
}
