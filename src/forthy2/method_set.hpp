#ifndef FORTHY2_METHOD_SET_HPP
#define FORTHY2_METHOD_SET_HPP

#include "forthy2/node.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  struct Env;
  struct Method;
  struct Sym;
  
  struct MethodSet: Val {
    static MethodSet &get(Cx &cx, Pos pos, Env &env, Sym &id);

    Node<Method> root;
    int len;

    MethodSet();
    void call(Cx &cx, Pos pos) override;
    Method *dispatch(Cx &cx);
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    bool mark(Cx &cx) override;
    void push(Method &m);
    void sweep(Cx &cx) override;
  };
}

#endif
