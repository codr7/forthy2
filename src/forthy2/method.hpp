#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/ret.hpp"
#include "forthy2/types/method.hpp"

namespace forthy2 {
  using namespace std;

  struct Method {
    using Imp = function<void (Cx &cx)>;

    const Sym *id;
    Args args;
    Rets rets;
    Imp imp;    

    Method(const Sym *id, const Args &args, const Rets &rets):
      id(id), args(args), rets(rets) {}
  };
}

#endif
