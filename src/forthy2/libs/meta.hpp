#ifndef FORTHY2_LIB_META_HPP
#define FORTHY2_LIB_META_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_meta(Cx &cx, Pos pos, Scope &scope);

  namespace meta {
    inline Node<Op> &body_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.peek(cx.scope_type).body);
      return *return_pc.next;
    }

    inline Node<Op> &compile_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      auto &f(cx.pop(cx.form_type));
      Lambda &l(cx.lambda_type.get(cx));
      Node<Op> &pc(cx.compile(f, *l.ops.prev));
      cx.return_op.get(f, pc);
      cx.push(l);
      return *return_pc.next;
    }

    inline Node<Op> &macro_imp(Cx &cx,
                               Form &form,
                               Forms &in,
                               Node<Op> &out,
                               bool stash) {
      Sym &id(dynamic_cast<IdForm *>(in.back())->val);
      in.pop_back();

      Form &args_form(*in.back());
      in.pop_back();

      args_form.eval(cx);
      Stack &args_val(cx.pop(form.pos, cx.stack_type));
      vector<Arg> args;

      transform(args_val.begin(),
                args_val.end(),
                back_inserter(args), [&](auto &v) {
                  if (&v->type(cx) == &cx.meta_type) {
                    return Arg(*dynamic_cast<Type *>(v));
                  }
                  
                  return Arg(v);
                });

      Macro &m(cx.scope->add_macro(cx, form.pos, id, args));
      Form &body(*in.back());
      in.pop_back();

      Node<Op> *pc(m.ops.prev);
      if (&body != &cx.nil_form) { pc = &cx.compile(body, *pc); }
      return out;
    }
  }
}

#endif
