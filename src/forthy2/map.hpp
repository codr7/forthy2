#ifndef FORTHY2_MAP_HPP
#define FORTHY2_MAP_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Map: Val {
    Val &in, &fn;
    
    Map(Val &in, Val &fn);
    void dump(ostream &out) override;
    void iter(Cx &cx, Pos pos, IterBody body) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using MapType = PoolType<Map>;
}

#endif
