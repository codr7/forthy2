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
    static MethodSet &get(Cx &cx, Pos pos, Scope &scope, Sym &id);

    Node<Method> root;
    Sym &id;
    int len;

    MethodSet(Sym &id);
    Node<Op> &call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) override;
    Method *dispatch(Cx &cx);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    void push(Method &m);
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
