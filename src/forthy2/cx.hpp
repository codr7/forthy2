#ifndef FORTHY2_CX_HPP
#define FORTHY2_CX_HPP

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "forthy2/bool.hpp"
#include "forthy2/call.hpp"
#include "forthy2/defer.hpp"
#include "forthy2/fn.hpp"
#include "forthy2/fix.hpp"
#include "forthy2/forms/dot.hpp"
#include "forthy2/forms/id.hpp"
#include "forthy2/forms/lit.hpp"
#include "forthy2/forms/nil.hpp"
#include "forthy2/forms/pair.hpp"
#include "forthy2/forms/quote.hpp"
#include "forthy2/forms/ref.hpp"
#include "forthy2/forms/scope.hpp"
#include "forthy2/forms/splice.hpp"
#include "forthy2/forms/stack.hpp"
#include "forthy2/forms/unquote.hpp"
#include "forthy2/int.hpp"
#include "forthy2/lambda.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/method.hpp"
#include "forthy2/method_set.hpp"
#include "forthy2/nil.hpp"
#include "forthy2/node.hpp"
#include "forthy2/ops/branch.hpp"
#include "forthy2/ops/call.hpp"
#include "forthy2/ops/check.hpp"
#include "forthy2/ops/clock.hpp"
#include "forthy2/ops/copy.hpp"
#include "forthy2/ops/drop.hpp"
#include "forthy2/ops/for.hpp"
#include "forthy2/ops/pair.hpp"
#include "forthy2/ops/peek.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/ops/repeat.hpp"
#include "forthy2/ops/restack.hpp"
#include "forthy2/ops/return.hpp"
#include "forthy2/ops/rotl.hpp"
#include "forthy2/ops/rotr.hpp"
#include "forthy2/ops/stack.hpp"
#include "forthy2/ops/swap.hpp"
#include "forthy2/pair.hpp"
#include "forthy2/path.hpp"
#include "forthy2/peek.hpp"
#include "forthy2/pool.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/read.hpp"
#include "forthy2/scope.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/timer.hpp"
#include "forthy2/type.hpp"
#include "forthy2/util.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Sym;
  
  struct Cx {
    bool debug = false;
    int unsafe = 0;
    
    Pool<Sym> sym_pool;
    unordered_map<string, Sym *> syms;

    Pool<DotForm> dot_form;
    Pool<IdForm> id_form;
    Pool<LitForm> lit_form;
    Pool<PairForm> pair_form;
    Pool<QuoteForm> quote_form;
    Pool<RefForm> ref_form;
    Pool<ScopeForm> scope_form;
    Pool<SpliceForm> splice_form;
    Pool<StackForm> stack_form;
    Pool<UnquoteForm> unquote_form;

    Pool<CallOp> call_op;
    Pool<CheckOp> check_op;
    Pool<ClockOp> clock_op;
    Pool<CopyOp> copy_op;
    Pool<DropOp> drop_op;
    Pool<BranchOp> branch_op;
    Pool<ForOp> for_op;
    Pool<PairOp> pair_op;

    Pool<PeekOp> peek_op;
    Pool<Peek> peek_pool;
    
    Pool<PushOp> push_op;
    Pool<RepeatOp> repeat_op;
    Pool<RestackOp> restack_op;
    Pool<ReturnOp> return_op;
    Pool<RotlOp> rotl_op;
    Pool<RotrOp> rotr_op;
    Pool<StackOp> stack_op;
    Pool<SwapOp> swap_op;

    uint64_t type_weight;
    Node<Val> marked, unmarked;

    NilType &nil_type;
    Type &a_type;

    BoolType &bool_type;

    FnType &fn_type;
    LambdaType &lambda_type;
    PoolType<Method> &method_type;
    PoolType<MethodSet> &method_set_type;

    FormType &form_type;
    PoolType<Macro> &macro_type;
    Type &meta_type;

    Type &num_type;
    PoolType<Fix> &fix_type;
    IntType &int_type;

    PeekType &peek_type;
    PoolType<Pair> &pair_type;
    PoolType<Stack> &stack_type;
    Type &sym_type;
    TimeType &time_type;
        
    Scope root_scope, *scope;
    Stack root_stack, *stack, alt_stack;
    
    Pool<Call> call_pool;
    Call *call;

    Node<Op> ops;

    NilForm nil_form;
    Nil _;

    Bool F, T;
    vector<Int> ints;
    vector<Peek> peeks;
    
    Path load_path;
    istream *stdin;
    ostream *stdout, *stderr;
    
    Cx():
      type_weight(1),
      nil_type(*new NilType(*this, sym("Nil"))),
      a_type(*new Type(*this, sym("A"))),

      bool_type(*new BoolType(*this, sym("Bool"), {&a_type})),

      fn_type(*new FnType(*this, sym("Fn"), {&a_type})),
      lambda_type(*new LambdaType(*this, sym("Lambda"), {&fn_type})),
      method_type(*new PoolType<Method>(*this, sym("Method"), {&fn_type})),
      method_set_type(*new PoolType<MethodSet>(*this, sym("MethodSet"), {&fn_type})),

      form_type(*new FormType(*this, sym("Form"), {&a_type})),
      macro_type(*new PoolType<Macro>(*this, sym("Macro"), {&a_type})),
      meta_type(*new Type(*this, sym("Meta"), {&a_type})),

      num_type(*new Type(*this, sym("Num"), {&a_type})),
      fix_type(*new PoolType<Fix>(*this, sym("Fix"), {&num_type})),
      int_type(*new IntType(*this, sym("Int"), {&num_type})),

      peek_type(*new PeekType(*this, sym("Peek"), {&a_type})),
      pair_type(*new PoolType<Pair>(*this, sym("Pair"), {&a_type})),
      stack_type(*new PoolType<Stack>(*this, sym("Stack"), {&a_type})),
      sym_type(*new Type(*this, sym("Sym"), {&a_type})),
      time_type(*new TimeType(*this, sym("Time"), {&a_type})),
      scope(&root_scope),
      stack(&root_stack),
      call(nullptr),
      F(false),
      T(true),
      stdin(&cin),
      stdout(&cout),
      stderr(&cerr) {
      ints.emplace_back(0);
    }

    void init_ints(Int::Imp max) {
      ints.reserve(max * 2 + 1);
      
      for (Int::Imp i(ints.size()); i < max; i++) {
        ints.emplace_back(-i);
        ints.emplace_back(i);
      }
    }

    void init_peeks(Int::Imp max) {
      peeks.reserve(max + 1);
      for (Int::Imp i(peeks.size()); i < max; i++) { peeks.emplace_back(i); }
    }
    
    Node<Op> &compile(Forms &in, Node<Op> &out, int quote = 0) {
      Forms tmp(in);
      reverse(tmp.begin(), tmp.end());
      Node<Op> *op(&out);

      while (!tmp.empty()) {
        Form &f(*tmp.back());
        tmp.pop_back();
        op = &f.compile(*this, tmp, *op, quote);
      }
      
      return *op;
    }

    void dealloc(Node<Op> &root) {
      for (Node<Op> *op(root.next); op != &root;) {
        Node<Op> *next(op->next);
        op->get().dealloc(*this);
        op = next;
      }
    }

    void deinit() {
      dealloc(ops);
      unmarked.extend(marked);
      sweep();

      for (auto &s: syms) { sym_pool.put(*s.second); }      
    }

    void deref(Forms &in) {
      for (auto i(in.begin()); i != in.end();) {
        Form *f(*i++);
        f->deref(*this);
      }
    }

    void eval(const string &in) {
      stringstream in_buf(in);
      eval(in_buf);
    }

    void eval(istream &in) {
      Forms forms;
      read(in, forms);
      eval(forms);
    }

    void eval(Forms &in, int quote = 0) {
      Node<Op> &pc(*ops.prev);
      compile(in, pc, quote);
      deref(in);
      eval(pc, ops);      
    }

    void eval(Node<Op> &beg_pc, Node<Op> &end_pc) {
      for (Node<Op> *op(beg_pc.next); op != &end_pc; op = &op->get().eval(*this));
    }

    void load(Pos pos, const Path &path) {
      auto in_path(path.is_absolute() ? path : load_path/path);
      ifstream in(in_path);
      if (in.fail()) { throw ESys(pos, "File not found: ", in_path); }
      
      auto prev_load_path(load_path);
      load_path = path.parent_path();
      auto restore_load_path(defer([&]() { load_path = prev_load_path; }));
      eval(in);
    }
    
    optional<Time::Imp> mark(optional<Time::Imp> max_time = {}) {
      Timer t;

      if (!unmarked) {
        for (auto i(marked.next); i != &marked; i = i->next) { i->get().unmark(); }
        unmarked.extend(marked);
      }
      
      for (Scope *e(scope); e; e = e->prev) {
        if (max_time && t.get() >= *max_time) { return {}; }
        e->mark_items(*this);
      }
      
      for (Stack *s(stack); s; s = s->prev) {
        if (max_time && t.get() >= *max_time) { return {}; }
        s->mark_items(*this);
      }

      for (Node<Op> *op(ops.next); op != &ops; op = op->next) {
        if (max_time && t.get() >= *max_time) { return {}; }
        op->get().mark_vals(*this);
      }

      return t.get();
    }

    optional<Time::Imp> sweep(optional<Time::Imp> max_time = {}) {
      Timer t;

      for (auto i(unmarked.prev); i != &unmarked;) {
        if (max_time && t.get() >= *max_time) { return {}; }
        Val &v(i->get());
        i = i->prev;
        v.sweep(*this);
      }

      return t.get();
    }

    optional<Time::Imp> mark_sweep(optional<Time::Imp> max_time = {}) {
      if (auto mark_time(mark(max_time)); mark_time) {
        if (max_time) { *max_time -= min(*max_time, *mark_time); }

        if (auto sweep_time(sweep(max_time)); sweep_time) {
          return *mark_time + *sweep_time;
        }
      }

      return {};
    }

    Val &peek(size_t offs = 0) { return stack->peek(offs); }

    void poke(Val &val, size_t offs = 0) { stack->poke(val, offs); }

    template <typename T>
    T &peek(ValType<T> &type, size_t offs = 0) {
      return dynamic_cast<T &>(peek(offs));
    }

    template <typename T>
    T &peek(Pos pos, ValType<T> &type, size_t offs = 0) {
      if (stack->len() < offs + 1) { throw ESys(pos, "Stack offset out of bounds"); }
      Val &v(peek(offs));
      Type &vt(v.type(*this));
      if (!vt.isa(type)) { ESys(pos, "Expected ", type.id, ": ", vt.id); }
      return dynamic_cast<T &>(v);
    }

    Val &pop() { return stack->pop(); }

    Val &pop(Pos pos) {
      if (stack->empty()) { throw ESys(pos, "Stack is empty"); }
      return pop();
    }

    template <typename T>
    T &pop(ValType<T> &type) { return dynamic_cast<T &>(pop()); }

    template <typename T>
    T &pop(Pos pos, ValType<T> &type) {
      Val &v(pop(pos));
      Type &vt(v.type(*this));
      if (!vt.isa(type)) { ESys(pos, "Expected ", type.id, ": ", vt.id); }
      return dynamic_cast<T &>(v);
    }

    Node<Op> &pop_call() {
      assert(call);
      Call &c(*call);
      call = call->prev;
      Node<Op> &rpc(c.return_pc);
      call_pool.put(c);
      return rpc;
    }

    void push(Val &val) { stack->push(val); }
    
    void push_call(Pos &pos, Fn &fn, Node<Op> &return_pc) {
      call = &call_pool.get(call, pos, fn, return_pc);
    }

    void read(istream &in, Forms &out) {
      Pos p;
      Form *f(nullptr);
      while ((f = read_form(*this, p, in, true))) { out.push_back(f); }
    }
    
    template <typename...Args>
    Sym &sym(Args &&...args) {
      string name(str(forward<Args>(args)...));
      auto ok(syms.find(name));
      if (ok != syms.end()) { return *ok->second; }    
      Sym &s(sym_pool.get(name));
      syms.emplace(make_pair(name, &s));
      return s;
    }

    template <typename T>
    T with_scope(Scope &e, function<T ()> body) {
      Scope *prev(scope);
      scope = &e;  
      e.prev = prev;
      auto restore(defer([&]() { scope = prev; }));
      return body();
    }

    template <typename T>
    T with_stack(Stack &s, function<T ()> body) {
      Stack *prev(stack);
      stack = &s;  
      s.prev = prev;
      auto restore(defer([&]() { stack = prev; }));
      return body();
    }
  };

  inline Bool &BoolType::get(Cx &cx, bool imp) { return imp ? cx.T : cx.F; }

  inline Node<Op> &BranchOp::eval(Cx &cx) {
    if (cx.peek() == neg) {
      if (pop_if) { cx.pop(); }
      return *pc->next;
    }
    
    if (pop_else) { cx.pop(); }
    return *Node<Op>::next;
  }

  inline Node<Op> &CallOp::eval(Cx &cx) {
    Val &v(val ? *val : cx.pop(form.pos));
    return v.call(cx, form.pos, *this, safe);
  }

  inline Node<Op> &CopyOp::eval(Cx &cx) {
    auto &s(*cx.stack);
    if (s.empty()) { throw ESys(form.pos, "Nothing to copy"); }
    s.copy();
    return *Node<Op>::next;   
  }

  inline Node<Op> &DropOp::eval(Cx &cx) {
    auto &s(*cx.stack);
    if (s.empty()) { throw ESys(form.pos, "Nothing to drop"); }
    auto beg(s.end() - offs - 1);
    s.items.erase(beg, beg + n);
    return *Node<Op>::next;
  }

  inline Node<Op> &Fn::call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe) {
    cx.push_call(pos, *this, return_pc);
    return *ops.next;
  }

  inline Node<Op> &ForOp::eval(Cx &cx) {
    Val &in(cx.pop(form.pos));

    in.iter(cx, [&](Val &val) {
        cx.push(val);
        if (end_pc != this) { cx.eval(*this, *end_pc->next); }
        return true;
      });

    return *end_pc->next;
  }

  inline Int &IntType::get(Cx &cx, Int::Imp imp) {
    size_t i((imp < 0) ? -imp * 2 - 1: imp * 2);
    return (i < cx.ints.size()) ? cx.ints[i] : PoolType<Int>::get(cx, imp);
  }

  inline bool Method::applicable(Cx &cx) {
    Stack::Items &stack(cx.stack->items);
    auto ss(stack.size());
    if (ss < args.len()) { return false; }
    Val **s(&stack[ss - args.len()]);

    for (Arg &a: args.items) {
      Type &at(a.val ? a.val->type(cx) : *a.type), &st((*s)->type(cx));
      if ((a.val && (&at != &st || !a.val->eq(**s))) || !st.isa(at)) { return false; }
      s++;
    }

    return true;
  }
  
  inline Node<Op> &Method::call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe) {
    if (cx.unsafe <= 0 && safe && !applicable(cx)) {
      throw ESys(pos, "Method not applicable: ", id.name, '\n', *cx.stack);
    }
    
    return imp ? imp(cx, pos, return_pc) : fn.call(cx, pos, return_pc, safe);
  }

  inline Node<Op> &MethodSet::call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe) {
    Method *m(dispatch(cx));
    if (!m) { throw ESys(pos, "Method not applicable: ", id.name); }
    return m->call(cx, pos, return_pc, false);
  }

  inline Method *MethodSet::dispatch(Cx &cx) {
    for (Node<Method> *i(root.prev); i != &root; i = i->prev) {
      if (Method &m(i->get()); m.applicable(cx)) { return &m; }
    }

    return nullptr;
  }

  inline Node<Op> &PeekOp::eval(Cx &cx) {
    auto &s(alt_src ? cx.alt_stack : *cx.stack);
    auto sl(s.len());
    if (sl < offs + 1) { throw ESys(form.pos, "Nothing to peek (", offs, "): ", s); }
    cx.push(*s.items[sl - offs - 1]);
    return *Node<Op>::next;
  }

  template <typename T>
  template <typename...Args>
  T &PoolType<T>::get(Cx &cx, Args &&...args) {
    T &v(pool.get(forward<Args>(args)...));
    cx.marked.push(v);
    return v;
  }

  inline Node<Op> &PushOp::eval(Cx &cx) {
    cx.push(val);
    return *Node<Op>::next;
  }

  inline Node<Op> &RepeatOp::eval(Cx &cx) {
    Int::Imp end(cx.pop(form.pos, cx.int_type).imp);
    for (Int::Imp i(0); i < end; i++) { cx.eval(*this, *end_pc->next); }
    return *end_pc->next;
  }

  inline Node<Op> &RestackOp::eval(Cx &cx) {
    if (cx.stack->len() < in_len) {
      throw ESys(form.pos, "Nothing to restack: ", *cx.stack);
    }
    
    auto end(cx.stack->end()), beg(end - in_len);
    move(beg, end, back_inserter(cx.alt_stack.items));
    cx.stack->items.erase(beg, end);
    cx.eval(*this, *end_pc->next);
    auto alt_end(cx.alt_stack.end());
    cx.alt_stack.items.erase(alt_end - in_len, alt_end);
    return *end_pc->next;
  }

  inline Node<Op> &ReturnOp::eval(Cx &cx) { return *cx.pop_call().next; }

  inline Node<Op> &RotlOp::eval(Cx &cx) {
    auto &s(*cx.stack);
    if (s.len() < 3) { throw ESys(form.pos, "Nothing to rotl: ", s); }
    rotate(s.end() - 3, s.end() - 1, s.end());
    return *Node<Op>::next;
  }

  inline Node<Op> &RotrOp::eval(Cx &cx) {
    auto &s(*cx.stack);
    if (s.len() < 3) { throw ESys(form.pos, "Nothing to rotr: ", s); }
    rotate(s.end() - 3, s.end() - 2, s.end());
    return *Node<Op>::next;
  }

  inline Node<Op> &SwapOp::eval(Cx &cx) {
    auto &s(*cx.stack);
    auto &is(s.items);
    auto i(is.size());
    if (i-- < 2) { throw ESys(form.pos, "Nothing to swap: ", s); }
    swap(is[i], is[i - 1]);
    return *Node<Op>::next;   
  }
}

#endif
