#include "forthy2/cx.hpp"
#include "forthy2/bool.hpp"

namespace forthy2 {
  Bool::Bool(Imp imp): imp(imp) {}

  Cmp Bool::cmp(Val &other) {
    return forthy2::cmp<Imp>(imp, dynamic_cast<Bool &>(other).imp);
  }

  void Bool::dump(ostream &out) { out << (imp ? "true" : "false"); }

  bool Bool::is(Val &other) { return dynamic_cast<Bool &>(other).imp == imp; }

  void Bool::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.bool_type.pool.put(*this);
  }

  Type &Bool::type(Cx &cx) { return cx.bool_type; }

  BoolType::BoolType(Cx &cx, Sym &id, vector<Type *> parents):
    PoolType<Bool>(cx, id, parents) {}

  Bool &BoolType::get(Cx &cx, bool imp) { return imp ? cx.T : cx.F; }
}
