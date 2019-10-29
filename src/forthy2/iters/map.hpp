#ifndef FORTHY2_ITER_MAP_HPP
#define FORTHY2_ITER_MAP_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Map: Iter {
    Iter &in;
    Val &fn;
    
    Map(Iter &in, Val &fn);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    Val *pop(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using MapType = PoolType<Map>;
}

#endif
