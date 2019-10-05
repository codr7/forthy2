#ifndef FORTHY2_VAL_HPP
#define FORTHY2_VAL_HPP

#include "forthy2/cmp.hpp"
#include "forthy2/node.hpp"

namespace forthy2 {
  struct Type;
  
  struct Val {
    Node<Val> gc_node;

    virtual Cmp cmp(Val &other) = 0;
    virtual bool is(Val &other) = 0;
    virtual void sweep() { gc_node.del(); }
    virtual Type &type() = 0;
  };

  template <typename T>
  struct TVal: Val {
    T v;

    template <typename...Args>
    TVal(Args &&...args): v(forward<Args>(args)...) {}     
  };
}

#endif
