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
    MethodSet *set(nullptr);
    auto found(find(id));
    
    if (found == items.end() || found->id != id) {
      MethodSetVal &s(cx.method_set_val.get(cx));
      bind(pos, id, s);
      set = &s.val;
    } else {
      set = &dynamic_cast<MethodSetVal *>(found->val)->val;
    }

    MethodVal &v(cx.method_val.get(cx,
                                   cx.get_id(id, args),
                                   cx.get_weight(args),
                                   args,
                                   rets));
    
    Method &m(v.val);
    bind(pos, m.id, v);

    Node<Method> *i(set->next);
    for (; i != set && i->get().weight <= m.weight; i = i->next);
    i->push(m);
    return m;
  }

  void Env::bind_type(Cx &cx, const Pos &pos, Type &type) {
    bind(pos, type.id, type.val);
  }

  void Env::mark_items(Cx &cx) {
    for (Item it: items) { it.val->mark(cx); }
  }
}
