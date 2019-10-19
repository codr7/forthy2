#include "forthy2/cx.hpp"
#include "forthy2/pair.hpp"

namespace forthy2 {
  Pair::Pair(const Imp &imp): imp(imp) {}

  Pair::Pair(Val &first, Val &second): imp(&first, &second) {}

  Cmp Pair::cmp(Val &other) {
    Imp &other_imp(dynamic_cast<Pair &>(other).imp);
    Cmp first(imp.first->cmp(*other_imp.first));
    return (first == Cmp::Eq) ? imp.second->cmp(*other_imp.second) : first;
  }

  void Pair::dump(ostream &out) {
    out << ',';
    imp.first->dump(out);
    out << ' ';
    imp.second->dump(out);
  }
  
  bool Pair::eq(Val &other) {
    Imp &other_imp(dynamic_cast<Pair &>(other).imp);
    return other_imp.first->eq(*imp.first) && other_imp.second->eq(*imp.second);
  }

  bool Pair::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    imp.first->mark(cx);
    imp.second->mark(cx);
    return true;
  }

  void Pair::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.pair_type.pool.put(*this);
  }

  Type &Pair::type(Cx &cx) { return cx.pair_type; }
}
