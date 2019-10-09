#include "forthy2/cx.hpp"
#include "forthy2/types/method.hpp"

namespace forthy2 {
  MethodVal::MethodVal(const Sym *id,
                       uint64_t weight,
                       const Args &args,
                       const Rets &rets):
    TVal<Method>(id, weight, args, rets) {}

  Cmp MethodVal::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

  void MethodVal::dump(ostream &out) { out << "Method@" << this; }

  Type &MethodVal::get_type(Cx &cx) { return cx.method_val; }

  bool MethodVal::is(Val &other) { return this == &other; }

  void MethodVal::sweep(Cx &cx) {
    Val::sweep(cx);
    val.unlink();
    cx.method_val.pool.put(this);
  }
}
