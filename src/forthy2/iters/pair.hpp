#ifndef FORTHY2_ITER_PAIR_HPP
#define FORTHY2_ITER_PAIR_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct PairIter: Iter {
    Val *left, *right;
    
    PairIter(Val &left, Val &right);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    Val *pop(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using PairIterType = PoolType<PairIter>;
}

#endif
