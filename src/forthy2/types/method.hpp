#ifndef FORTHY2_TYPE_METHOD_HPP
#define FORTHY2_TYPE_METHOD_HPP

#include "forthy2/method.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/ref_val.hpp"

namespace forthy2 {
  struct Method;
  
  struct MethodVal: RefVal<Method> {
    template <typename...Args>
    MethodVal(Args &&...args): RefVal<Method>(forward<Args>(args)...) {}
    Type &type() override;
  };

  struct MethodType: PoolType<MethodVal> {
    MethodType(const string &id): PoolType<MethodVal>(id) {}
  };

  extern MethodType method_type;
}

#endif
