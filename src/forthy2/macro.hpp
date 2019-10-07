#ifndef FORTHY2_MACRO_HPP
#define FORTHY2_MACRO_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/ret.hpp"

namespace forthy2 {
  using namespace std;

  struct Macro {
    using Imp = function<Node<Op> &(Cx &cx,
                                    Stack::Iter &in,
                                    Stack::Iter end,
                                    Node<Op> &out)>;

    const Sym *id;
    Args args;
    Rets rets;
    Imp imp;

    Macro(const Sym *id, const Args &args, const Rets &rets):
      id(id), args(args), rets(rets) {}
  };
}

#endif
