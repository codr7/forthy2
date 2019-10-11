#include "forthy2/cx.hpp"
#include "forthy2/forms/scope.hpp"

namespace forthy2 {
  ScopeForm::ScopeForm(Pos pos): Form(pos) {}

  Node<Op> &ScopeForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Env env(*cx.env);
    
    return cx.with_env<Node<Op> &>(env, [&]() -> Node<Op> & {
        return cx.compile(body, out);
      });
  }

  void ScopeForm::dealloc(Cx &cx) {
    for (Form *f: body) { f->deref(cx); }
    cx.scope_form.put(*this);
  }

  void ScopeForm::dump(ostream &out) { out << '{' << body << '}' << endl; }
}
