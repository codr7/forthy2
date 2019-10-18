#include "forthy2/cx.hpp"
#include "forthy2/fn.hpp"

namespace forthy2 {  
  void Fn::dump(ostream &out) { out << "Fn@" << this; }

  Type &Fn::type(Cx &cx) { return cx.fn_type; }

  bool Fn::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }

    for (Node<Op> *op(ops.next); op != &ops; op = op->next) {
      op->get().mark_vals(cx);
    }

    return true;
  }

  void Fn::sweep(Cx &cx) {
    Val::sweep(cx);

    for (Node<Op> *op(ops.next); op != &ops;) {
      Node<Op> *next(op->next);
      op->get().dealloc(cx);
      op = next;
    }
  }
}
