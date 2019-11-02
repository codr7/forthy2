#include "forthy2/libs/meta.hpp"

namespace forthy2 {
  void init_meta(Cx &cx, Pos pos, Scope &scope) {
    using namespace meta;

    scope.add_method(cx, pos, cx.sym("body"), {{cx.scope_type}}).imp = body_imp;
    scope.add_method(cx, pos, cx.sym("compile"), {{cx.form_type}}).imp = compile_imp;

    scope.add_macro(cx, pos, cx.sym("macro"),
                    {{cx.sym_type}, {cx.stack_type}, {cx.a_type}}).imp = macro_imp;
  }
}
