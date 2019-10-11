#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  static Node<Op> &const_imp(Cx &cx,
                             Form &form,
                             FormIter &in,
                             FormIter end,
                             Node<Op> &out) {
    Form &id_form(**in++), &val_form(**in++);
    val_form.eval(cx, in, end);
    Sym &id(dynamic_cast<IdForm &>(id_form).val);
    cx.env->bind(form.pos, id, cx.pop(form.pos));
    return out;
  }

  static void unpair_imp(Cx &cx, Pos pos) {
    auto &p(dynamic_cast<Pair &>(cx.pop()).imp);
    cx.push(*p.first);
    cx.push(*p.second);
  }

  static void dump_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.pop().dump(out);
    out << endl;
  }

  void init_abc(Cx &cx, Pos pos, Env &env) {
    env.bind_type(cx, pos, cx.a_type);
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.macro_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_set_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);

    env.add_macro(cx, pos, cx.sym("const"),
                  {{cx.sym_type}, {cx.a_type}}).imp = const_imp;

    env.add_method(cx, pos, cx.sym(",,"),
                   {{cx.pair_type}},
                   {cx.a_type, cx.a_type}).imp = unpair_imp;

    env.add_method(cx, pos, cx.sym("dump"),
                   {{cx.a_type}},
                   {}).imp = dump_imp;
  }
}
