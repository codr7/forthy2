#ifndef FORTHY2_METHOD_SET_HPP
#define FORTHY2_METHOD_SET_HPP

#include <set>

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  struct Scope;
  struct Method;
  struct Sym;
  
  struct MethodSet: Val {
    struct Order {
      bool operator() (Method *x, Method *y) const;
    };
    
    using Items = set<Method *, Order>;
    using Iter = Items::iterator;
    
    static MethodSet &get(Cx &cx, Pos pos, Scope &scope, Sym &id, int nargs);

    Items items;
    Sym &id;
    int nargs;

    MethodSet(Sym &id, int nargs);

    Node<Op> &call(Cx &cx,
                   Pos pos,
                   Node<Op> &return_pc,
                   bool safe,
                   bool now) override;
    
    Val &clone(Cx &cx) override;
    Method *dispatch(Cx &cx);
    void dump(ostream &out) override;
    Len len() override;
    bool mark(Cx &cx) override;
    Iter push(Method &m);
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
