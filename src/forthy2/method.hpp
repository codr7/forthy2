#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/node.hpp"
#include "forthy2/ret.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Sym;
  
  struct Method: Node<Method> {
    using Imp = function<void (Cx &cx)>;
    
    const Sym *id;
    uint64_t weight;
    Args args;
    Rets rets;
    Imp imp;

    Method(const Sym *id, uint64_t weight, const Args &args, const Rets &rets);
  };
}

#endif
