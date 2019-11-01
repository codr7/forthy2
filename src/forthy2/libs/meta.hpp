#ifndef FORTHY2_LIB_META_HPP
#define FORTHY2_LIB_META_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_meta(Cx &cx, Pos pos, Scope &scope);

  namespace meta {
    inline Node<Op> &compile_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &f(dynamic_cast<Form &>(cx.pop()));
      Lambda &l(cx.lambda_type.get(cx));
      Node<Op> &pc(cx.compile(f, *l.ops.prev));
      cx.return_op.get(f, pc);
      cx.push(l);
      return *return_pc.next;
    }

    inline Node<Op> &body_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &body(cx.pop(cx.scope_type).body);
      Stack &out(cx.stack_type.get(cx));

      transform(body.begin(), body.end(), back_inserter(out.items), [&](Form *f) {
          cx.marked.push(f->ref());
          return f;
        });

      cx.push(out);
      return *return_pc.next;
    }


  }
}

#endif
