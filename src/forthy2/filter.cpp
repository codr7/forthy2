#include "forthy2/cx.hpp"
#include "forthy2/filter.hpp"

namespace forthy2 {
  Filter::Filter(Val &in, Val &pred): in(in), pred(pred) {}

  void Filter::dump(ostream &out) { out << "Filter@" << this; }

  void Filter::iter(Cx &cx, Pos pos, IterBody body) {
    in.iter(cx, pos, [&](Val &in_val) {
        cx.push(in_val);
        pred.call(cx, pos, cx.ops, true, true);
        if (cx.pop(pos)) { body(in_val); }
        return true;
      });
  }

  bool Filter::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    in.mark(cx);
    pred.mark(cx);
    return true;
  }

  void Filter::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.filter_type.pool.put(*this);
  }

  Type &Filter::type(Cx &cx) { return cx.filter_type; }
}
