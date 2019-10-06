#include "forthy2/cx.hpp"
#include "forthy2/ops/bind.hpp"

namespace forthy2 {
  void BindOp::dump(ostream &out) { out << "bind"; }

  Node<Op> *BindOp::eval(Cx &cx) {
    Val *val(cx.stack->pop()), *id(cx.stack->pop());
    cx.env->bind(pos, dynamic_cast<SymVal *>(id)->v, val);
    return Node<Op>::next;
  }
}
