#ifndef FORTHY2_VAL_HPP
#define FORTHY2_VAL_HPP

#include <functional>
#include <iostream>
#include <utility>

#include "forthy2/cmp.hpp"
#include "forthy2/node.hpp"
#include "forthy2/pos.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Form;
  struct Iter;
  struct Op;
  struct Pos;
  struct Type;
  
  struct Val: Node<Val> {
    using IterBody = function<bool (Val &)>;
    using Len = int64_t;
    
    bool marked;

    Val(): marked(true) {}

    virtual ~Val() {}

    virtual operator bool() { return true; }

    virtual Node<Op> &call(Cx &cx,
                           Pos pos,
                           Node<Op> &return_pc,
                           bool safe,
                           bool now);

    virtual Cmp cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

    virtual Val &clone(Cx &cx) { return *this; }

    virtual void dump(ostream &out) = 0;

    virtual bool eq(Val &other) { return this == &other; }

    virtual Iter &iter(Cx &cx, Pos pos);

    virtual Len len() { return 1; }
    
    virtual bool mark(Cx &cx);

    virtual void print(Cx &cx, Pos pos, ostream &out) { dump(out); }

    virtual void sweep(Cx &cx) { Node<Val>::unlink(); }

    virtual Form &to_form(Cx &cx, Pos pos);
    virtual Type &type(Cx &cx) = 0;

    virtual void unmark() { marked = false; }
  };

  ostream &operator <<(ostream &out, const Val &val);
}

#endif
