#include "forthy2/cx.hpp"
#include "forthy2/iter.hpp"

namespace forthy2 {
  void Iter::dump(ostream &out) { out << "Iter@" << this; }

  Iter &Iter::iter(Cx &cx, Pos pos) { return *this; }

  void Iter::print(Cx &cx, Pos pos, ostream &out) {
    Val *v(nullptr);
    while ((v = pop(cx, pos))) { v->print(cx, pos, out); }
  }

  void Iter::sweep(Cx &cx) { assert(false); }

  Type &Iter::type(Cx &cx) { return cx.iter_type; }
}
