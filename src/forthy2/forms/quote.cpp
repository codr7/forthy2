#include "forthy2/cx.hpp"
#include "forthy2/forms/quote.hpp"

namespace forthy2 {
  QuoteForm::QuoteForm(const Pos &pos, Form &val): Form(pos), val(&val) {}

  Node<Op> &QuoteForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    return val->quote(cx, pos).compile(cx, in, out);
  }

  void QuoteForm::dealloc(Cx &cx) {
    val->deref(cx);
    cx.quote_form.put(*this);
  }

  void QuoteForm::mark_vals(Cx &cx) { val->mark_vals(cx); }

  bool QuoteForm::splice(Cx &cx) { return splice_arg(cx, pos, val); }

  void QuoteForm::write(ostream &out) {
    out << '\'';
    val->write(out);
  }
}
