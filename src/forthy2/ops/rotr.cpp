#include "forthy2/cx.hpp"
#include "forthy2/ops/rotr.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  RotrOp::RotrOp(Form &form, Node<Op> &prev): Op(form, prev) {}

  void RotrOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.rotr_op.put(*this);
  }

  void RotrOp::dump(ostream &out) { out << "rotr"; }
}
