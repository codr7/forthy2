#include "forthy2/cx.hpp"
#include "forthy2/forms/splice.hpp"

namespace forthy2 {
  SpliceForm::SpliceForm(const Pos &pos): Form(pos) {}

  Node<Op> &SpliceForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    throw ESys(pos, "Missing splice");
  }

  Form &SpliceForm::quote(Cx &cx, Pos pos) { return cx.quote_form.get(pos, *this); }

  void SpliceForm::dealloc(Cx &cx) { cx.splice_form.put(*this); }

  void SpliceForm::write(ostream &out) { out << '%'; }
}
