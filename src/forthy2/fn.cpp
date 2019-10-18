#include "forthy2/cx.hpp"
#include "forthy2/fn.hpp"

namespace forthy2 {
  Fn::Fn(Node<Op> &beg_pc, Node<Op> &end_pc):
    beg_pc(beg_pc), end_pc(end_pc) { }

  Node<Op> &Fn::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    cx.push_call(pc, *this, return_pc);
    return *beg_pc.next;
  }
  
  void Fn::dump(ostream &out) { out << "Fn@" << this; }

  Type &Fn::type(Cx &cx) { return cx.fn_type; }
}
