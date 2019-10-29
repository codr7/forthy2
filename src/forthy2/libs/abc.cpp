#include "forthy2/cx.hpp"
#include "forthy2/libs/abc.hpp"

namespace forthy2 {
  void init_abc(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.a_type);
    scope.bind_type(cx, pos, cx.bool_type);
    scope.bind_type(cx, pos, cx.fn_type);
    scope.bind_type(cx, pos, cx.form_type);
    scope.bind_type(cx, pos, cx.int_type);
    scope.bind_type(cx, pos, cx.int_iter_type);
    scope.bind_type(cx, pos, cx.iter_type);
    scope.bind_type(cx, pos, cx.macro_type);
    scope.bind_type(cx, pos, cx.meta_type);
    scope.bind_type(cx, pos, cx.method_set_type);
    scope.bind_type(cx, pos, cx.method_type);
    scope.bind_type(cx, pos, cx.nil_type);
    scope.bind_type(cx, pos, cx.num_type);
    scope.bind_type(cx, pos, cx.pair_type);
    scope.bind_type(cx, pos, cx.pair_iter_type);
    scope.bind_type(cx, pos, cx.stack_type);
    scope.bind_type(cx, pos, cx.stack_iter_type);
    scope.bind_type(cx, pos, cx.sym_type);
    scope.bind_type(cx, pos, cx.val_iter_type);

    scope.bind(pos, cx.sym("F"), cx.F);
    scope.bind(pos, cx.sym("T"), cx.T);
    
    scope.add_method(cx, pos, cx.sym("="),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = eq_imp;

    scope.add_method(cx, pos, cx.sym("<"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = lt_imp;

    scope.add_method(cx, pos, cx.sym(">"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = gt_imp;

    scope.add_method(cx, pos, cx.sym("+1!"), {{cx.int_type}}).imp = inc_imp;
    scope.add_method(cx, pos, cx.sym("-1!"), {{cx.int_type}}).imp = dec_imp;
    scope.add_macro(cx, pos, cx.sym("$"), {{cx.stack_type}}).imp = restack_imp;

    scope.add_macro(cx, pos, cx.sym("and"), {{cx.a_type.or_()}}).imp = and_imp;

    scope.add_method(cx, pos, cx.sym("bool"), {{cx.a_type.or_()}}).imp = bool_imp;
    scope.add_method(cx, pos, cx.sym("int"), {{cx.bool_type}}).imp = bool_int_imp;

    scope.add_method(cx, pos, cx.sym("call"), {{cx.a_type.or_()}}).imp = call_imp;
    scope.add_macro(cx, pos, cx.sym("check"), {{cx.a_type.or_()}}).imp = check_imp;
    scope.add_macro(cx, pos, cx.sym("clock"), {{cx.a_type.or_()}}).imp = clock_imp;
    scope.add_method(cx, pos, cx.sym("compile"), {{cx.form_type}}).imp = compile_imp;
    scope.add_macro(cx, pos, cx.sym("copy")).imp = copy_imp;
    scope.add_macro(cx, pos, cx.sym("drop")).imp = drop_imp;
    scope.add_method(cx, pos, cx.sym("dump"), {{cx.a_type.or_()}}).imp = dump_imp;
    scope.add_method(cx, pos, cx.sym("dump-stack")).imp = dump_stack_imp;    
    scope.add_macro(cx, pos, cx.sym("else"), {{cx.a_type}}).imp = else_imp;

    scope.add_macro(cx, pos, cx.sym("for"), {{cx.a_type}}).imp = for_imp;
    scope.add_macro(cx, pos, cx.sym("if"), {{cx.a_type}}).imp = if_imp;

    scope.add_method(cx, pos, cx.sym("is"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = is_imp;

    scope.add_method(cx, pos, cx.sym("isa"),
                     {{cx.meta_type}, {cx.meta_type}}).imp = isa_imp;

    scope.add_macro(cx, pos, cx.sym("let"),
                    {{cx.sym_type}, {cx.a_type.or_()}}).imp = let_imp;

    scope.add_method(cx, pos, cx.sym("mark"),
                     {{cx.time_type.or_()}}).imp = mark_imp;

    scope.add_method(cx, pos, cx.sym("mark-sweep"),
                     {{cx.time_type.or_()}}).imp = mark_sweep_imp;

    scope.add_macro(cx, pos, cx.sym("method"),
                    {{cx.sym_type}, {cx.stack_type}, {cx.a_type}}).imp = method_imp;

    scope.add_method(cx, pos, cx.sym("not"), {{cx.a_type}}).imp = not_imp;
    scope.add_macro(cx, pos, cx.sym("or"), {{cx.a_type.or_()}}).imp = or_imp;

    scope.add_method(cx, pos, cx.sym("pair"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = pair_imp;

    scope.add_method(cx, pos, cx.sym("unpair"), {{cx.pair_type}}).imp = unpair_imp;

    scope.add_method(cx, pos, cx.sym("len"),
                     {{cx.stack_type}}).imp = stack_len_imp;

    scope.add_method(cx, pos, cx.sym("pop"),
                     {{cx.stack_type}}).imp = stack_pop_imp;    

    scope.add_method(cx, pos, cx.sym("push"),
                     {{cx.stack_type}, {cx.a_type}}).imp = stack_push_imp;    

    scope.add_macro(cx, pos, cx.sym("recall"), {{cx.fn_type.or_()}}).imp = recall_imp;
    scope.add_macro(cx, pos, cx.sym("repeat"), {{cx.a_type}}).imp = repeat_imp;

    scope.add_macro(cx, pos, cx.sym("rotl")).imp = rotl_imp;
    scope.add_macro(cx, pos, cx.sym("rotr")).imp = rotr_imp;

    scope.add_method(cx, pos, cx.sym("splice"),
                     {{cx.form_type}, {cx.a_type}}).imp = splice_imp;

    scope.add_macro(cx, pos, cx.sym("swap")).imp = swap_imp;

    scope.add_method(cx, pos, cx.sym("sweep"),
                     {{cx.time_type.or_()}}).imp = sweep_imp;

    scope.add_method(cx, pos, cx.sym("type"), {{cx.a_type.or_()}}).imp = type_imp;

    scope.add_macro(cx, pos, cx.sym("while"), {{cx.a_type}}).imp = while_imp;
  }
}
