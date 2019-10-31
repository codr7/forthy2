#include "forthy2/cx.hpp"
#include "forthy2/forms/stack.hpp"

namespace forthy2 {
  StackForm::StackForm(Pos pos, const Forms &body): Form(pos), body(body) {}

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

  void StackForm::mark_vals(Cx &cx) {
    for (Form *f: body) { f->mark_vals(cx); }
  }

  bool StackForm::splice(Cx &cx) {
    for (Form *&f: body) {
      if (splice_arg(cx, pos, f)) { return true; }
    }
    
    return false;
  }

  void StackForm::write(ostream &out) { out << '(' << body << ')'; }
}
