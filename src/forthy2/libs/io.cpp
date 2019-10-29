#include "forthy2/libs/io.hpp"

namespace forthy2 {
  void init_io(Cx &cx, Pos pos, Scope &scope) {
    using namespace io;
    
    scope.add_method(cx, pos, cx.sym("dump"), {{cx.a_type.or_()}}).imp = dump_imp;
    scope.add_method(cx, pos, cx.sym("dump-stack")).imp = dump_stack_imp;
    scope.add_method(cx, pos, cx.sym("say")).imp = say_imp;
  }
}
