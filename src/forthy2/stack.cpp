#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  void Stack::mark_items(Cx &cx) {
    for (Val *v: items) { v->mark(cx); }
  }
}
