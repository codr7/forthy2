#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/bool.hpp"

namespace forthy2 {
  Bool::Bool(Imp imp): imp(imp) {}

  Cmp Bool::cmp(Val &other) {
    return forthy2::cmp<Imp>(imp, dynamic_cast<Bool &>(other).imp);
  }

  void Bool::dump(ostream &out) { out << (imp ? 'T' : 'F'); }

  void Bool::sweep(Cx &cx) { assert(false); }

  Type &Bool::type(Cx &cx) { return cx.bool_type; }

  BoolType::BoolType(Cx &cx, Sym &id, vector<Type *> parents):
    ValType<Bool>(cx, id, parents) {}
}
