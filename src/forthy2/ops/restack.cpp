#include "forthy2/cx.hpp"
#include "forthy2/ops/restack.hpp"

namespace forthy2 {
  RestackOp::RestackOp(Form &form, Node<Op> &prev, Int::Imp in_len):
    Op(form, prev), in_len(in_len), end_pc(nullptr) {}

  void RestackOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.restack_op.put(*this);
  }

  void RestackOp::dump(ostream &out) { out << "restack"; }
}
