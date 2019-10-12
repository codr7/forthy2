#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/nil.hpp"

namespace forthy2 {
  Cmp Nil::cmp(Val &other) { return Cmp::Eq; }

  void Nil::dump(ostream &out) { out << '_'; }

  bool Nil::is(Val &other) { return this == &other; }

  void Nil::sweep(Cx &cx) { assert(false); }

  Type &Nil::type(Cx &cx) { return cx.nil_type; }

  NilType::NilType(Cx &cx, Sym &id, vector<Type *> parents):
    ValType<Nil>(cx, id, parents) {}
}
