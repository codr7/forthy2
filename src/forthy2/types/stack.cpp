#include "forthy2/cx.hpp"
#include "forthy2/types/stack.hpp"

namespace forthy2 {
  Type &StackVal::get_type(Cx &cx) { return cx.stack_type; }

  bool StackVal::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (Val *v: v.items) { v->mark(cx); }
    return true;
  }

  void StackVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_type.pool.put(this);
  }
}
