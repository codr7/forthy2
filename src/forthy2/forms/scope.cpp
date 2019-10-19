#include "forthy2/cx.hpp"
#include "forthy2/forms/scope.hpp"

namespace forthy2 {
  ScopeForm::ScopeForm(Pos pos): Form(pos) {}

  Node<Op> &ScopeForm::compile(Cx &cx, Forms &in, Node<Op> &out) {    
    Node<Op> *pc(&out);
    Scope scope(cx, *cx.scope);
    cx.with_scope<void>(scope, [&]() { pc = &cx.compile(body, *pc); });

    if (cte) {
      cx.eval(out, *pc->next);

      while (pc != &out) {
        Op &op(pc->get());
        pc = pc->prev;
        op.dealloc(cx);
      }
      
      return out;
    }

    return *pc;
  }

  Node<Op> &ScopeForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Lambda &l(cx.lambda_type.get(cx));
    Scope scope(cx, *cx.scope);
    
    cx.with_scope<void>(scope, [&]() {
        Node<Op> &pc(compile(cx, in, *l.ops.prev));
        cx.return_op.get(*this, pc);
      });
    
    return cx.push_op.get(*this, out, l);
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
