#include "forthy2/cx.hpp"
#include "forthy2/types/int.hpp"

namespace forthy2 {
  Type &IntVal::get_type(Cx &cx) { return cx.int_type; }

  void IntVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.int_type.pool.put(this);
  }
}
