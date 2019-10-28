#include "forthy2/cx.hpp"
#include "forthy2/iter.hpp"

namespace forthy2 {
  void Iter::dump(ostream &out) { out << "Iter@" << this; }

  Iter &Iter::iter(Cx &cx, Pos pos) { return *this; }

  void Iter::sweep(Cx &cx) { assert(false); }

  Type &Iter::type(Cx &cx) { return cx.iter_type; }
}
