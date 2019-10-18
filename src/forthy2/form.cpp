#include "forthy2/cx.hpp"
#include "forthy2/form.hpp"

namespace forthy2 {
  Form::Form(Pos pos): pos(pos), cte(false), nrefs(1) { }

  Form::~Form() {}

  Node<Op> &Form::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    throw ESys(pos, "Invalid ref: ", *this);
  }

  void Form::deref(Cx &cx) {
    if (!--nrefs) { dealloc(cx); }
  }

  void Form::eval(Cx &cx, Forms &in) {
    Node<Op> &pc(*cx.ops.prev);
    compile(cx, in, pc);
    cx.eval(pc, cx.ops);
    while (cx.ops.prev != &pc) { cx.ops.prev->get().dealloc(cx); }
  }

  void Form::mark_vals(Cx &cx) {}

  Form &Form::ref() {
    nrefs++;
    return *this;
  }

  ostream &operator <<(ostream &out, const Form &in) {
    const_cast<Form &>(in).dump(out);
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
      
      f->dump(out);
    }

    return out;
  }
}
