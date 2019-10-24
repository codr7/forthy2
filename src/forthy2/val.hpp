#ifndef FORTHY2_VAL_HPP
#define FORTHY2_VAL_HPP

#include <functional>
#include <iostream>
#include <utility>

#include "forthy2/cmp.hpp"
#include "forthy2/node.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Form;
  struct Op;
  struct Pos;
  struct Type;
  
  struct Val: Node<Val> {
    using IterBody = function<bool (Val &)>;
    
    bool marked;

    Val(): marked(true) {}

    virtual ~Val() {}

    virtual operator bool() { return true; }

    virtual Val &clone(Cx &cx) { return *this; }

    virtual Node<Op> &call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe);

    virtual Cmp cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

    virtual void dump(ostream &out) = 0;

    virtual bool eq(Val &other) { return this == &other; }

    virtual void iter(Cx &cx, IterBody body);
    
    virtual bool mark(Cx &cx);

    virtual void sweep(Cx &cx) { Node<Val>::unlink(); }

    virtual Type &type(Cx &cx) = 0;

    virtual void unmark() { marked = false; }

    virtual Form &unquote(Cx &cx, Pos pos);
  };

  ostream &operator <<(ostream &out, const Val &val);
}

#endif
