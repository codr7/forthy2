#include "forthy2/cx.hpp"
#include "forthy2/forms/scope.hpp"

namespace forthy2 {
  ScopeForm::ScopeForm(Pos pos): Form(pos) {}

  Node<Op> &ScopeForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Scope scope(cx, *cx.scope);
    
    return cx.with_scope<Node<Op> &>(scope, [&]() -> Node<Op> & {
        return cx.compile(body, out);
      });
  }

  Node<Op> &ScopeForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    LambdaOp &lambda_op(cx.lambda_op.get(*this, out));
    Node<Op> *pc(&compile(cx, in, lambda_op));
    pc = &cx.return_op.get(*this, *pc);
    lambda_op.end_pc = pc;
    return *pc;
  }

  void ScopeForm::dealloc(Cx &cx) {
    for (Form *f: body) { f->deref(cx); }
    cx.scope_form.put(*this);
  }

  void ScopeForm::dump(ostream &out) { out << '{' << body << '}'; }

  void ScopeForm::mark_vals(Cx &cx) {
    for (Form *f: body) { f->mark_vals(cx); }
  }
}
