#include "forthy2/cx.hpp"
#include "forthy2/ops/copy.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  CopyOp::CopyOp(Form &form, Node<Op> &prev): Op(form, prev) {}

  void CopyOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.copy_op.put(*this);
  }

  void CopyOp::dump(ostream &out) { out << "copy"; }
}
