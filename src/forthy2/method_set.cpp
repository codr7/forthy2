#include "forthy2/cx.hpp"
#include "forthy2/scope.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  MethodSet &MethodSet::get(Cx &cx, Pos pos, Scope &scope, Sym &id) {
    auto i(scope.find(id));
    
    if (i != scope.items.end() && i->id == &id) {
      return *dynamic_cast<MethodSet *>(i->val);
    }
    
    MethodSet &s(cx.method_set_type.get(cx, id));
    scope.insert(i, id, s);
    return s;
  }

  MethodSet::MethodSet(Sym &id): id(id), len(0) {}
  
  Node<Op> &MethodSet::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    Method *m(dispatch(cx));
    if (!m) { throw ESys(pc.form.pos, "Method not applicable: ", id); }
    return m->call(cx, pc, return_pc, safe);
  }

  Method *MethodSet::dispatch(Cx &cx) {
    for (Node<Method> *i(root.prev); i != &root; i = i->prev) {
      if (Method &m(i->get()); m.applicable(cx)) { return &m; }
    }

    return nullptr;
  }
  
  void MethodSet::dump(ostream &out) {
    out << '(';
    bool first(true);
      
    for (Node<Method> *i(root.next); i != &root; i = i->next) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }
            
      out << i->get().id;
    }

    out << ')';
  }
  
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
