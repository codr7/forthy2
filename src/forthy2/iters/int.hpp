#ifndef FORTHY2_ITER_INT_HPP
#define FORTHY2_ITER_INT_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct IntIter: Iter {
    Int::Imp i, max;
    
    IntIter(Int::Imp i, Int::Imp max);
    void dump(ostream &out) override;
    Val *get_next(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using IntIterType = PoolType<IntIter>;
}

#endif
