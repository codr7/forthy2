#include "forthy2/cx.hpp"
#include "forthy2/types/method.hpp"

namespace forthy2 {
  Type &MethodVal::get_type(Cx &cx) { return cx.method_type; }

  void MethodVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_type.pool.put(this);
  }
}
