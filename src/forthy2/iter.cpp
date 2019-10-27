#include "forthy2/cx.hpp"
#include "forthy2/iter.hpp"

namespace forthy2 {
  Iter::Iter(Imp imp): imp(imp) {}

  void Iter::dump(ostream &out) { out << "Iter@" << this; }

  void Iter::iter(Cx &cx, IterBody body) { imp(body); }
  
  void Iter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.iter_type.pool.put(*this);
  }
  
  Type &Iter::type(Cx &cx) { return cx.iter_type; }
}
