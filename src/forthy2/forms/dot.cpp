#include "forthy2/cx.hpp"
#include "forthy2/forms/dot.hpp"

namespace forthy2 {
  DotForm::DotForm(Pos pos, Form *x, Form *y, Form &z):
    Form(pos), x(x), y(y), z(&z) {}

  Node<Op> &DotForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Sym &id(dynamic_cast<IdForm &>(*z).val);
    Val &v(cx.scope->get(pos, id));
    Type &vt(v.type(cx));
    
    if (&vt == &cx.macro_type) {
      if (y) { in.push_back(y); }
      if (x) { in.push_back(x); }
      in.push_back(z);
    } else if (&vt == &cx.method_type || &vt == &cx.method_set_type) {
      in.push_back(z);
      if (y) { in.push_back(y); }
      if (x) { in.push_back(x); }
    } else {
      throw ESys(pos, "Invalid dot z: ", vt.id);
    }

    return out;
  }

  void DotForm::dealloc(Cx &cx) {
    if (x) { x->deref(cx); }
    if (y) { y->deref(cx); }
    z->deref(cx);
    cx.dot_form.put(*this);
  }
  
  void DotForm::mark_vals(Cx &cx) {
    if (x) { x->mark_vals(cx); }
    if (y) { y->mark_vals(cx); }
    z->mark_vals(cx);
  }

  Form &DotForm::quote(Cx &cx, Pos pos) {
    x = &x->quote(cx, pos);
    return *this;
  }

  bool DotForm::splice(Cx &cx) {
    return splice_arg(cx, pos, x) || splice_arg(cx, pos, y) || splice_arg(cx, pos, z);
  }

  void DotForm::write(ostream &out) {
    if (x) { x->write(out); }
    out << '.';
    z->write(out);

    if (y) {
      out << ' ';
      y->write(out);
    }
  }
}
