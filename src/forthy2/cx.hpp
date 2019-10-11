#ifndef FORTHY2_CX_HPP
#define FORTHY2_CX_HPP

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "forthy2/bool.hpp"
#include "forthy2/defer.hpp"
#include "forthy2/env.hpp"
#include "forthy2/fix.hpp"
#include "forthy2/forms/dot.hpp"
#include "forthy2/forms/id.hpp"
#include "forthy2/forms/lit.hpp"
#include "forthy2/forms/pair.hpp"
#include "forthy2/forms/scope.hpp"
#include "forthy2/int.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/method.hpp"
#include "forthy2/method_set.hpp"
#include "forthy2/node.hpp"
#include "forthy2/ops/call.hpp"
#include "forthy2/ops/check.hpp"
#include "forthy2/ops/pair.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/pair.hpp"
#include "forthy2/path.hpp"
#include "forthy2/pool.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/read.hpp"
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
    Pool<ScopeForm> scope_form;

    Pool<CallOp> call_op;
    Pool<CheckOp> check_op;
    Pool<PairOp> pair_op;
    Pool<PushOp> push_op;

    uint64_t type_weight;
    Node<Val> marked_vals, unmarked_vals;

    Type &a_type;

    PoolType<Bool> &bool_type;
    PoolType<Fix> &fix_type;
    PoolType<Int> &int_type;
    PoolType<Macro> &macro_type;
    Type &meta_type;
    PoolType<MethodSet> &method_set_type;
    PoolType<Method> &method_type;
    PoolType<Pair> &pair_type;
    PoolType<Stack> &stack_type;
    Type &sym_type;
        
    Env root_env, *env;
    Stack root_stack, *stack;
    Node<Op> ops;

    Path load_path;
    istream *stdin;
    ostream *stdout, *stderr;
    
    Cx():
      type_weight(1),
      a_type(*new Type(*this, sym("A"))),
      bool_type(*new PoolType<Bool>(*this, sym("Bool"), {&a_type})),
      fix_type(*new PoolType<Fix>(*this, sym("Fix"), {&a_type})),
      int_type(*new PoolType<Int>(*this, sym("Int"), {&a_type})),
      macro_type(*new PoolType<Macro>(*this, sym("Macro"), {&a_type})),
      meta_type(*new Type(*this, sym("Meta"), {&a_type})),
      method_set_type(*new PoolType<MethodSet>(*this, sym("MethodSet"), {&a_type})),
      method_type(*new PoolType<Method>(*this, sym("Method"), {&a_type})),
      pair_type(*new PoolType<Pair>(*this, sym("Pair"), {&a_type})),
      stack_type(*new PoolType<Stack>(*this, sym("Stack"), {&a_type})),
      sym_type(*new Type(*this, sym("Sym"), {&a_type})),
      env(&root_env),
      stack(&root_stack),
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

      unmarked_vals.extend(marked_vals);
      sweep_vals();

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
      eval(pc);      
    }

    void eval(Node<Op> &pc) { eval(pc, ops); }
    
    void eval(Node<Op> &beg, Node<Op> &end) {
      for (Node<Op> *op(beg.next); op != &end;) { op = &op->get().eval(*this); }
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
    
    bool mark_vals(optional<uint64_t> max_ns = {}) {
      Timer t;

      if (!unmarked_vals) {
        for (auto i(marked_vals.next); i != &marked_vals; i = i->next) {
          i->get().unmark();
        }
        
        unmarked_vals.extend(marked_vals);
      }
      
      for (Env *e(env); e; e = e->prev) {
        if (max_ns && t.ns() >= *max_ns) { return false; }
        e->mark_items(*this);
      }
      
      for (Stack *s(stack); s; s = s->prev) {
        if (max_ns && t.ns() >= *max_ns) { return false; }
        s->mark_items(*this);
      }

      for (Node<Op> *op(ops.next); op != &ops; op = op->next) {
        op->get().mark_vals(*this);
      }
      
      return true;
    }

    Val &pop() { return stack->pop(); }

    Val &pop(Pos pos) {
      if (stack->empty()) { throw ESys(pos, "Stack is empty"); }
      return pop();
    }

    template <typename T>
    T &pop(Pos pos, PoolType<T> &type) {
      Val &v(pop(pos));
      Type &vt(v.type(*this));
      if (!vt.isa(type)) { ESys(pos, "Expected ", type.id, ": ", vt.id); }
      return dynamic_cast<T &>(v);
    }

    void push(Val &val) { stack->push(val); }
    
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

    bool sweep_vals(optional<uint64_t> max_ns = {}) {
      Timer t;

      for (auto i(unmarked_vals.prev); i != &unmarked_vals;) {
        if (max_ns && t.ns() >= *max_ns) { return false; }
        Val &v(i->get());
        i = i->prev;
        v.sweep(*this);
      }

      return true;
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
    T with_env(Env &e, function<T ()> body) {
      Env *prev(env);
      env = &e;  
      e.prev = prev;
      auto restore(defer([&]() { env = prev; }));
      return body();
    }

    void with_stack(Stack &s, function<void ()> body) {
      Stack *prev(stack);
      stack = &s;  
      s.prev = prev;
      auto restore(defer([&]() { stack = prev; }));
      body();
    }
  };

  template <typename T>
  template <typename...Args>
  T &PoolType<T>::get(Cx &cx, Args &&...args) {
    T &v(pool.get(forward<Args>(args)...));
    cx.marked_vals.push(v);
    return v;
  }
}

#endif
