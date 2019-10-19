#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/nil.hpp"

namespace forthy2 {
  Node<Op> &Nil::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    return *return_pc.next;
  }

  Cmp Nil::cmp(Val &other) { return Cmp::Eq; }

  void Nil::dump(ostream &out) { out << '_'; }

  void Nil::sweep(Cx &cx) { assert(false); }

  Type &Nil::type(Cx &cx) { return cx.nil_type; }
}
