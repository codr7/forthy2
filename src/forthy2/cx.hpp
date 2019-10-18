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
#include "forthy2/forms/pair.hpp"
#include "forthy2/forms/ref.hpp"
#include "forthy2/forms/scope.hpp"
#include "forthy2/forms/stack.hpp"
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
#include "forthy2/ops/pair.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/ops/return.hpp"
#include "forthy2/ops/stack.hpp"
#include "forthy2/pair.hpp"
#include "forthy2/path.hpp"
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
    
    Pool<Sym> sym_pool;
    unordered_map<string, Sym *> syms;

    Pool<DotForm> dot_form;
    Pool<IdForm> id_form;
    Pool<LitForm> lit_form;
    Pool<PairForm> pair_form;
    Pool<RefForm> ref_form;
    Pool<ScopeForm> scope_form;
    Pool<StackForm> stack_form;

    Pool<CallOp> call_op;
    Pool<CheckOp> check_op;
    Pool<ClockOp> clock_op;
    Pool<BranchOp> branch_op;
    Pool<PairOp> pair_op;
    Pool<PushOp> push_op;
    Pool<ReturnOp> return_op;
    Pool<StackOp> stack_op;

    uint64_t type_weight;
    Node<Val> marked, unmarked;

    NilType &nil_type;
    Type &a_type;

    BoolType &bool_type;

    FnType &fn_type;
    LambdaType &lambda_type;
    PoolType<Method> &method_type;
    PoolType<MethodSet> &method_set_type;

    PoolType<Macro> &macro_type;
    Type &meta_type;

    Type &num_type;
    PoolType<Fix> &fix_type;
    IntType &int_type;

    PoolType<Pair> &pair_type;
    PoolType<Stack> &stack_type;
    Type &sym_type;
        
    Scope root_scope, *scope;
    Stack root_stack, *stack;
    
    Pool<Call> call_pool;
    Call *call;

    Node<Op> ops;

    Nil _;
    Bool F, T;
    Int int_zero;
    
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

      macro_type(*new PoolType<Macro>(*this, sym("Macro"), {&a_type})),
      meta_type(*new Type(*this, sym("Meta"), {&a_type})),

      num_type(*new Type(*this, sym("Num"), {&a_type})),
      fix_type(*new PoolType<Fix>(*this, sym("Fix"), {&num_type})),
      int_type(*new IntType(*this, sym("Int"), {&num_type})),

      pair_type(*new PoolType<Pair>(*this, sym("Pair"), {&a_type})),
      stack_type(*new PoolType<Stack>(*this, sym("Stack"), {&a_type})),
      sym_type(*new Type(*this, sym("Sym"), {&a_type})),
      scope(&root_scope),
      stack(&root_stack),
      call(nullptr),
      F(false),
      T(true),
      int_zero(0),
      stdin(&cin),
      stdout(&cout),
      stderr(&cerr) { }

    Node<Op> &compile(Forms &in, Node<Op> &out) {
      Forms tmp(in);
      reverse(tmp.begin(), tmp.end());
      Node<Op> *op(&out);

      while (!tmp.empty()) {
        Form &f(*tmp.back());
        tmp.pop_back();
        op = &f.compile(*this, tmp, *op);
        
        if (debug && op != &ops) {
          op->get().dump(*stdout);
          (*stdout) << endl;
        }
      }
      
      if (debug) { (*stdout) << endl; }
      return *op;
    }
    
    void deinit() {
      for (Node<Op> *op(ops.next); op != &ops;) {
        Node<Op> *next(op->next);
        op->get().dealloc(*this);
        op = next;
      }

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
      Node<Op> &pc(*ops.prev);
      compile(forms, pc);
      deref(forms);
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
    
    optional<uint64_t> mark(optional<uint64_t> max_ns = {}) {
      Timer t;

      if (!unmarked) {
        for (auto i(marked.next); i != &marked; i = i->next) { i->get().unmark(); }
        unmarked.extend(marked);
      }
      
      for (Scope *e(scope); e; e = e->prev) {
        if (max_ns && t.ns() >= *max_ns) { return {}; }
        e->mark_items(*this);
      }
      
      for (Stack *s(stack); s; s = s->prev) {
        if (max_ns && t.ns() >= *max_ns) { return {}; }
        s->mark_items(*this);
      }

      for (Node<Op> *op(ops.next); op != &ops; op = op->next) {
        if (max_ns && t.ns() >= *max_ns) { return {}; }
        op->get().mark_vals(*this);
      }

      return t.ns();
    }

    optional<uint64_t> mark_sweep(optional<uint64_t> max_ns = {}) {
      if (auto mark_ns(mark(max_ns)); mark_ns) {
        if (max_ns) { *max_ns -= min(*max_ns, *mark_ns); }
        if (auto sweep_ns(sweep(max_ns)); sweep_ns) { return *mark_ns + *sweep_ns; }
      }

      return {};
    }

    Val &peek(size_t offs = 0) { return stack->peek(offs); }

    Val &pop() { return stack->pop(); }

    Val &pop(Pos pos) {
      if (stack->empty()) { throw ESys(pos, "Stack is empty"); }
      return pop();
    }

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
    
    void push_call(Op &pc, Fn &fn, Node<Op> &return_pc) {
      call = &call_pool.get(call, pc, fn, return_pc);
    }

    void read(istream &in, Forms &out) {
      Pos p;
      Form *f(nullptr);
      
      while ((f = read_form(*this, p, in))) {
        out.push_back(f);

        if (debug) {
          f->dump(*stdout);
          (*stdout) << endl;
        }
      }

      if (debug) { (*stdout) << endl; }
    }

    optional<uint64_t> sweep(optional<uint64_t> max_ns = {}) {
      Timer t;

      for (auto i(unmarked.prev); i != &unmarked;) {
        if (max_ns && t.ns() >= *max_ns) { return {}; }
        Val &v(i->get());
        i = i->prev;
        v.sweep(*this);
      }

      return t.ns();
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

  template <typename T>
  template <typename...Args>
  T &PoolType<T>::get(Cx &cx, Args &&...args) {
    T &v(pool.get(forward<Args>(args)...));
    cx.marked.push(v);
    return v;
  }

  inline bool Method::applicable(Cx &cx) {
    Stack::Items &s(cx.stack->items);
    auto ss(s.size());
    if (ss < args.len()) { return false; }
    Val **sv = &s[ss-args.len()];

    for (Arg &a: args.items) {
      if (a.val) {
        if (!a.val->eq(**sv)) { return false; }
      } else if (!(*sv)->type(cx).isa(*a.type)) {
        return false;
      }

      sv++;
    }

    return true;
  }
  
  inline Node<Op> &Method::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    if (safe && !applicable(cx)) {
      throw ESys(pc.form.pos, "Method not applicable: ", id);
    }
    
    return imp ? imp(cx, pc) : fn.call(cx, pc, return_pc, safe);
  }

  inline Node<Op> &MethodSet::call(Cx &cx, Op &pc, Node<Op> &return_pc, bool safe) {
    Method *m(dispatch(cx));
    if (!m) { throw ESys(pc.form.pos, "Method not applicable: ", id); }
    return m->call(cx, pc, return_pc, false);
  }

  inline Method *MethodSet::dispatch(Cx &cx) {
    for (Node<Method> *i(root.prev); i != &root; i = i->prev) {
      if (Method &m(i->get()); m.applicable(cx)) { return &m; }
    }

    return nullptr;
  }
}

#endif
