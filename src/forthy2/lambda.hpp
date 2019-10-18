#ifndef FORTHY2_LAMBDA_HPP
#define FORTHY2_LAMBDA_HPP

#include "forthy2/fn.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Lambda: Fn {
    void dump(ostream &out) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  using LambdaType = PoolType<Lambda>;
}

#endif
