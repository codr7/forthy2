#include "forthy2/cx.hpp"
#include "forthy2/iters/val.hpp"

namespace forthy2 {
  ValIter::ValIter(Val &val): val(&val) {}

  void ValIter::dump(ostream &out) { out << "ValIter@" << this; }

  bool ValIter::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    if (val) { val->mark(cx); }
    return true;
  }

  Val *ValIter::pop(Cx &cx, Pos pos) {
    if (!val) { return nullptr; }
    Val *tmp(val);
    val = nullptr;
    return tmp;
  }

  void ValIter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.val_iter_type.pool.put(*this);
  }

  Type &ValIter::type(Cx &cx) { return cx.val_iter_type; }
}
