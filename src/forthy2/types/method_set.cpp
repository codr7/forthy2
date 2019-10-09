#include "forthy2/cx.hpp"
#include "forthy2/types/method_set.hpp"

namespace forthy2 {
  MethodSetVal::MethodSetVal(): TVal<MethodSet>() {}

  void MethodSetVal::dump(ostream &out) {
    out << '(';
    bool first(true);
      
    for (Node<Method> *i(val.next); i != &val; i = i->next) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }
            
      forthy2::dump(i->get().args, out);
    }

    out << ')';
  }

  Cmp MethodSetVal::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }
  
  Type &MethodSetVal::get_type(Cx &cx) { return cx.method_set_val; }

  bool MethodSetVal::is(Val &other) { return this == &other; }

  void MethodSetVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_set_val.pool.put(this);
  }
}
