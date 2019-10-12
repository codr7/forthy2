#include "forthy2/cx.hpp"
#include "forthy2/forms/pair.hpp"

namespace forthy2 {
  PairForm::PairForm(const Pos &pos, Form &left, Form &right):
    Form(pos), left(left), right(right) {}

  Node<Op> &PairForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Node<Op> *op(&out);
    op = &left.compile(cx, in, *op);
    op = &right.compile(cx, in, *op);
    return cx.pair_op.get(*this, *op);
  }

  void PairForm::dealloc(Cx &cx) {
    left.deref(cx);
    right.deref(cx);
    cx.pair_form.put(*this);
  }

  void PairForm::dump(ostream &out) {
    left.dump(out);
    out << ' ';
    right.dump(out);
    out << ',';
  }
  
  void PairForm::mark_vals(Cx &cx) {
    left.mark_vals(cx);
    right.mark_vals(cx);
  }
}
