#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  MethodSet &MethodSet::get(Cx &cx, Pos pos, Env &env, Sym &id) {
    auto found(env.find(id));
    
    if (found != env.items.end() && *found->id == id) {
      return *dynamic_cast<MethodSet *>(found->val);
    }
    
    MethodSet &s(cx.method_set_type.get(cx));
    env.bind(pos, id, s);
    return s;
  }
  
  MethodSet::MethodSet(): len(0) {}

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
  
  Type &MethodSet::get_type(Cx &cx) { return cx.method_set_type; }

  bool MethodSet::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }

    for (Node<Method> *i(root.next); i != &root; i = i->next) {
      i->get().mark(cx);
    }

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
    cx.method_set_type.pool.put(this);
  }
}
