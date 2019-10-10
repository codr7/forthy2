#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/ret.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct MethodSet;
  struct Sym;
  
  struct Method: Node<Method>, Val {
    using Imp = function<void (Cx &cx, Pos pos)>;

    MethodSet &set;
    Sym &id;
    Args args;
    Rets rets;
    uint64_t weight;
    Imp imp;

    Method(MethodSet &set,
           Sym &id,
           const vector<Arg> &args,
           const vector<Ret> &rets,
           uint64_t weight);

    bool applicable(Cx &cx);
    void call(Cx &cx, Pos pos) override;
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;    
    Type &type(Cx &cx) override;
  };
}

#endif
