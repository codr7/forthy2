#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/nil.hpp"

namespace forthy2 {
  Node<Op> &Nil::call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe, bool now) {
    return *return_pc.next;
  }

  Cmp Nil::cmp(Val &other) { return Cmp::Eq; }

  void Nil::dump(ostream &out) { out << '_'; }

  void Nil::iter(Cx &cx, Pos pos, IterBody body) {}

  void Nil::sweep(Cx &cx) { assert(false); }

  Type &Nil::type(Cx &cx) { return cx.nil_type; }
}
