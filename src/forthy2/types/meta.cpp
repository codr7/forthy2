#include "forthy2/cx.hpp"
#include "forthy2/types/meta.hpp"

namespace forthy2 {
  MetaVal::MetaVal(Type &t): TVal<Type &>(t) {}

  Cmp MetaVal::cmp(Val &other) {
    return forthy2::cmp(&v, &dynamic_cast<MetaVal &>(other).v);
  }

  void MetaVal::dump(ostream &out) { out << v.id; }

  Type &MetaVal::get_type(Cx &cx) { return cx.meta_type; }

  bool MetaVal::is(Val &other) { return &v == &dynamic_cast<MetaVal &>(other).v; }

  void MetaVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.meta_type.pool.put(this);
  }
}
