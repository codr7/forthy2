#include "forthy2/cx.hpp"
#include "forthy2/types/fix.hpp"

namespace forthy2 {
  FixVal::FixVal(Fix val): PrimVal<Fix>(val) {}

  void FixVal::dump(ostream &out) { fix::dump(val, out); }

  Type &FixVal::get_type(Cx &cx) { return cx.fix_type; }

  void FixVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.fix_type.pool.put(this);
  }
}
