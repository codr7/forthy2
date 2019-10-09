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
    Val &id_val(cx.sym_val.get(cx, dynamic_cast<IdForm &>(id).val));
    op = cx.push_op.get(form, *op, id_val);
    return *cx.bind_op.get(form, *op);
  }
  
  void init_abc(Cx &cx, const Pos &pos, Env &env) {
    env.bind_type(cx, pos, cx.any_type);
    env.bind_type(cx, pos, cx.meta_type);

    env.bind_type(cx, pos, cx.int_val);
    env.bind_type(cx, pos, cx.macro_val);
    env.bind_type(cx, pos, cx.method_set_val);
    env.bind_type(cx, pos, cx.method_val);
    env.bind_type(cx, pos, cx.pair_val);
    env.bind_type(cx, pos, cx.stack_val);
    env.bind_type(cx, pos, cx.sym_val);

    env.add_macro(cx, pos, cx.sym("const"),
                  {{cx.sym_val}, {cx.any_type}},
                  {}).imp = const_imp;
  }
}
