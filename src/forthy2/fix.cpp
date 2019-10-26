#include "forthy2/cx.hpp"
#include "forthy2/fix.hpp"

namespace forthy2 {
  void Fix::dump(ostream &out) {
    const int64_t v(trunc());
    const bool _neg(neg());
    if (_neg && !v) { out << '-'; }
    const int64_t f(frac());
    out << v << '.' << setw(scale()) << setfill('0') << (_neg ? -f : f);
  }

  void Fix::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.fix_type.pool.put(*this);
  }

  Type &Fix::type(Cx &cx) { return cx.fix_type; }
}
