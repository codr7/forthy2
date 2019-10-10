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

    virtual Val &clone(Cx &cx) { return *this; }
    virtual void call(Cx &cx, Pos pos);
    virtual Cmp cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }
    virtual void dump(ostream &out) = 0;
    virtual bool eq(Val &other) { return is(other); }
    virtual Type &get_type(Cx &cx) = 0;
    virtual bool is(Val &other) { return this == &other; }
    virtual bool mark(Cx &cx);
    
    virtual void sweep(Cx &cx) { Node<Val>::unlink(); }

    virtual void unmark() { marked = false; }
  };
}

#endif
