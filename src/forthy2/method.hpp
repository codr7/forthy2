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

    string id;
    Args args;
    Rets rets;
    Imp imp;
    
    MethodVal val;
    
    Method(const string &id, const Args &args, const Rets &rets, bool macro):
      id(id), args(args), rets(rets), val(*this) {}
  };
}

#endif
