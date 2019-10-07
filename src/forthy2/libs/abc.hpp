#ifndef FORTHY2_LIB_ABC_HPP
#define FORTHY2_LIB_ABC_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_abc(Cx &cx, const Pos &pos, Env &env) {
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);
  }
}

#endif
