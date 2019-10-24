#include "forthy2/cx.hpp"
#include "forthy2/forms/scope.hpp"

namespace forthy2 {
  ScopeForm::ScopeForm(Pos pos): Form(pos) {}

  Node<Op> &ScopeForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {    
    if (quote > 0) {
      cx.marked.push(*this);
      return cx.push_op.get(*this, out, *this);
    }
    
    Node<Op> *pc(&out);
    Scope scope(cx, *cx.scope);
    cx.with_scope<void>(scope, [&]() { pc = &cx.compile(body, *pc); });
    return *pc;
  }

  Node<Op> &ScopeForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Lambda &l(cx.lambda_type.get(cx));
    Scope scope(cx, *cx.scope);
    
    cx.with_scope<void>(scope, [&]() {
        Node<Op> &pc(compile(cx, in, *l.ops.prev, 0));
        cx.return_op.get(*this, pc);
      });
    
    return cx.push_op.get(*this, out, l);
  }

  void ScopeForm::dealloc(Cx &cx) {
    for (Form *f: body) { f->deref(cx); }
    cx.scope_form.put(*this);
  }

  void ScopeForm::mark_vals(Cx &cx) {
    for (Form *f: body) { f->mark_vals(cx); }
  }

  int ScopeForm::splice(Cx &cx, int n) {
    for (auto i(body.begin()); n && i != body.end(); i++) {
      if (auto *sf(dynamic_cast<SpliceForm *>(*i)); sf) {
        (*i)->deref(cx);
        *i = &cx.pop(pos).unquote(cx, pos);
        n--;
      } else {
        n = (*i)->splice(cx, n);
      }
    }

    return n;
  }

  void ScopeForm::write(ostream &out) { out << '{' << body << '}'; }
}
