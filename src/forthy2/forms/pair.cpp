#include "forthy2/cx.hpp"
#include "forthy2/forms/pair.hpp"

namespace forthy2 {
  PairForm::PairForm(const Pos &pos, Form &left, Form &right):
    Form(pos), left(&left), right(&right) {}

  Node<Op> &PairForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Node<Op> *op(&out);
    op = &left->compile(cx, in, *op);
    op = &right->compile(cx, in, *op);
    return cx.pair_op.get(*this, *op);
  }

  void PairForm::dealloc(Cx &cx) {
    left->deref(cx);
    right->deref(cx);
    cx.pair_form.put(*this);
  }
  
  void PairForm::mark_vals(Cx &cx) {
    left->mark_vals(cx);
    right->mark_vals(cx);
  }

  Form &PairForm::quote(Cx &cx, Pos pos) {
    left = &left->quote(cx, pos);
    return *this;
  }

  bool PairForm::splice(Cx &cx) {
    return splice_arg(cx, pos, left) || splice_arg(cx, pos, right);
  }

  Val &PairForm::unquote(Cx &cx) {
    cx.marked.push(left->ref());
    cx.marked.push(right->ref());
    return cx.pair_type.get(cx, *left, *right);
  }

  void PairForm::write(ostream &out) {
    left->write(out);
    out << ':';
    right->write(out);
  }
}
