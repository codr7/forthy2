#include "forthy2/cx.hpp"
#include "forthy2/fn.hpp"

namespace forthy2 {
  Node<Op> &Fn::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    cx.push_call(pc, *this, return_pc);
    return *ops.next;
  }
  
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
