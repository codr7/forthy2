#include "forthy2/cx.hpp"
#include "forthy2/forms/ref.hpp"

namespace forthy2 {
  RefForm::RefForm(const Pos &pos, Form &val): Form(pos), val(val) {}

  Node<Op> &RefForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    return val.compile_ref(cx, in, out);
  }

  void RefForm::dealloc(Cx &cx) {
    val.deref(cx);
    cx.ref_form.put(*this);
  }
  
  void RefForm::mark_vals(Cx &cx) { val.mark_vals(cx); }

  void RefForm::write(ostream &out) { out << '&' << val; }
}
