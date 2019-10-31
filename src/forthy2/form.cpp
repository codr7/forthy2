#include "forthy2/cx.hpp"
#include "forthy2/form.hpp"

namespace forthy2 {
  bool Form::splice_arg(Cx &cx, Pos pos, Form *&f) {
    if (!f) { return false; }
    
    if (auto *sf(dynamic_cast<SpliceForm *>(f)); sf) {
      f->deref(cx);
      f = &cx.pop(pos).unquote(cx, pos);
      return true;
    }

    return f->splice(cx);
  }

  Form::Form(Pos pos): pos(pos), nrefs(1) { }

  Form::~Form() { Node<Val>::unlink(); }

  Node<Op> &Form::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    throw ESys(pos, "Invalid ref: ", *this);
  }

  void Form::deref(Cx &cx) {
    if (!--nrefs) { dealloc(cx); }
  }

  void Form::dump(ostream &out) { out << "Form@" << this; }

  void Form::eval(Cx &cx) {
    Node<Op> ops;
    Forms in;
    in.push_back(this);
    cx.compile(in, ops);
    cx.eval(ops, ops);
    cx.dealloc(ops);
  }

  void Form::mark_vals(Cx &cx) {}

  Form &Form::quote(Cx &cx, Pos pos) { return cx.lit_form.get(pos, *this); }

  Form &Form::ref() {
    nrefs++;
    return *this;
  }

  Type &Form::type(Cx &cx) { return cx.form_type; }

  ostream &operator <<(ostream &out, const Form &in) {
    const_cast<Form &>(in).write(out);
    return out;
  }

  ostream &operator <<(ostream &out, const Forms &in) {
    bool sep(false);
    
    for (Form *f: const_cast<Forms &>(in)) {
      if (sep) {
        out << ' ';
      } else {
        sep = true;
      }
      
      f->write(out);
    }

    return out;
  }
}
