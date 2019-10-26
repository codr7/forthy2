#include "forthy2/cx.hpp"
#include "forthy2/ops/swap.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  SwapOp::SwapOp(Form &form, Node<Op> &prev): Op(form, prev) {}

  void SwapOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.swap_op.put(*this);
  }

  void SwapOp::dump(ostream &out) { out << "swap"; }
}
