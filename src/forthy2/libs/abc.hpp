#ifndef FORTHY2_LIB_ABC_HPP
#define FORTHY2_LIB_ABC_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  /*
  static Node<Op> &const_imp(Cx &cx,
                             Stack::Iter &in,
                             Stack::Iter end,
                             Node<Op> &out) {
    return out;
  }
  */
  
  void init_abc(Cx &cx, const Pos &pos, Env &env) {
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);

    //env.add_macro(cx, pos, cx.sym("const"), {{cx.sym_type}, {cx.any_type}}, {}, const_imp);
  }
}

#endif
