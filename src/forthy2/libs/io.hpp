#ifndef FORTHY2_LIB_IO_HPP
#define FORTHY2_LIB_IO_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_io(Cx &cx, Pos pos, Scope &scope);

  namespace io {
    inline Node<Op> &dump_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &out(*cx.stdout);
      cx.pop().dump(out);
      out << endl;
      return *return_pc.next;
    }

    inline Node<Op> &dump_stack_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &out(*cx.stdout);
      cx.stack->dump(out);
      out << endl;
      return *return_pc.next;
    }

    inline Node<Op> &say_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &out(*cx.stdout);
      cx.pop().print(cx, pos, out);
      out << endl;
      return *return_pc.next;
    }
  }
}

#endif
