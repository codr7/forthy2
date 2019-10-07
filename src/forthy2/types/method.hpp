#ifndef FORTHY2_TYPE_METHOD_HPP
#define FORTHY2_TYPE_METHOD_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Method;
  
  struct MethodVal: TVal<Method &> {
    template <typename...Args>
    MethodVal(Args &&...args): TVal<Method>(forward<Args>(args)...) {}

    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
  };
}

#endif
