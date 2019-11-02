#include "forthy2/cx.hpp"
#include "forthy2/forms/scope.hpp"

namespace forthy2 {
  ScopeForm::ScopeForm(Pos pos): Form(pos) {}

  Forms ScopeForm::body_forms() {
    Forms out;

    transform(body.begin(), body.end(), back_inserter(out), [&](Val *f) {
        return dynamic_cast<Form *>(f);
      });

    return out;
  }

  
  Node<Op> &ScopeForm::compile(Cx &cx, Forms &in, Node<Op> &out) {    
    Node<Op> *pc(&out);
    Scope scope(cx, *cx.scope);
    Forms fs(body_forms());
    cx.with_scope<void>(scope, [&]() { pc = &cx.compile(fs, *pc); });
    return *pc;
  }

  Node<Op> &ScopeForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Lambda &l(cx.lambda_type.get(cx));
    Node<Op> &pc(cx.compile(*this, *l.ops.prev));
    cx.return_op.get(*this, pc);
    return cx.push_op.get(*this, out, l);
  }

  void ScopeForm::dealloc(Cx &cx) {
    for (Val *f: body) { dynamic_cast<Form *>(f)->deref(cx); }
    cx.scope_form.put(*this);
  }

  void ScopeForm::mark_vals(Cx &cx) {
    for (Val *f: body) { dynamic_cast<Form *>(f)->mark_vals(cx); }
  }

  bool ScopeForm::splice(Cx &cx) {
    for (auto i(body.begin()); i != body.end(); i++) {
      Form *f(dynamic_cast<Form *>(*i));
      
      if (auto *sf(dynamic_cast<SpliceForm *>(*i)); sf) {
        f->deref(cx);
        *i = &cx.pop(pos).to_form(cx, pos);
        return true;
      } else {
        if (f->splice(cx)) { return true; }
      }
    }

    return false;
  }

  Type &ScopeForm::type(Cx &cx) { return cx.scope_type; }

  void ScopeForm::write(ostream &out) {
    out << '{';
    bool sep(false);
    
    for (Val *f: body) {
      if (sep) {
        out << ' ';
      } else {
        sep = true;
      }

      dynamic_cast<Form *>(f)->write(out);
    }
    
    out << '}';
  }
}
