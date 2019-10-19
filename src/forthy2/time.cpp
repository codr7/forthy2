#include "forthy2/cx.hpp"
#include "forthy2/time.hpp"

namespace forthy2 {
  void Time::dump(ostream &out) {
    out << "Time@" << imp.count();
  }

  void Time::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.time_type.pool.put(*this);
  }

  Type &Time::type(Cx &cx) { return cx.time_type; }
}
