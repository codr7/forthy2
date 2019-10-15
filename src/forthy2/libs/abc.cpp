#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  static void mark_sweep_imp(Cx &cx, Pos pos) {
    optional<uint64_t> max_ns;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_ns = dynamic_cast<Int &>(v).imp;
    }
    
    if (auto ok(cx.mark_sweep(max_ns)); ok) {
      cx.push(cx.int_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }
  }

  static void mark_imp(Cx &cx, Pos pos) {
    optional<uint64_t> max_ns;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_ns = dynamic_cast<Int &>(v).imp;
    }
    
    if (auto ok(cx.mark(max_ns)); ok) {
      cx.push(cx.int_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }
  }

  static void sweep_imp(Cx &cx, Pos pos) {
    optional<uint64_t> max_ns;

    if (Val &v(cx.pop()); v.type(cx) == cx.int_type) {
      max_ns = dynamic_cast<Int &>(v).imp;
    }
    
    if (auto ok(cx.sweep(max_ns)); ok) {
      cx.push(cx.int_type.get(cx, *ok));
    } else {
      cx.push(cx._);
    }
  }

  static void eq_imp(Cx &cx, Pos pos) {
    Val &y(cx.pop()), &x(cx.pop());
    bool ok(x.type(cx) == y.type(cx) && x.eq(y));
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void lt_imp(Cx &cx, Pos pos) {
    Val &y(cx.pop()), &x(cx.pop());
    bool ok(x.type(cx) == y.type(cx) && x.cmp(y) == Cmp::Lt);
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void gt_imp(Cx &cx, Pos pos) {
    Val &y(cx.pop()), &x(cx.pop());
    bool ok(x.type(cx) == y.type(cx) && x.cmp(y) == Cmp::Gt);
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void dup_imp(Cx &cx, Pos pos) { cx.push(cx.peek()); }

  static void drop_imp(Cx &cx, Pos pos) { cx.pop(); }

  static void swap_imp(Cx &cx, Pos pos) { cx.stack->swap(); }

  static void pair_imp(Cx &cx, Pos pos) {
    Val &r(cx.pop()), &l(cx.pop());
    cx.push(cx.pair_type.get(cx, l, r));
  }

  static void unpair_imp(Cx &cx, Pos pos) {
    auto &p(dynamic_cast<Pair &>(cx.pop()).imp);
    cx.push(*p.first);
    cx.push(*p.second);
  }

  static void bool_imp(Cx &cx, Pos pos) {
    cx.push(cx.bool_type.get(cx, cx.pop()));
  }

  static Node<Op> &check_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();
    Node<Op> *op(&out);
    op = &body.compile(cx, in, *op);
    return cx.check_op.get(form, *op, body.ref());
  }

  static Node<Op> &clock_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();
    ClockOp &clock_op(cx.clock_op.get(form, out, body.ref()));
    Node<Op> &end_pc(body.compile(cx, in, clock_op));
    clock_op.end_pc = &end_pc;
    return end_pc;
  }

  static void dump_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.pop().dump(out);
    out << endl;
  }

  static void dump_stack_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.stack->dump(out);
    out << endl;
  }

  static void is_imp(Cx &cx, Pos pos) {
    Val &y(cx.pop()), &x(cx.pop());
    bool ok(x.type(cx) == y.type(cx) && x.is(y));
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void isa_imp(Cx &cx, Pos pos) {
    Val &p(cx.pop()), &c(cx.pop());

    if (Type *t(dynamic_cast<Type &>(c).isa(dynamic_cast<Type &>(p))); t) {
      cx.push(*t);
    } else {
      cx.push(cx._);
    }
  }

  static Node<Op> &let_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &id_form(*in.back());
    in.pop_back();
    Sym &id(dynamic_cast<IdForm &>(id_form).val);
    Form &val_form(*in.back());
    in.pop_back();
    val_form.eval(cx, in);
    cx.scope->bind(form.pos, id, cx.pop(form.pos));
    return out;
  }

  static void type_imp(Cx &cx, Pos pos) { cx.push(cx.pop().type(cx)); }

  static Node<Op> &and_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &y(*in.back());
    in.pop_back();
    
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &y.compile(cx, in, op);
    op.pop_else = true;
    return *op.pc;
  }

  static Node<Op> &or_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &y(*in.back());
    in.pop_back();
    
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &y.compile(cx, in, op);
    op.neg = true;
    op.pop_else = true;
    return *op.pc;
  }

  static void not_imp(Cx &cx, Pos pos) {
    cx.push(cx.bool_type.get(cx, !dynamic_cast<Bool &>(cx.pop()).imp));
  }

  static Node<Op> &if_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();
   
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &body.compile(cx, in, op);
    op.pop_if = true;
    op.pop_else = true;
    return *op.pc;
  }

  static Node<Op> &else_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();
   
    BranchOp &op(cx.branch_op.get(form, out));
    op.pc = &body.compile(cx, in, op);
    op.neg = true;
    op.pop_if = true;
    op.pop_else = true;
    return *op.pc;
  }

  static Node<Op> &while_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();

    Node<Op> *op(&body.compile(cx, in, out));
    BranchOp &branch_op(cx.branch_op.get(form, *op));
    branch_op.pc = &out;
    branch_op.neg = true;
    return branch_op;
  }

  static void inc_imp(Cx &cx, Pos pos) {
    Val &v(cx.pop(pos));
    cx.push(cx.int_type.get(cx, dynamic_cast<Int &>(v).imp + 1));
  }

  static void dec_imp(Cx &cx, Pos pos) {
    Val &v(cx.pop(pos));
    cx.push(cx.int_type.get(cx, dynamic_cast<Int &>(v).imp - 1));
  }

  static void stack_len_imp(Cx &cx, Pos pos) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Stack &>(cx.pop()).len()));
  }

  static void stack_pop_imp(Cx &cx, Pos pos) {
    cx.push(dynamic_cast<Stack &>(cx.pop()).try_pop(cx));
  }

  static void stack_push_imp(Cx &cx, Pos pos) {
    Val &v(cx.pop());
    dynamic_cast<Stack &>(cx.pop()).push(v);
  }

  void init_abc(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.a_type);
    scope.bind_type(cx, pos, cx.bool_type);
    scope.bind_type(cx, pos, cx.int_type);
    scope.bind_type(cx, pos, cx.macro_type);
    scope.bind_type(cx, pos, cx.meta_type);
    scope.bind_type(cx, pos, cx.method_set_type);
    scope.bind_type(cx, pos, cx.method_type);
    scope.bind_type(cx, pos, cx.nil_type);
    scope.bind_type(cx, pos, cx.num_type);
    scope.bind_type(cx, pos, cx.pair_type);
    scope.bind_type(cx, pos, cx.stack_type);
    scope.bind_type(cx, pos, cx.sym_type);

    scope.bind(pos, cx.sym("_"), cx._);
    scope.bind(pos, cx.sym("F"), cx.F);
    scope.bind(pos, cx.sym("T"), cx.T);

    scope.add_method(cx, pos, cx.sym("mark-sweep"),
                   {{cx.int_type.or_nil()}}).imp = mark_sweep_imp;

    scope.add_method(cx, pos, cx.sym("mark"),
                   {{cx.int_type.or_nil()}}).imp = mark_imp;

    scope.add_method(cx, pos, cx.sym("sweep"),
                   {{cx.int_type.or_nil()}}).imp = sweep_imp;

    scope.add_method(cx, pos, cx.sym("="),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = eq_imp;

    scope.add_method(cx, pos, cx.sym("<"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = lt_imp;

    scope.add_method(cx, pos, cx.sym(">"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = gt_imp;

    scope.add_method(cx, pos, cx.sym(".:"), {{cx.a_type.or_nil()}}).imp = dup_imp;
    scope.add_method(cx, pos, cx.sym(":."), {{cx.a_type.or_nil()}}).imp = drop_imp;

    scope.add_method(cx, pos, cx.sym("::"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = swap_imp;

    scope.add_method(cx, pos, cx.sym(","),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = pair_imp;
    
    scope.add_method(cx, pos, cx.sym(",,"), {{cx.pair_type}}).imp = unpair_imp;
    scope.add_method(cx, pos, cx.sym("bool"), {{cx.a_type.or_nil()}}).imp = bool_imp;
    scope.add_macro(cx, pos, cx.sym("check"), {{cx.a_type.or_nil()}}).imp = check_imp;
    scope.add_macro(cx, pos, cx.sym("clock"), {{cx.a_type.or_nil()}}).imp = clock_imp;
    scope.add_method(cx, pos, cx.sym("dump"), {{cx.a_type.or_nil()}}).imp = dump_imp;
    scope.add_method(cx, pos, cx.sym("dump-stack")).imp = dump_stack_imp;
    
    scope.add_method(cx, pos, cx.sym("is"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = is_imp;

    scope.add_method(cx, pos, cx.sym("isa"),
                   {{cx.meta_type}, {cx.meta_type}}).imp = isa_imp;

    scope.add_macro(cx, pos, cx.sym("let"),
                  {{cx.sym_type}, {cx.a_type.or_nil()}}).imp = let_imp;

    scope.add_method(cx, pos, cx.sym("type"), {{cx.a_type.or_nil()}}).imp = type_imp;

    scope.add_macro(cx, pos, cx.sym("and"), {{cx.a_type.or_nil()}}).imp = and_imp;
    scope.add_macro(cx, pos, cx.sym("or"), {{cx.a_type.or_nil()}}).imp = or_imp;
    scope.add_method(cx, pos, cx.sym("not"), {{cx.bool_type}}).imp = not_imp;

    scope.add_macro(cx, pos, cx.sym("if"), {{cx.a_type}}).imp = if_imp;
    scope.add_macro(cx, pos, cx.sym("else"), {{cx.a_type}}).imp = else_imp;
    scope.add_macro(cx, pos, cx.sym("while"), {{cx.a_type}}).imp = while_imp;

    scope.add_method(cx, pos, cx.sym("+1"), {{cx.int_type}}).imp = inc_imp;
    scope.add_method(cx, pos, cx.sym("-1"), {{cx.int_type}}).imp = dec_imp;

    scope.add_method(cx, pos, cx.sym("len"),
                     {{cx.stack_type}}).imp = stack_len_imp;
    
    scope.add_method(cx, pos, cx.sym("pop"),
                     {{cx.stack_type}}).imp = stack_pop_imp;    

    scope.add_method(cx, pos, cx.sym("push"),
                   {{cx.stack_type}, {cx.a_type}}).imp = stack_push_imp;    
  }
}
