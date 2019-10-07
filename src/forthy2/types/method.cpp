#include "forthy2/cx.hpp"
#include "forthy2/types/method.hpp"

namespace forthy2 {
  MethodVal::MethodVal(Method &m): TVal<Method &>(m) {}

  Cmp MethodVal::cmp(Val &other) {
    return forthy2::cmp(&v, &dynamic_cast<MethodVal &>(other).v);
  }

  void MethodVal::dump(ostream &out) { out << "Method@" << this; }

  Type &MethodVal::get_type(Cx &cx) { return cx.method_type; }

  bool MethodVal::is(Val &other) { return &v == &dynamic_cast<MethodVal &>(other).v; }

  void MethodVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_type.pool.put(this);
  }
}
