#include "forthy2/cx.hpp"
#include "forthy2/types/stack.hpp"

namespace forthy2 {
  Val &StackVal::clone(Cx &cx) { return cx.stack_val.get(cx, val); }

  Type &StackVal::get_type(Cx &cx) { return cx.stack_val; }

  bool StackVal::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (Val *v: val.items) { v->mark(cx); }
    return true;
  }

  void StackVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_val.pool.put(this);
  }
}
