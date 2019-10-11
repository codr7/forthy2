#include "forthy2/cx.hpp"
#include "forthy2/forms/dot.hpp"

namespace forthy2 {
  DotForm::DotForm(Pos pos, Form *x, Form *y, Form &z): Form(pos), x(x), y(y), z(z) {}

  Node<Op> &DotForm::compile(Cx &cx, FormIter &in, FormIter end, Node<Op> &out) {
    Node<Op> *op(&out);

    Sym &id(dynamic_cast<IdForm &>(z).val);
    Val &v(cx.env->get(pos, id));
    Type &vt(v.type(cx));

    if (&vt == &cx.macro_type) {
      op = &z.compile(cx, end, end, *op);
      if (x) { op = &x->compile(cx, end, end, *op); }
      if (y) { op = &y->compile(cx, end, end, *op); }
    } else if (&vt == &cx.method_type || &vt == &cx.method_set_type) {
      if (x) { op = &x->compile(cx, end, end, *op); }
      if (y) { op = &y->compile(cx, end, end, *op); }
      op = &z.compile(cx, end, end, *op);
    } else {
      throw ESys(pos, "Invalid dot z: ", vt.id);
    }
    
    return *op;
  }

  void DotForm::dealloc(Cx &cx) {
    if (x) { x->deref(cx); }
    if (y) { y->deref(cx); }
    z.deref(cx);
    cx.dot_form.put(*this);
  }

  void DotForm::dump(ostream &out) {
    if (x) { x->dump(out); }
    out << '.';
    z.dump(out);
    if (y) {
      out << ' ';
      y->dump(out);
    }
  }
  
  void DotForm::mark_vals(Cx &cx) {
    if (x) { x->mark_vals(cx); }
    if (y) { y->mark_vals(cx); }
    z.mark_vals(cx);
  }
}
