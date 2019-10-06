#include "forthy2/cx.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  void PushOp::dump(ostream &out) {
    out << "push ";
    val->dump(out);
  }

  Node<Op> *PushOp::eval(Cx &cx) {
    cx.stack->push(val);
    return Node<Op>::next;
  }
}
