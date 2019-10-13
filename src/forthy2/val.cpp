#include "forthy2/cx.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  void Val::call(Cx &cx, Pos pos) { cx.push(*this); }

  bool Val::mark(Cx &cx) {
    if (marked) { return false; }
    if (Type &t(type(cx)); this != &t) { t.mark(cx); }
    Node<Val>::unlink();
    cx.marked_vals.push(*this);
    marked = true;
    return true;
  }


  ostream &operator <<(ostream &out, const Val &val) {
    const_cast<Val &>(val).dump(out);
    return out;
  }
}
