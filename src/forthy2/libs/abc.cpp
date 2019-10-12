#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  static void eq_imp(Cx &cx, Pos pos) {
    bool ok(cx.pop(pos).eq(cx.pop(pos)));
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void dup_imp(Cx &cx, Pos pos) { cx.push(cx.peek()); }

  static void drop_imp(Cx &cx, Pos pos) { cx.pop(); }

  static void swap_imp(Cx &cx, Pos pos) { cx.stack->swap(); }

  static void unpair_imp(Cx &cx, Pos pos) {
    auto &p(dynamic_cast<Pair &>(cx.pop(pos)).imp);
    cx.push(*p.first);
    cx.push(*p.second);
  }

  static void bool_imp(Cx &cx, Pos pos) {
    cx.push(cx.bool_type.get(cx, cx.pop(pos)));
  }

  static Node<Op> &check_imp(Cx &cx, Form &form, Forms &in, Node<Op> &out) {
    Form &body(*in.back());
    in.pop_back();
    Node<Op> *op(&out);
    op = &body.compile(cx, in, *op);
    return cx.check_op.get(form, *op, body.ref());
  }

  static void dump_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.pop(pos).dump(out);
    out << endl;
  }

  static void dump_stack_imp(Cx &cx, Pos pos) {
    auto &out(*cx.stdout);
    cx.stack->dump(out);
    out << endl;
  }

  static void is_imp(Cx &cx, Pos pos) {
    bool ok(cx.pop(pos).is(cx.pop(pos)));
    cx.push(cx.bool_type.get(cx, ok));
  }

  static void isa_imp(Cx &cx, Pos pos) {
    Val &p(cx.pop(pos)), &c(cx.pop(pos));

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
    cx.env->bind(form.pos, id, cx.pop(form.pos));
    return out;
  }

  static void not_imp(Cx &cx, Pos pos) {
    cx.push(cx.bool_type.get(cx, !dynamic_cast<Bool &>(cx.pop(pos)).imp));
  }

  static void type_imp(Cx &cx, Pos pos) { cx.push(cx.pop(pos).type(cx)); }

  void init_abc(Cx &cx, Pos pos, Env &env) {
    env.bind_type(cx, pos, cx.a_type);
    env.bind_type(cx, pos, cx.bool_type);
    env.bind_type(cx, pos, cx.int_type);
    env.bind_type(cx, pos, cx.macro_type);
    env.bind_type(cx, pos, cx.meta_type);
    env.bind_type(cx, pos, cx.method_set_type);
    env.bind_type(cx, pos, cx.method_type);
    env.bind_type(cx, pos, cx.nil_type);
    env.bind_type(cx, pos, cx.num_type);
    env.bind_type(cx, pos, cx.pair_type);
    env.bind_type(cx, pos, cx.stack_type);
    env.bind_type(cx, pos, cx.sym_type);

    env.bind(pos, cx.sym("_"), cx._);
    env.bind(pos, cx.sym("F"), cx.F);
    env.bind(pos, cx.sym("T"), cx.T);

    env.add_method(cx, pos, cx.sym("="),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = eq_imp;

    env.add_method(cx, pos, cx.sym(".:"), {{cx.a_type.or_nil()}}).imp = dup_imp;
    env.add_method(cx, pos, cx.sym(":."), {{cx.a_type.or_nil()}}).imp = drop_imp;

    env.add_method(cx, pos, cx.sym("::"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = swap_imp;

    env.add_method(cx, pos, cx.sym(",,"), {{cx.pair_type}}).imp = unpair_imp;
    env.add_method(cx, pos, cx.sym("bool"), {{cx.a_type.or_nil()}}).imp = bool_imp;
    env.add_macro(cx, pos, cx.sym("check"), {{cx.a_type.or_nil()}}).imp = check_imp;
    env.add_method(cx, pos, cx.sym("dump"), {{cx.a_type.or_nil()}}).imp = dump_imp;
    env.add_method(cx, pos, cx.sym("dump-stack")).imp = dump_stack_imp;
    
    env.add_method(cx, pos, cx.sym("is"),
                   {{cx.a_type.or_nil()}, {cx.a_type.or_nil()}}).imp = is_imp;

    env.add_method(cx, pos, cx.sym("isa"),
                   {{cx.meta_type}, {cx.meta_type}}).imp = isa_imp;

    env.add_macro(cx, pos, cx.sym("let"),
                  {{cx.sym_type}, {cx.a_type.or_nil()}}).imp = let_imp;

    env.add_method(cx, pos, cx.sym("not"), {{cx.bool_type}}).imp = not_imp;
    env.add_method(cx, pos, cx.sym("type"), {{cx.a_type.or_nil()}}).imp = type_imp;
  }
}
