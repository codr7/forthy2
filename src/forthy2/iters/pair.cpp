#include "forthy2/cx.hpp"
#include "forthy2/iters/pair.hpp"

namespace forthy2 {
  PairIter::PairIter(Val &left, Val &right): left(&left), right(&right) {}

  void PairIter::dump(ostream &out) { out << "PairIter@" << this; }

  bool PairIter::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    if (left) { left->mark(cx); }
    if (right) { right->mark(cx); }
    return true;
  }

  Val *PairIter::pop(Cx &cx, Pos pos) {
    if (left) {
      Val *tmp(left);
      left = nullptr;
      return tmp;
    }

    if (right) {
      Val *tmp(right);
      right = nullptr;
      return tmp;
    }
    
    return nullptr;
  }

  void PairIter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.pair_iter_type.pool.put(*this);
  }

  Type &PairIter::type(Cx &cx) { return cx.pair_iter_type; }
}
