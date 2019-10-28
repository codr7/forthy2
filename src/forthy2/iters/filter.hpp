#ifndef FORTHY2_ITER_FILTER_HPP
#define FORTHY2_ITER_FILTER_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Filter: Iter {
    Iter &in;
    Val &pred;
    
    Filter(Iter &in, Val &pred);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    Val *get_next(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using FilterType = PoolType<Filter>;
}

#endif
