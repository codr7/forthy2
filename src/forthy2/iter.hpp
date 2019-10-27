#ifndef FORTHY2_ITER_HPP
#define FORTHY2_ITER_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Iter: Val {
    using Imp = function<void (IterBody)>;
    Imp imp;
    
    Iter(Imp imp);
    void dump(ostream &out) override;
    void iter(Cx &cx, IterBody body) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using IterType = PoolType<Iter>;
}

#endif
