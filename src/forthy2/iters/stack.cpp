#include "forthy2/cx.hpp"
#include "forthy2/iters/stack.hpp"

namespace forthy2 {
  StackIter::StackIter(Stack &in): in(in), i(in.beg()) {}

  void StackIter::dump(ostream &out) { out << "StackIter@" << this; }

  bool StackIter::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    in.mark(cx);
    return true;
  }

  Val *StackIter::pop(Cx &cx, Pos pos) { return (i == in.end()) ? nullptr : *i++; }

  void StackIter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_iter_type.pool.put(*this);
  }

  Type &StackIter::type(Cx &cx) { return cx.stack_iter_type; }
}
