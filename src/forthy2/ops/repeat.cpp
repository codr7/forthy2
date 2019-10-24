#include "forthy2/cx.hpp"
#include "forthy2/ops/repeat.hpp"

namespace forthy2 {
  RepeatOp::RepeatOp(Form &form, Node<Op> &prev): Op(form, prev), end_pc(nullptr) {}

  void RepeatOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.repeat_op.put(*this);
  }

  void RepeatOp::dump(ostream &out) { out << "repeat"; }
}
