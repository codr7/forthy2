#include "forthy2/cx.hpp"
#include "forthy2/types/meta.hpp"

namespace forthy2 {
  MetaVal::MetaVal(Type &v): TVal<Type *>(&v) {}

  Cmp MetaVal::cmp(Val &other) {
    return forthy2::cmp(v, dynamic_cast<MetaVal &>(other).v);
  }

  void MetaVal::dump(ostream &out) { out << v->id->name; }

  Type &MetaVal::get_type(Cx &cx) { return cx.meta_type; }

  bool MetaVal::is(Val &other) { return v == dynamic_cast<MetaVal &>(other).v; }

  void MetaVal::sweep(Cx &cx) {
    Val::sweep(cx);
    delete v;
    cx.type_pool.put(this);
  }
}
