#ifndef FORTHY2_LIB_ABC_HPP
#define FORTHY2_LIB_ABC_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  static Node<Op> &const_imp(Cx &cx,
                             Pos &pos,
                             Stack::Iter &in,
                             Stack::Iter end,
                             Node<Op> &out) {
    Val &id(**in++), &val(**in++);
    Node<Op> *op(&out);
    op = cx.push_op.get(*op, pos, id);
    op = cx.push_op.get(*op, pos, val);
    return *cx.bind_op.get(*op, pos);
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

#endif
