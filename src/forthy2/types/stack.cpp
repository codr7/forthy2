#include "forthy2/cx.hpp"
#include "forthy2/types/stack.hpp"

namespace forthy2 {
  Type &StackVal::get_type(Cx &cx) { return cx.stack_type; }

  bool StackVal::mark(Cx &cx) {
    bool marked(Val::mark(cx));
    for (Val *v: v.items) { marked |= v->mark(cx); }
    return marked;
  }

  void StackVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_type.pool.put(this);
  }
}
