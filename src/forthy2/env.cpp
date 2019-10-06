#include "forthy2/env.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  bool Env::mark_items(Cx &cx) {
    bool marked(false);
    for (Item it: items) { marked |= it.val->mark(cx); }
    return marked;
  }
}
