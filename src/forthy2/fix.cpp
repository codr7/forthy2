#include "forthy2/cx.hpp"
#include "forthy2/fix.hpp"

namespace forthy2 {
  void Fix::dump(ostream &out) {
    const uint8_t s(scale());
    const int64_t v(trunc() / pow(s));
    const bool neg(negative());
    if (neg && !v) { out << '-'; }
    const int64_t f(frac());
    out << v << '.' << setw(s) << setfill('0') << (neg ? -f : f);
  }

  Type &Fix::get_type(Cx &cx) { return cx.fix_type; }

  void Fix::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.fix_type.pool.put(this);
  }

}
