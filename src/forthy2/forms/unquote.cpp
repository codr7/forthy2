#include "forthy2/cx.hpp"
#include "forthy2/forms/unquote.hpp"

namespace forthy2 {
  UnquoteForm::UnquoteForm(const Pos &pos, Form &val): Form(pos), val(val) {}

  Node<Op> &UnquoteForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {
    return val.compile(cx, in, out, quote - 1);
  }

  void UnquoteForm::dealloc(Cx &cx) {
    val.deref(cx);
    cx.unquote_form.put(*this);
  }

  void UnquoteForm::mark_vals(Cx &cx) { val.mark_vals(cx); }

  void UnquoteForm::write(ostream &out) {
    out << "unquote ";
    val.write(out);
  }
}
