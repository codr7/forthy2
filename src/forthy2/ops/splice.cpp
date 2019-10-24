#include "forthy2/cx.hpp"
#include "forthy2/ops/splice.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  SpliceOp::SpliceOp(Form &form, Node<Op> &prev): Op(form, prev) {}
  
  void SpliceOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.splice_op.put(*this);
  }

  void SpliceOp::dump(ostream &out) { out << "splice"; }

  Node<Op> &SpliceOp::eval(Cx &cx) {
    Stack &vals(cx.pop(form.pos, cx.stack_type));
    Form &dest(cx.peek(form.pos, cx.form_type));
    dest.splice(cx, vals);
    return *Node<Op>::next;
  }
}
