#include "forthy2/cx.hpp"
#include "forthy2/int.hpp"

namespace forthy2 {
  Int::Int(Imp imp): imp(imp) {}

  Cmp Int::cmp(Val &other) {
    return forthy2::cmp<Imp>(imp, dynamic_cast<Int &>(other).imp);
  }

  void Int::dump(ostream &out) { out << imp; }

  bool Int::is(Val &other) { return dynamic_cast<Int &>(other).imp == imp; }

  void Int::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.int_type.pool.put(*this);
  }

  Type &Int::type(Cx &cx) { return cx.int_type; }

  IntType::IntType(Cx &cx, Sym &id, vector<Type *> parents):
    PoolType<Int>(cx, id, parents) {}

  Int &IntType::get(Cx &cx, Int::Imp imp) {
    return imp ? PoolType<Int>::get(cx, imp) : cx.int_zero;
  }
}
