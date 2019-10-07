#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  void Env::bind_type(Cx &cx, const Pos &pos, Type &type) {
    bind(pos, cx.sym(type.id), cx.meta_type.get(cx, type));
  }

  bool Env::mark_items(Cx &cx) {
    bool marked(false);
    for (Item it: items) { marked |= it.val->mark(cx); }
    return marked;
  }
}
