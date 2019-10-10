#include "forthy2/cx.hpp"
#include "forthy2/ops/pair.hpp"

namespace forthy2 {
  PairOp::PairOp(Form &form, Node<Op> &prev): Op(form, prev) {}
  
  void PairOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.pair_op.put(this);
  }

  void PairOp::dump(ostream &out) { out << "pair"; }

  Node<Op> &PairOp::eval(Cx &cx) {
    Val &r(cx.stack->pop()), &l(cx.stack->pop());
    cx.stack->push(cx.pair_type.get(cx, l, r));
    return *Node<Op>::next;
  }
}
