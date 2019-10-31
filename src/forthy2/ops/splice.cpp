#include "forthy2/cx.hpp"
#include "forthy2/ops/splice.hpp"

namespace forthy2 {
  SpliceOp::SpliceOp(Form &form, Node<Op> &prev): Op(form, prev) {}
  
  void SpliceOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.splice_op.put(*this);
  }

  void SpliceOp::dump(ostream &out) { out << "splice"; }
}
