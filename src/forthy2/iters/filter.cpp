#include "forthy2/cx.hpp"
#include "forthy2/iters/filter.hpp"

namespace forthy2 {
  Filter::Filter(Iter &in, Val &pred): in(in), pred(pred) {}

  void Filter::dump(ostream &out) { out << "Filter@" << this; }

  bool Filter::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    in.mark(cx);
    pred.mark(cx);
    return true;
  }

  Val *Filter::pop(Cx &cx, Pos pos) {
    for (;;) {
      Val *in_val(in.pop(cx, pos));
      if (!in_val) { return nullptr; }
      cx.push(*in_val);
      pred.call(cx, pos, cx.ops, true, true);
      if (cx.pop(pos)) { return in_val; }
    }

    return nullptr;
  }

  void Filter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.filter_type.pool.put(*this);
  }

  Type &Filter::type(Cx &cx) { return cx.filter_type; }
}
