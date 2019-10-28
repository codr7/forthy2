#ifndef FORTHY2_ITER_NIL_HPP
#define FORTHY2_ITER_NIL_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct NilIter: Iter {
    Val *get_next(Cx &cx, Pos pos) override { return nullptr; }
  };
}

#endif
