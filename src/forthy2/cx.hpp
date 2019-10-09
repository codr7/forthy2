#ifndef FORTHY2_CX_HPP
#define FORTHY2_CX_HPP

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "forthy2/defer.hpp"
#include "forthy2/env.hpp"
#include "forthy2/forms/id.hpp"
#include "forthy2/forms/lit.hpp"
#include "forthy2/forms/pair.hpp"
#include "forthy2/node.hpp"
#include "forthy2/ops/bind.hpp"
#include "forthy2/ops/pair.hpp"
#include "forthy2/ops/push.hpp"
#include "forthy2/path.hpp"
#include "forthy2/pool.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/read.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/timer.hpp"
#include "forthy2/types/fix.hpp"
#include "forthy2/types/int.hpp"
#include "forthy2/types/macro.hpp"
#include "forthy2/types/meta.hpp"
#include "forthy2/types/method.hpp"
#include "forthy2/types/method_set.hpp"
#include "forthy2/types/pair.hpp"
#include "forthy2/types/stack.hpp"
#include "forthy2/types/sym.hpp"
#include "forthy2/util.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Sym;
  
  struct Cx {
    bool debug = false;
    ostream &out = cout;
    
    Pool<Sym> sym_pool;
    unordered_map<string, Sym *> syms;

    Pool<IdForm> id_form;
    Pool<LitForm> lit_form;
    Pool<PairForm> pair_form;

    Pool<BindOp> bind_op;
    Pool<PairOp> pair_op;
    Pool<PushOp> push_op;

    uint64_t type_weight;
    Pool<MetaVal> type_pool;
    Node<Val> marked_vals, unmarked_vals;

    Type &any_type;
    Type &meta_type;

    PoolType<FixVal> &fix_val;
    PoolType<IntVal> &int_val;
    PoolType<MacroVal> &macro_val;
    PoolType<MethodSetVal> &method_set_val;
    PoolType<MethodVal> &method_val;
    PoolType<PairVal> &pair_val;
    PoolType<StackVal> &stack_val;
    PoolType<SymVal> &sym_val;
        
    Env root_env, *env;
    Stack root_stack, *stack;
    Node<Op> ops;

    Path load_path;
    istream *stdin;
    ostream *stdout, *stderr;
    
    Cx():
      type_weight(1),
      any_type(*new Type(*this, sym("Any"))),
      meta_type(*new Type(*this, sym("Meta"), {&any_type})),
      fix_val(*new PoolType<FixVal>(*this, sym("Fix"), {&any_type})),
      int_val(*new PoolType<IntVal>(*this, sym("Int"), {&any_type})),
      macro_val(*new PoolType<MacroVal>(*this, sym("Macro"), {&any_type})),
      method_set_val(*new PoolType<MethodSetVal>
                     (*this, sym("MethodSet"), {&any_type})),
      method_val(*new PoolType<MethodVal>(*this, sym("Method"), {&any_type})),
      pair_val(*new PoolType<PairVal>(*this, sym("Pair"), {&any_type})),
      stack_val(*new PoolType<StackVal>(*this, sym("Stack"), {&any_type})),
      sym_val(*new PoolType<SymVal>(*this, sym("Sym"), {&any_type})),
      env(&root_env),
      stack(&root_stack),
      stdin(&cin),
      stdout(&cout),
      stderr(&cerr) { }

    Node<Op> &compile(Forms &in, Node<Op> &out) {
      Node<Op> *op(&out);

      for (auto i(in.begin()); i != in.end();) {
        auto j(i++);
        op = &(*j)->compile(*this, i, in.end(), *op);
        op->get().dump(cout);
        cout << endl;
      }

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

      for (auto &s: syms) { sym_pool.put(s.second); }      
    }

    void deref(Forms &in) {
      for (auto i(in.begin()); i != in.end();) {
        Form *f(*i++);
        f->deref(*this);
      }
    }

    void eval(Node<Op> &root) {
      for (Node<Op> *op(root.next); op != &root;) { op = op->get().eval(*this); }
    }

    const Sym *get_id(const Sym *set_id, Args &args) {
      stringstream buf;
      buf << set_id->name;
      dump(args, buf);
      return sym(buf.str());
    }

    uint64_t get_weight(Args &args) {
      uint64_t weight(0);
      
      for (Arg &a: args) {
        weight += a.val ? a.val->get_type(*this).weight + 1 : a.type->weight;
      }
      
      return weight;
    }

    void load(const Pos &pos, const Path &path) {
      auto in_path(path.is_absolute() ? path : load_path/path);
      ifstream in(in_path);
      if (in.fail()) { throw ESys(pos, "File not found: ", in_path); }
      
      auto prev_load_path(load_path);
      load_path = path.parent_path();
      auto restore_load_path(defer([&]() { load_path = prev_load_path; }));

      Forms forms;
      read(in, forms);
      Node<Op> &pc(*ops.prev);
      compile(forms, pc);
      deref(forms);
      eval(pc);
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

    void read(istream &in, Forms &out) {
      Pos p;
      Form *f(nullptr);
      
      while ((f = read_form(*this, p, in))) {
        f->dump(cout);
        cout << endl;
        out.push_back(f);
      }
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
    const Sym *sym(Args &&...args) {
      string name(str(forward<Args>(args)...));
      auto ok(syms.find(name));
      if (ok != syms.end()) { return ok->second; }    
      Sym *s(sym_pool.get(name));
      syms.emplace(make_pair(name, s));
      return s;
    }

    template <typename T, typename...Args>
    auto with_env(Env &e, T body, Args &&...args) {
      Env *prev(env);
      env = &e;  
      e.prev = prev;
      auto restore(defer([&]() { env = prev; }));
      return body(forward<Args>(args)...);
    }

    template <typename T, typename...Args>
    auto with_stack(Stack &s, T body, Args &&...args) {
      Stack *prev(stack);
      stack = &s;  
      s.prev = prev;
      auto restore(defer([&]() { stack = prev; }));
      return body(forward<Args>(args)...);
    }
  };

  template <typename T>
  template <typename...Args>
  T &PoolType<T>::get(Cx &cx, Args &&...args) {
    T &v(*pool.get(forward<Args>(args)...));
    cx.marked_vals.push(v);
    return v;
  }
}

#endif
