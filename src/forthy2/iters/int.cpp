#include "forthy2/cx.hpp"
#include "forthy2/iters/int.hpp"

namespace forthy2 {
  IntIter::IntIter(Int::Imp i, Int::Imp max): i(i), max(max) {}

  void IntIter::dump(ostream &out) { out << "IntIter@" << this; }

  Val *IntIter::get_next(Cx &cx, Pos pos) {
    return (i == max) ? nullptr : &cx.int_type.get(cx, i++);
  }

  void IntIter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.int_iter_type.pool.put(*this);
  }

  Type &IntIter::type(Cx &cx) { return cx.int_iter_type; }
}
