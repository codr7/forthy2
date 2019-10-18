#include "forthy2/op.hpp"

namespace forthy2 {
  Op::Op(Form &form, Node<Op> &prev): form(form.ref()) { prev.append(*this); }

  Op::~Op() {}
    
  void Op::dealloc(Cx &cx) {
    form.deref(cx);
    Node<Op>::unlink();
  }
    
  Node<Op> &Op::eval(Cx &cx) { return *Node<Op>::next; }
  void Op::mark_vals(Cx &cx) { form.mark_vals(cx); } 

  ostream &operator <<(ostream &out, const Op &op) {
    const_cast<Op &>(op).dump(out);
    return out;
  }
}

