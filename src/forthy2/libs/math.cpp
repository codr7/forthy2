#include "forthy2/cx.hpp"
#include "forthy2/libs/math.hpp"

namespace forthy2 {
  static void int_add_imp(Cx &cx) {
    Val &y(cx.stack->pop()), &x(cx.stack->pop());
    cx.stack->push(cx.int_val.get(cx,
                                  dynamic_cast<IntVal &>(x).val +
                                  dynamic_cast<IntVal &>(y).val));
  }
  
  void init_math(Cx &cx, const Pos &pos, Env &env) {
    env.bind_type(cx, pos, cx.fix_val);

    env.add_method(cx, pos, cx.sym("+"),
                   {{cx.int_val}, {cx.int_val}},
                   {cx.int_val}).imp = int_add_imp;
  }
}
