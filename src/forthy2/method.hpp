#ifndef FORTHY2_METHOD_HPP
#define FORTHY2_METHOD_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/fn.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct MethodSet;
  struct Sym;
  
  struct Method: Val {
    using Imp = function<Node<Op> &(Cx &, Pos pos, Node<Op> &)>;

    MethodSet &set;
    Sym &id;
    Args args;
    uint64_t weight;
    MethodSet::Iter iter;
    Fn fn;
    Imp imp;
    
    Method(MethodSet &set,
           Sym &id,
           const vector<Arg> &args,
           uint64_t weight);

    Node<Op> &call(Cx &cx,
                   Pos pos,
                   Node<Op> &return_pc,
                   bool safe,
                   bool now) override;
    
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;    
    Type &type(Cx &cx) override;
  };
}

#endif
