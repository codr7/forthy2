#include "forthy2/e.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  Macro::Macro(const Sym *id, const Args &args, const Rets &rets):
    id(id), args(args), rets(rets) {}

  Node<Op> &Macro::expand(Cx &cx,
                          Form &form,
                          FormIter &in,
                          FormIter end,
                          Node<Op> &out) {
    FormIter i(in);

    for (int j(0); j < args.size(); i++, j++) {
      if (i == end) { throw ESys(form.pos, "Missing args: ", id->name); }
    }

    return imp(cx, form, in, end, out);
  }
}
