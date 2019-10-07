#include "forthy2/cx.hpp"
#include "forthy2/types/meta.hpp"

namespace forthy2 {
  MetaVal::MetaVal(Type &val): TVal<Type *>(&val) {}

  Cmp MetaVal::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

  void MetaVal::dump(ostream &out) { out << val->id->name; }

  Type &MetaVal::get_type(Cx &cx) { return cx.meta_type; }

  bool MetaVal::is(Val &other) { return this == &other; }

  void MetaVal::sweep(Cx &cx) {
    Val::sweep(cx);
    delete val;
    cx.type_pool.put(this);
  }
}
