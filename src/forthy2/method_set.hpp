#ifndef FORTHY2_METHOD_SET_HPP
#define FORTHY2_METHOD_SET_HPP

#include "forthy2/node.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  struct Scope;
  struct Method;
  struct Sym;
  
  struct MethodSet: Val {
    static MethodSet &get(Cx &cx, Pos pos, Scope &scope, Sym &id, int nargs);

    Node<Method> root;
    Sym &id;
    int nargs;
    int _len;

    MethodSet(Sym &id, int nargs);

    Node<Op> &call(Cx &cx,
                   Pos pos,
                   Node<Op> &return_pc,
                   bool safe,
                   bool now) override;
    
    Method *dispatch(Cx &cx);
    void dump(ostream &out) override;
    Len len() override { return _len; }
    bool mark(Cx &cx) override;
    void push(Method &m);
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
