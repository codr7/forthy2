#include "forthy2/cx.hpp"
#include "forthy2/iters/zip.hpp"

namespace forthy2 {
  Zip::Zip(Iter &left, Iter &right): left(left), right(right) {}

  void Zip::dump(ostream &out) { out << "Zip@" << this; }

  bool Zip::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    left.mark(cx);
    right.mark(cx);
    return true;
  }

  Val *Zip::get_next(Cx &cx, Pos pos) {
    Val *l(left.get_next(cx, pos));
    if (!l) { return nullptr; }
    Val *r(right.get_next(cx, pos));
    if (!r) { return nullptr; }
    return &cx.pair_type.get(cx, *l, *r);
  }

  void Zip::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.zip_type.pool.put(*this);
  }

  Type &Zip::type(Cx &cx) { return cx.zip_type; }
}
