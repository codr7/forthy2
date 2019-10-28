#include "forthy2/cx.hpp"
#include "forthy2/forms/pair.hpp"

namespace forthy2 {
  PairForm::PairForm(const Pos &pos, Form &left, Form &right):
    Form(pos), left(left), right(right) {}

  Node<Op> &PairForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {
    Node<Op> *op(&out);
    op = &left.compile(cx, in, *op, quote);
    op = &right.compile(cx, in, *op, quote);
    return cx.pair_op.get(*this, *op);
  }

  void PairForm::dealloc(Cx &cx) {
    left.deref(cx);
    right.deref(cx);
    cx.pair_form.put(*this);
  }
  
  void PairForm::mark_vals(Cx &cx) {
    left.mark_vals(cx);
    right.mark_vals(cx);
  }

  void PairForm::write(ostream &out) {
    left.write(out);
    out << ':';
    right.write(out);
  }
}
