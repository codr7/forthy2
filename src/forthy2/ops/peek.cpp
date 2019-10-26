#include "forthy2/cx.hpp"
#include "forthy2/ops/peek.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  PeekOp::PeekOp(Form &form, Node<Op> &prev, bool alt_src, int offs):
    Op(form, prev), alt_src(alt_src), offs(offs) {}

  void PeekOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.peek_op.put(*this);
  }

  void PeekOp::dump(ostream &out) { out << "peek"; }
}
