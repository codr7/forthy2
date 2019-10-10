#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  static Node<Op> &const_imp(Cx &cx,
                             Form &form,
                             FormIter &in,
                             FormIter end,
                             Node<Op> &out) {
    Form &id(**in++), &val(**in++);
    Node<Op> *op(&out);
    op = &val.compile(cx, end, end, *op);
    Val &id_val(dynamic_cast<IdForm &>(id).val);
    op = &cx.push_op.get(form, *op, id_val);
    return cx.bind_op.get(form, *op);
  }

  static void dump_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.pop(pos).dump(out);
    out << endl;
  }

  void init_abc(Cx &cx, Pos pos, Env &env) {
    env.bind_type(cx, pos, cx.any_type);
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.macro_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_set_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);

    env.add_macro(cx, pos, cx.sym("const"),
                  {{cx.sym_type}, {cx.any_type}}).imp = const_imp;

    env.add_method(cx, pos, cx.sym("dump"),
                   {{cx.any_type}},
                   {}).imp = dump_imp;
  }
}
