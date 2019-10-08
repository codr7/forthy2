#include "forthy2/cx.hpp"
#include "forthy2/ops/bind.hpp"

namespace forthy2 {
  void BindOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.bind_op.put(this);
  }

  void BindOp::dump(ostream &out) { out << "bind"; }

  Node<Op> *BindOp::eval(Cx &cx) {
    Val &val(cx.stack->pop()), &id(cx.stack->pop());
    cx.env->bind(form.pos, dynamic_cast<SymVal &>(id).val, val);
    return Node<Op>::next;
  }
}
