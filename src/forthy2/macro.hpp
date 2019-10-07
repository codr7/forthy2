#ifndef FORTHY2_MACRO_HPP
#define FORTHY2_MACRO_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/ret.hpp"

namespace forthy2 {
  using namespace std;

  struct Macro {
    using Imp = function<void (Cx &cx,
                               Stack::Iter &in,
                               Stack::Iter end,
                               Node<Op> &prev)>;

    string id;
    Args args;
    Rets rets;
    Imp imp;

    Macro(const string &id, const Args &args, const Rets &rets, bool macro):
      id(id), args(args), rets(rets) {}
  };
}

#endif
