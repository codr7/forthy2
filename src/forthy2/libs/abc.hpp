#ifndef FORTHY2_LIB_ABC_HPP
#define FORTHY2_LIB_ABC_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_abc(Cx &cx, Pos pos, Scope &scope);

  inline Node<Op> &eq_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    cx.push(cx.bool_type.get(cx, x.eq(y)));
    return *return_pc.next;
  }

  inline Node<Op> &lt_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    cx.push(cx.bool_type.get(cx, x.cmp(y) == Cmp::Lt));
    return *return_pc.next;
  }

  inline Node<Op> &gt_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    bool ok(x.type(cx) == y.type(cx) && x.cmp(y) == Cmp::Gt);
    cx.push(cx.bool_type.get(cx, ok));
    return *return_pc.next;
  }

  inline Node<Op> &inc_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Int::Imp &v(cx.peek(cx.int_type).imp);

    if (v >= cx.ints.back().imp) {
      v++;
    } else {
      cx.poke(cx.int_type.get(cx, v + 1));
    }
    
    return *return_pc.next;
  }

  inline Node<Op> &dec_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Int::Imp &v(cx.peek(cx.int_type).imp);

    if (v > cx.ints.back().imp + 1) {
      v--;
    } else {
      cx.poke(cx.int_type.get(cx, v - 1));
    }
    
    return *return_pc.next;
  }

  inline Node<Op> &truffle_imp(Cx &cx,
                               Form &form,
                               Forms &in,
                               Node<Op> &out,
                               bool stash) {
    auto *in_spec(dynamic_cast<StackForm *>(in.back()));

    if (!in_spec || in_spec->body.empty()) {
      throw ESys(form.pos, "Invalid stack spec");
    }
    
    in.pop_back();
    auto *out_spec(dynamic_cast<StackForm *>(in_spec->body.back()));
    if (!out_spec) { throw ESys(form.pos, "Invalid stack spec"); }
    in_spec->body.pop_back();

    Scope scope(*cx.scope);
    auto in_len(in_spec->body.size());
    Int::Imp i(in_len-1);
    vector<Peek *> peeks;
    
    for (Form *f: in_spec->body) {
      if (auto *id(dynamic_cast<IdForm *>(f)); id) {
        Peek &p(cx.peek_pool.get(true, i));
        scope.bind(f->pos, id->val, p);
        peeks.push_back(&p);
      } else if (!dynamic_cast<NilForm *>(f)) {
        throw ESys(f->pos, "Invalid stack spec");
      }

      i--;
    }
    
    TruffleOp &op(cx.truffle_op.get(form, out, in_len, stash));
    Node<Op> *pc(&op);
    cx.with_scope<void>(scope, [&]() { pc = &cx.compile(out_spec->body, *pc); });
    op.end_pc = pc;
    for (Peek *p: peeks) { cx.peek_pool.put(*p); }
    return *pc;
  }

  inline Node<Op> &copy_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    return cx.copy_op.get(form, out);
  }

  inline Node<Op> &drop_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    return cx.drop_op.get(form, out);
  }

  inline Node<Op> &pair_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &r(cx.pop()), &l(cx.pop());
    cx.push(cx.pair_type.get(cx, l, r));
    return *return_pc.next;
  }

  inline Node<Op> &unpair_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &p(dynamic_cast<Pair &>(cx.pop()).imp);
    cx.push(*p.first);
    cx.push(*p.second);
    return *return_pc.next;
  }

  inline Node<Op> &bool_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.bool_type.get(cx, cx.pop()));
    return *return_pc.next;
  }

  inline Node<Op> &bool_int_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.int_type.get(cx, cx.pop(cx.bool_type).imp ? 1 : 0));
    return *return_pc.next;
  }

  inline Node<Op> &call_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    return cx.pop().call(cx, pos, return_pc, true, false);
  }

  inline Node<Op> &check_imp(Cx &cx,
                             Form &form,
                             Forms &in,
                             Node<Op> &out,
                             bool stash) {
    Form &body(*in.back());
    in.pop_back();
    Node<Op> *op(&out);
    op = &body.compile(cx, in, *op);
    return cx.check_op.get(form, *op, body.ref());
  }

  inline Node<Op> &clock_imp(Cx &cx,
                             Form &form,
                             Forms &in,
                             Node<Op> &out,
                             bool stash) {
    Form &body(*in.back());
    in.pop_back();
    ClockOp &clock_op(cx.clock_op.get(form, out, body.ref()));
    Node<Op> &end_pc(body.compile(cx, in, clock_op));
    clock_op.end_pc = &end_pc;
    return end_pc;
  }

  inline Node<Op> &compile_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &f(dynamic_cast<Form &>(cx.pop()));
    Lambda &l(cx.lambda_type.get(cx));
    Forms in;
    Node<Op> &f_pc(f.compile(cx, in, *l.ops.prev));
    cx.return_op.get(f, f_pc);
    cx.push(l);
    return *return_pc.next;
  }

  inline Node<Op> &is_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    cx.push(cx.bool_type.get(cx, &x == &y));
    return *return_pc.next;
  }

  inline Node<Op> &isa_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &p(cx.pop()), &c(cx.pop());

    if (Type *t(dynamic_cast<Type &>(c).isa(dynamic_cast<Type &>(p))); t) {
      cx.push(*t);
    } else {
      cx.push(cx._);
    }

    return *return_pc.next;
  }

  inline Node<Op> &let_imp(Cx &cx,
                           Form &form,
                           Forms &in,
                           Node<Op> &out,
                           bool stash) {
    Form &id_form(*in.back());
    in.pop_back();
    Sym &id(dynamic_cast<IdForm &>(id_form).val);
    Form &val_form(*in.back());
    in.pop_back();
    val_form.eval(cx);
    cx.scope->bind(form.pos, id, cx.pop(form.pos));
    return out;
  }

  inline Node<Op> &mark_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    optional<Time::Imp> max_time;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_time = dynamic_cast<Time &>(v).imp;
    }
    
    if (auto ok(cx.mark(max_time)); ok) {
      cx.push(cx.time_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }

    return *return_pc.next;
  }

  inline Node<Op> &mark_sweep_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    optional<Time::Imp> max_time;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_time = dynamic_cast<Time &>(v).imp;
    }
    
    if (auto ok(cx.mark_sweep(max_time)); ok) {
      cx.push(cx.time_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }

    return *return_pc.next;
  }
  
  inline Node<Op> &method_imp(Cx &cx,
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

    transform(args_val.beg(),
              args_val.end(),
              back_inserter(args), [&](auto &v) {
                if (&v->type(cx) == &cx.meta_type) {
                  return Arg(*dynamic_cast<Type *>(v));
                }
                  
                return Arg(v);
              });

    Method &m(cx.scope->add_method(cx, form.pos, id, args));
    Form &body(*in.back());
    in.pop_back();

    Node<Op> *pc(m.fn.ops.prev);
    if (&body != &cx.nil_form) { pc = &cx.compile(body, *pc); }
    cx.return_op.get(form, *pc);
    return out;
  }

  inline Node<Op> &type_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.pop().type(cx));
    return *return_pc.next;
  }

  inline Node<Op> &and_imp(Cx &cx,
                           Form &form,
                           Forms &in,
                           Node<Op> &out,
                           bool stash) {
    Form &y(*in.back());
    in.pop_back();
    
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &y.compile(cx, in, op);
    op.pop_else = true;
    return *op.pc;
  }

  inline Node<Op> &or_imp(Cx &cx,
                          Form &form,
                          Forms &in,
                          Node<Op> &out,
                          bool stash) {
    Form &y(*in.back());
    in.pop_back();
    
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &y.compile(cx, in, op);
    op.neg = true;
    op.pop_else = true;
    return *op.pc;
  }

  inline Node<Op> &not_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.bool_type.get(cx, !cx.pop()));
    return *return_pc.next;
  }

  inline Node<Op> &if_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out, bool stash) {
    Form &body(*in.back());
    in.pop_back();
   
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &body.compile(cx, in, op);
    op.pop_if = true;
    op.pop_else = true;
    return *op.pc;
  }

  inline Node<Op> &else_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    Form &body(*in.back());
    in.pop_back();
   
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &body.compile(cx, in, op);
    op.neg = true;
    op.pop_if = true;
    op.pop_else = true;
    return *op.pc;
  }

  inline Node<Op> &for_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out, bool stash) {
    ForOp &pc(cx.for_op.get(form, out));
    Form &body(*in.back());
    in.pop_back();
    pc.end_pc = (&body == &cx.nil_form) ? &pc : &body.compile(cx, in, pc);
    return *pc.end_pc;
  }

  inline Node<Op> &recall_imp(Cx &cx,
                              Form &form,
                              Forms &in,
                              Node<Op> &out,
                              bool stash) {
    auto *lit(dynamic_cast<LitForm *>(in.back()));
    Val *fn(nullptr);

    if (lit) {
      fn = &lit->val;
    } else {
      auto *id(dynamic_cast<IdForm *>(in.back()));

      if (!id) {
        throw ESys(form.pos, "Invalid recall: ", *in.back());
      }

      fn = &cx.scope->get(form.pos, id->val);
    }

    in.pop_back();
    return cx.recall_op.get(form, out, *fn);
  }

  inline Node<Op> &repeat_imp(Cx &cx,
                              Form &form,
                              Forms &in,
                              Node<Op> &out,
                              bool stash) {
    RepeatOp &op(cx.repeat_op.get(form, out));
    Form &body(*in.back());
    in.pop_back();
    op.end_pc = &body.compile(cx, in, op);
    return *op.end_pc;
  }

  inline Node<Op> &rotl_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    return cx.rotl_op.get(form, out);
  }

  inline Node<Op> &rotr_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    return cx.rotr_op.get(form, out);
  }

  inline Node<Op> &splice_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Form &dst(cx.peek(cx.form_type, 1));
    if (dst.splice(cx, 1)) { throw ESys(pos, "Missing splice"); }
    return *return_pc.next;
  }

  inline Node<Op> &len_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    cx.push(cx.int_type.get(cx, cx.pop().len()));
    return *return_pc.next;
  }

  inline Node<Op> &stack_pop_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    if (Val *v(dynamic_cast<Stack &>(cx.peek()).try_pop(cx)); v) {
      cx.push(*v);
    } else {
      cx.push(cx._);
    }

    return *return_pc.next;
  }

  inline Node<Op> &stack_push_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &v(cx.pop());
    dynamic_cast<Stack &>(cx.peek()).push(v);
    return *return_pc.next;
  }

  inline Node<Op> &swap_imp(Cx &cx,
                            Form &form,
                            Forms &in,
                            Node<Op> &out,
                            bool stash) {
    return cx.swap_op.get(form, out);
  }

  inline Node<Op> &sweep_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    optional<Time::Imp> max_time;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_time = dynamic_cast<Time &>(v).imp;
    }
    
    if (auto ok(cx.sweep(max_time)); ok) {
      cx.push(cx.time_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }

    return *return_pc.next;
  }

  inline Node<Op> &while_imp(Cx &cx,
                             Form &form,
                             Forms &in,
                             Node<Op> &out,
                             bool stash) {
    Form &body(*in.back());
    in.pop_back();

    Node<Op> *op(&body.compile(cx, in, out));
    BranchOp &branch_op(cx.branch_op.get(form, *op));
    branch_op.pc = &out;
    branch_op.neg = true;
    return branch_op;
  }
}

#endif
