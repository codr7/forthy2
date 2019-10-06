#include "forthy2/cx.hpp"
#include "forthy2/types/pair.hpp"

namespace forthy2 {
  Type &PairVal::get_type(Cx &cx) { return cx.pair_type; }

  bool PairVal::mark(Cx &cx) {
    Val::mark(cx);
    bool marked(v.first->mark(cx));
    marked |= v.second->mark(cx);
    return marked;
  }

  void PairVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.pair_type.pool.put(this);
  }
}
