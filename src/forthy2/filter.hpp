#ifndef FORTHY2_FILTER_HPP
#define FORTHY2_FILTER_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Filter: Val {
    Val &in, &pred;
    
    Filter(Val &in, Val &pred);
    void dump(ostream &out) override;
    void iter(Cx &cx, Pos pos, IterBody body) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using FilterType = PoolType<Filter>;
}

#endif
