#ifndef FORTHY2_LIB_ITER_HPP
#define FORTHY2_LIB_ITER_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_iter(Cx &cx, Pos pos, Scope &scope);

  inline Node<Op> &filter_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &pred(cx.pop()), &in(cx.pop());
    cx.push(cx.filter_type.get(cx, in.iter(cx, pos), pred));
    return *return_pc.next;
  }

  inline Node<Op> &iter_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.pop().iter(cx, pos));
    return *return_pc.next;
  }
  
  inline Node<Op> &map_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &fn(cx.pop()), &in(cx.pop());
    cx.push(cx.map_type.get(cx, in.iter(cx, pos), fn));
    return *return_pc.next;
  }

  inline Node<Op> &zip_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &right(cx.pop()), &left(cx.pop());
    cx.push(cx.zip_type.get(cx, left.iter(cx, pos), right.iter(cx, pos)));
    return *return_pc.next;
  }

  inline Node<Op> &unzip_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Iter &in(cx.pop().iter(cx, pos));
    Stack &left(cx.stack_type.get(cx)), &right(cx.stack_type.get(cx));
    Val *v;
    
    while ((v = in.get_next(cx, pos))) {
      Pair *p(dynamic_cast<Pair *>(v));
      if (!p) { throw ESys(pos, "Expected Pair: ", *v); }
      left.push(*p->imp.first);
      right.push(*p->imp.second);
    }

    cx.push(left);
    cx.push(right);
    return *return_pc.next;
  }
}

#endif
