#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Macro &Env::add_macro(Cx &cx, const Pos &pos, const Sym *id, Args args, Rets rets) {
    MacroVal &m(cx.macro_type.get(cx, id, args, rets));
    bind(pos, id, m);
    return m.val;
  }

  void Env::bind_type(Cx &cx, const Pos &pos, Type &type) {
    bind(pos, type.id, type.val);
  }

  void Env::mark_items(Cx &cx) {
    for (Item it: items) { it.val->mark(cx); }
  }
}
