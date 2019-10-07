#ifndef FORTHY2_TYPE_METHOD_HPP
#define FORTHY2_TYPE_METHOD_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Method;
  
  struct MethodVal: TVal<Method &> {
    MethodVal(Method &m);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
  };
}

#endif
