#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  bool Stack::mark_items(Cx &cx) {
    bool marked(false);
    for (Val *v: items) { marked |= v->mark(cx); }
    return marked;
  }
}
