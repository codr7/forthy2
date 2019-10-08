#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  static Node<Op> &const_imp(Cx &cx, Form &form, FormIter &in, Node<Op> &out) {
    Form &id(**in++), &val(**in++);
    Node<Op> *op(&out);
    Val &id_val(cx.sym_type.get(cx, dynamic_cast<IdForm &>(id).val));
    op = cx.push_op.get(form, *op, id_val);
    op = cx.push_op.get(form, *op, dynamic_cast<LitForm &>(val).val);
    return *cx.bind_op.get(form, *op);
  }
  
  void init_abc(Cx &cx, const Pos &pos, Env &env) {
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.macro_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);

    env.add_macro(cx, pos, cx.sym("const"),
                  {{cx.sym_type}, {cx.any_type}},
                  {}).imp = const_imp;
  }
}
