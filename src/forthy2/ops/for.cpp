#include "forthy2/cx.hpp"
#include "forthy2/ops/for.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  ForOp::ForOp(Form &form, Node<Op> &prev): Op(form, prev), end_pc(nullptr) {}

  void ForOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.for_op.put(*this);
  }

  void ForOp::dump(ostream &out) { out << "for"; }
}
