#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/peek.hpp"

namespace forthy2 {
  void Peek::dump(ostream &out) { out << "Peek@" << offs; }

  void Peek::sweep(Cx &cx) { assert(false); }

  Type &Peek::type(Cx &cx) { return cx.peek_type; }
}
