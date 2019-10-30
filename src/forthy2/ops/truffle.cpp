#include "forthy2/cx.hpp"
#include "forthy2/ops/truffle.hpp"

namespace forthy2 {
  TruffleOp::TruffleOp(Form &form, Node<Op> &prev, Int::Imp in_len, bool stash):
    Op(form, prev), in_len(in_len), stash(stash), end_pc(nullptr) {}

  void TruffleOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.truffle_op.put(*this);
  }

  void TruffleOp::dump(ostream &out) { out << "truffle"; }
}
