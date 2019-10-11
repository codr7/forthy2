#include "forthy2/cx.hpp"
#include "forthy2/form.hpp"

namespace forthy2 {
  Form::Form(Pos pos): pos(pos), cte(false), nrefs(1) { }

  Form::~Form() {}
    
  void Form::deref(Cx &cx) {
    if (!--nrefs) { dealloc(cx); }
  }

  void Form::eval(Cx &cx, FormIter &in, FormIter end) {
    Node<Op> &pc(*cx.ops.prev);
    compile(cx, in, end, pc);
    cx.eval(pc);
    while (cx.ops.prev != &pc) { cx.ops.prev->get().dealloc(cx); }
  }

  void Form::mark_vals(Cx &cx) {}

  Form &Form::ref() {
    nrefs++;
    return *this;
  }

  ostream &operator <<(ostream &out, Form &form) {
    form.dump(out);
    return out;
  }
}
