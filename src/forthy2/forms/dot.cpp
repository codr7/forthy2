#include "forthy2/cx.hpp"
#include "forthy2/forms/dot.hpp"

namespace forthy2 {
  DotForm::DotForm(Pos pos, Form &y, Form &z):
    Form(pos), y(y.ref()), z(z.ref()) {}

  Node<Op> &DotForm::compile(Cx &cx, FormIter &in, FormIter end, Node<Op> &out) {
    Node<Op> *op(&out);
    op = &y.compile(cx, end, end, *op);
    return z.compile(cx, end, end, *op);
  }

  void DotForm::dealloc(Cx &cx) {
    y.deref(cx);
    z.deref(cx);
    cx.dot_form.put(this);
  }

  void DotForm::dump(ostream &out) {
    out << '.';
    y.dump(out);
    out << ' ';
    z.dump(out);
  }
  
  void DotForm::mark_vals(Cx &cx) {
    y.mark_vals(cx);
    z.mark_vals(cx);
  }
}
