#include "forthy2/cx.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  bool Val::mark(Cx &cx) {
    if (marked) { return false; }
    Node<Val>::del();
    cx.marked_vals.push(*this);
    marked = true;
    return true;
  }
}
