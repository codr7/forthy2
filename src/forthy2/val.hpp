#ifndef FORTHY2_VAL_HPP
#define FORTHY2_VAL_HPP

#include <iostream>
#include <utility>

#include "forthy2/cmp.hpp"
#include "forthy2/node.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Type;
  
  struct Val: Node<Val> {
    bool marked = true;

    virtual ~Val() {}
    virtual Cmp cmp(Val &other) = 0;
    virtual void dump(ostream &out) = 0;
    virtual Type &get_type(Cx &cx) = 0;
    virtual bool is(Val &other) = 0;
    virtual bool mark(Cx &cx);
    
    virtual void sweep(Cx &cx) { Node<Val>::del(); }

    virtual void unmark() { marked = false; }
  };

  template <typename T>
  struct TVal: Val {
    T v;

    template <typename...Args>
    TVal(Args &&...args): v(forward<Args>(args)...) {}
  };
}

#endif
