#include "forthy2/cx.hpp"
#include "forthy2/forms/pair.hpp"

namespace forthy2 {
  PairForm::PairForm(const Pos &pos, Form &left, Form &right):
    Form(pos), left(left.ref()), right(right.ref()) {}

  void PairForm::dealloc(Cx &cx) {
    left.deref(cx);
    right.deref(cx);
    cx.pair_form.put(this);
  }

  void PairForm::dump(ostream &out) {
    out << "pair ";
    left.dump(out);
    out << ',';
    right.dump(out);
  }
  
  void PairForm::mark_vals(Cx &cx) {
    left.mark_vals(cx);
    right.mark_vals(cx);
  }
}
