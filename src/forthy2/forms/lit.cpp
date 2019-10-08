#include "forthy2/cx.hpp"
#include "forthy2/forms/lit.hpp"

namespace forthy2 {
  LitForm::LitForm(const Pos &pos, Val &val): Form(pos), val(val) {}

  void LitForm::dealloc(Cx &cx) { cx.lit_form.put(this); }

  void LitForm::dump(ostream &out) {
    out << "lit ";
    val.dump(out);
  }
  
  void LitForm::mark_vals(Cx &cx) { val.mark(cx); }
}
