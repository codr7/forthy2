#include "forthy2/cx.hpp"
#include "forthy2/forms/stack.hpp"

namespace forthy2 {
  StackForm::StackForm(Pos pos): Form(pos) {}

  Node<Op> &StackForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    StackOp &s(cx.stack_op.get(*this, out));
    Node<Op> &end_pc(cx.compile(body, s));
    s.end_pc = &end_pc;
    return end_pc;
  }

  void StackForm::dealloc(Cx &cx) {
    for (Form *f: body) { f->deref(cx); }
    cx.stack_form.put(*this);
  }

  void StackForm::dump(ostream &out) { out << '(' << body << ')'; }

  void StackForm::mark_vals(Cx &cx) {
    for (Form *f: body) { f->mark_vals(cx); }
  }
}
