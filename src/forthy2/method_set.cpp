#include "forthy2/cx.hpp"
#include "forthy2/scope.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  MethodSet &MethodSet::get(Cx &cx, Pos pos, Scope &scope, Sym &id, int nargs) {
    auto i(scope.find(id));
    
    if (i != scope.items.end() && i->id == &id) {
      auto &ms(*dynamic_cast<MethodSet *>(i->val));

      if (nargs != ms.nargs) {
        ESys(pos, "Argument count mismatch (", nargs, "): ", id);
      }
      
      return ms;
    }
    
    MethodSet &s(cx.method_set_type.get(cx, id, nargs));
    scope.insert(i, id, s);
    return s;
  }

  MethodSet::MethodSet(Sym &id, int nargs): id(id), nargs(nargs), len(0) {}
  
  void MethodSet::dump(ostream &out) { out << "MethodSet@" << this; }

  bool MethodSet::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (Node<Method> *i(root.next); i != &root; i = i->next) { i->get().mark(cx); }
    return true;
  }
  
  void MethodSet::push(Method &m) {
    Node<Method> *i(root.next);
    for (; i != &root && i->get().weight <= m.weight; i = i->next);
    i->push(m);
    len++;
  }

  void MethodSet::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_set_type.pool.put(*this);
  }

  Type &MethodSet::type(Cx &cx) { return cx.method_set_type; }
}
