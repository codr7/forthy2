#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  Sym::Sym(string_view name): name(name) {}

  void Sym::dump(ostream &out) { out << '\'' << name; }

  void Sym::print(Cx &cx, Pos pos, ostream &out) { out << name; }

  void Sym::sweep(Cx &cx) { assert(false); }

  Type &Sym::type(Cx &cx) { return cx.sym_type; }

  Form &Sym::unquote(Cx &cx, Pos pos) { return cx.id_form.get(pos, *this); }
}
