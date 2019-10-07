#include "forthy2/forthy2.hpp"
#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/types/int.hpp"
#include "forthy2/types/method.hpp"
#include "forthy2/types/pair.hpp"
#include "forthy2/types/sym.hpp"

using namespace std;
using namespace forthy2;

enum struct Mode {repl, run};

void repl(Cx &cx) {
  cx.out << "forthy2." << VERSION << "\n\n";
}

int main(int argc, char *argv[]) {  
  Cx cx;
  Mode mode(Mode::repl);

  cx.op(cx.push_op, Pos::_, cx.sym_type.get(cx, cx.sym("foo")));
  cx.op(cx.push_op, Pos::_, cx.int_type.get(cx, 42));
  cx.op(cx.bind_op, Pos::_);
  cx.eval(cx.ops);
  
  /*
  cx.env->bind(Pos::_, cx.sym("foo"), cx.int_type.get(cx, 42));
  cx.stack->push(cx.pair_type.get(cx,
                                  cx.int_type.get(cx, 1),
                                  cx.int_type.get(cx, 2)));
  MethodVal *m(cx.method_type.get(cx, "let", Args({{cx.sym_type}}), Rets({}), true));
  cx.stack->push(m);
  */
  
  while (--argc && ++argv) {
    string a(*argv);
    
    if (a == "-debug") {
      cx.debug = not cx.debug;
    } else {
      mode = Mode::run;
    }
  }

  if (mode == Mode::repl) { repl(cx); }
  if (cx.debug) { cx.deinit(); }
  return 0;
}
