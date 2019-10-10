#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  Sym::Sym(const string &name): name(name) {}

  void Sym::dump(ostream &out) { out << name; }

  void Sym::sweep(Cx &cx) { assert(false); }

  ostream &operator <<(ostream &out, const Sym &sym) {
    out << sym.name;
    return out;
  }

  Type &Sym::type(Cx &cx) { return cx.sym_type; }
}
