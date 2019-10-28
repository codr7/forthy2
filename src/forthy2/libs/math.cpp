#include "forthy2/libs/math.hpp"

namespace forthy2 {
  void init_math(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.fix_type);    
    
    scope.add_method(cx, pos, cx.sym("+"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_add_imp;

    scope.add_method(cx, pos, cx.sym("+!"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_add_bang_imp;

    scope.add_method(cx, pos, cx.sym("/"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_div_imp;

    scope.add_method(cx, pos, cx.sym("*"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_mul_imp;

    scope.add_method(cx, pos, cx.sym("-"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_sub_imp;


    scope.add_method(cx, pos, cx.sym("fix"),
                     {{cx.int_type}, {cx.int_type}}).imp = fix_imp;
    
    scope.add_method(cx, pos, cx.sym("+"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_add_imp;

    scope.add_method(cx, pos, cx.sym("+!"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_add_bang_imp;

    scope.add_method(cx, pos, cx.sym("/"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_div_imp;

    scope.add_method(cx, pos, cx.sym("*"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_mul_imp;

    scope.add_method(cx, pos, cx.sym("-"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_sub_imp;
  }
}
