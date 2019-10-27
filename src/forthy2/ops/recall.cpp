#include "forthy2/cx.hpp"
#include "forthy2/ops/recall.hpp"

namespace forthy2 {
  RecallOp::RecallOp(Form &form, Node<Op> &prev, Val &val):
    Op(form, prev), val(val) {}

  void RecallOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.recall_op.put(*this);
  }

  void RecallOp::dump(ostream &out) { out << "recall " << val; }
}
