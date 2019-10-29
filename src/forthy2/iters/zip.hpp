#ifndef FORTHY2_ITER_ZIP_HPP
#define FORTHY2_ITER_ZIP_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Zip: Iter {
    Iter &left, &right;
    
    Zip(Iter &left, Iter &right);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    Val *get_next(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using ZipType = PoolType<Zip>;
}

#endif
