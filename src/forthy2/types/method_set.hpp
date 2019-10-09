#ifndef FORTHY2_TYPE_METHOD_SET_HPP
#define FORTHY2_TYPE_METHOD_SET_HPP

#include "forthy2/node.hpp"
#include "forthy2/method.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using MethodSet = Node<Method>;
  
  struct MethodSetVal: TVal<MethodSet> {
    MethodSetVal();
    void dump(ostream &out) override;
    Cmp cmp(Val &other) override;
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
  };
}

#endif
