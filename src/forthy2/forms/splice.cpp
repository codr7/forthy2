#include "forthy2/cx.hpp"
#include "forthy2/forms/splice.hpp"

namespace forthy2 {
  SpliceForm::SpliceForm(const Pos &pos, Form &val): Form(pos), val(val) {}

  Node<Op> &SpliceForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {
    return val.compile(cx, in, out, quote - 1);
  }

  void SpliceForm::dealloc(Cx &cx) {
    val.deref(cx);
    cx.splice_form.put(*this);
  }

  void SpliceForm::mark_vals(Cx &cx) { val.mark_vals(cx); }

  void SpliceForm::write(ostream &out) {
    out << '%';
    val.write(out);
  }
}
