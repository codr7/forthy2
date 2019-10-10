#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  MethodSet::MethodSet() {}

  MethodSet &MethodSet::get(Cx &cx, Pos pos, Env &env, Sym &id) {
    auto i(env.find(id));
    
    if (i != env.items.end() && *i->id == id) {
      return *dynamic_cast<MethodSet *>(i->val);
    }
    
    MethodSet &s(cx.method_set_type.get(cx));
    env.insert(i, id, s);
    return s;
  }
  
  void MethodSet::call(Cx &cx, Pos pos) {
    Method *m(dispatch(cx));
    if (!m) { throw ESys(pos, "Method not applicable"); }
    m->call(cx, pos);
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
