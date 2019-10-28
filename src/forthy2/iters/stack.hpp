#ifndef FORTHY2_ITER_STACK_HPP
#define FORTHY2_ITER_STACK_HPP

#include "forthy2/iter.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/stack.hpp"

namespace forthy2 {
  struct StackIter: Iter {
    Stack &in;
    Stack::Iter i;
    
    StackIter(Stack &in);
    void dump(ostream &out) override;
    bool mark(Cx &cx) override;
    Val *get_next(Cx &cx, Pos pos) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;    
  };

  using StackIterType = PoolType<StackIter>;
}

#endif
