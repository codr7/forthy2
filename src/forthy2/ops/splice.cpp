#include "forthy2/cx.hpp"
#include "forthy2/ops/splice.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  SpliceOp::SpliceOp(Form &form, Node<Op> &prev, Form &vals):
    Op(form, prev), vals(vals) {}
  
  void SpliceOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    vals.deref(cx);
    cx.splice_op.put(*this);
  }

  void SpliceOp::dump(ostream &out) { out << "splice " << vals; }

  Node<Op> &SpliceOp::eval(Cx &cx) {
    Form &dest(cx.peek(form.pos, cx.form_type));
    vals.eval(cx, 0);
    Stack &vs(cx.pop(form.pos, cx.stack_type));
    dest.splice(cx, vs);
    return *Node<Op>::next;
  }

  void SpliceOp::mark_vals(Cx &cx) {
    Op::mark_vals(cx);
    vals.mark_vals(cx);
  }
}
