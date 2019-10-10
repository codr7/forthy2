#include "forthy2/cx.hpp"
#include "forthy2/ops/bind.hpp"

namespace forthy2 {
  void BindOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.bind_op.put(*this);
  }

  void BindOp::dump(ostream &out) { out << "bind"; }

  Node<Op> &BindOp::eval(Cx &cx) {
    Val &id(cx.pop(form.pos)), &val(cx.pop(form.pos));
    cx.env->bind(form.pos, dynamic_cast<Sym &>(id), val);
    return *Node<Op>::next;
  }
}
