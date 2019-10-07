#include "forthy2/cx.hpp"
#include "forthy2/types/pair.hpp"

namespace forthy2 {
  Type &PairVal::get_type(Cx &cx) { return cx.pair_type; }

  bool PairVal::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    val.first->mark(cx);
    val.second->mark(cx);
    return true;
  }

  void PairVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.pair_type.pool.put(this);
  }
}
