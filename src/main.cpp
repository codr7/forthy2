#include "forthy2/cx.hpp"
#include "forthy2/forthy2.hpp"
#include "forthy2/libs/abc.hpp"
#include "forthy2/libs/math.hpp"

using namespace std;
using namespace forthy2;

enum struct Mode {repl, run};

void repl(Cx &cx) {
  (*cx.stdout) <<
    "forthy2." << VERSION << "\n\n" <<
    "Press Return on empty row to evaluate." << endl <<
    "Empty input clears stack and Ctrl+D exits." << endl << endl <<
    "  ";

  stringstream buf;
  string line;
  
  while (getline(*(cx.stdin), line)) {
    if (line.empty()) {
      if (buf.tellp()) {
        try {
          cx.eval(buf);
        } catch (const exception &e) {
          if (cx.debug) { throw; }
          (*cx.stdout) << e.what() << endl;
        }
      } else {
        cx.stack->clear();
      }
        
      cx.stack->dump_items(*cx.stdout);
      (*cx.stdout) << endl;
      stringstream().swap(buf);
    } else {
      buf << line << endl;
    }

    (*cx.stdout) << "  ";
  }
}

int main(int argc, char *argv[]) {  
  Cx cx;
  init_abc(cx, Pos::_, cx.root_scope);
  init_math(cx, Pos::_, cx.root_scope);
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
