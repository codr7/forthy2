#include "forthy2/cx.hpp"
#include "forthy2/ops/drop.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  DropOp::DropOp(Form &form, Node<Op> &prev, bool stash, int offs, int n):
    Op(form, prev), stash(stash), offs(offs), n(n) {}

  void DropOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.drop_op.put(*this);
  }

  void DropOp::dump(ostream &out) { out << "drop"; }
}
