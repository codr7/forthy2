#include "forthy2/cx.hpp"
#include "forthy2/types/method.hpp"

namespace forthy2 {
  MethodVal::MethodVal(const Sym *id, const Args &args, const Rets &rets):
    TVal<Method>(id, args, rets) {}

  Cmp MethodVal::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

  void MethodVal::dump(ostream &out) { out << "Method@" << this; }

  Type &MethodVal::get_type(Cx &cx) { return cx.method_type; }

  bool MethodVal::is(Val &other) { return this == &other; }

  void MethodVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_type.pool.put(this);
  }
}
