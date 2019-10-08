#include "forthy2/cx.hpp"
#include "forthy2/forthy2.hpp"
#include "forthy2/libs/abc.hpp"
#include "forthy2/libs/math.hpp"

using namespace std;
using namespace forthy2;

enum struct Mode {repl, run};

void repl(Cx &cx) {
  cx.out << "forthy2." << VERSION << "\n\n";
}

int main(int argc, char *argv[]) {  
  Cx cx;
  init_abc(cx, Pos::_, cx.root_env);
  init_math(cx, Pos::_, cx.root_env);
  
  Mode mode(Mode::repl);

  while (--argc && ++argv) {
    string a(*argv);
    
    if (a == "-debug") {
      cx.debug = not cx.debug;
    } else {
      cx.load(Pos::_, a);
      mode = Mode::run;
    }
  }

  if (mode == Mode::repl) { repl(cx); }
  if (cx.debug) { cx.deinit(); }
  return 0;
}
