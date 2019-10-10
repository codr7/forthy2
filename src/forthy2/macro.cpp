#include "forthy2/cx.hpp"
#include "forthy2/e.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  Macro::Macro(Sym &id, const vector<Arg> &args): id(id), args(args) {}

  Cmp Macro::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }
  
  void Macro::dump(ostream &out) { out << "Macro@" << this; }

  Node<Op> &Macro::expand(Cx &cx,
                          Form &form,
                          FormIter &in,
                          FormIter end,
                          Node<Op> &out) {
    FormIter i(in);

    for (int j(0); j < args.len(); i++, j++) {
      if (i == end) { throw ESys(form.pos, "Missing args: ", id); }
    }

    return imp(cx, form, in, end, out);
  }

  bool Macro::is(Val &other) { return this == &other; }

  bool Macro::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    args.mark_items(cx);
    return true;
  }

  void Macro::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.macro_type.pool.put(*this);
  }

  Type &Macro::type(Cx &cx) { return cx.macro_type; }
}
