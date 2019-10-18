#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/fn.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct MethodSet;
  struct Sym;
  
  struct Method: Node<Method>, Val {
    using Imp = function<Node<Op> &(Cx &, Op &)>;

    MethodSet &set;
    Sym &id;
    Args args;
    uint64_t weight;
    Fn fn;
    Imp imp;
    
    Method(MethodSet &set, Sym &id, const vector<Arg> &args, uint64_t weight);
    bool applicable(Cx &cx);
    Node<Op> &call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) override;
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;    
    Type &type(Cx &cx) override;
  };
}

#endif
