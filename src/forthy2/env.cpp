#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Macro &Env::add_macro(Cx &cx,
                        const Pos &pos,
                        const Sym *id,
                        Args args,
                        Rets rets) {
    MacroVal &v(cx.macro_val.get(cx, id, args, rets));
    bind(pos, id, v);
    return v.val;
  }

  Method &Env::add_method(Cx &cx,
                          const Pos &pos,
                          const Sym *id,
                          Args args,
                          Rets rets) {
    MethodVal &v(cx.method_val.get(cx, id, args, rets));
    bind(pos, id, v);
    return v.val;
  }

  void Env::bind_type(Cx &cx, const Pos &pos, Type &type) {
    bind(pos, type.id, type.val);
  }

  void Env::mark_items(Cx &cx) {
    for (Item it: items) { it.val->mark(cx); }
  }
}
