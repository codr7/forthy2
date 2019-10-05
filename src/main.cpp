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

  cx.env->bind(Pos::_, cx.sym("foo"), int_type.get(cx, 42));
  cx.stack->push(pair_type.get(cx, int_type.get(cx, 1), int_type.get(cx, 2)));
  MethodVal *m(method_type.get(cx, "let", Args({{sym_type}}), Rets({}), true));
  cx.stack->push(m);
  
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
