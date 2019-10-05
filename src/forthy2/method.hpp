#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/imp.hpp"
#include "forthy2/ret.hpp"

namespace forthy2 {
  using namespace std;

  struct Method {
    string id;
    Args args;
    Rets rets;
    bool macro;
    Imp imp;

    Method(const string &id, const Args &args, const Rets &rets, bool macro):
      id(id), args(args), rets(rets), macro(macro) {}
  };
}

#endif
