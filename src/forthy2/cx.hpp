#ifndef FORTHY2_CX_HPP
#define FORTHY2_CX_HPP

#include <iostream>
#include <unordered_map>

#include "forthy2/defer.hpp"
#include "forthy2/env.hpp"
#include "forthy2/node.hpp"
#include "forthy2/pool.hpp"
#include "forthy2/pool_type.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/timer.hpp"
#include "forthy2/types/int.hpp"
#include "forthy2/types/method.hpp"
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

    PoolType<IntVal> int_type;
    PoolType<MethodVal> method_type;
    PoolType<PairVal> pair_type;
    PoolType<StackVal> stack_type;
    PoolType<SymVal> sym_type;

    Node<Val> marked_vals, unmarked_vals;
    
    Env root_env, *env;
    Stack root_stack, *stack;

    Cx():
      int_type("Int"),
      method_type("Method"),
      pair_type("Pair"),
      stack_type("Stack"),
      sym_type("Sym"),
      env(&root_env),
      stack(&root_stack) { }
    
    void deinit() {
      unmarked_vals = move(marked_vals);
      sweep_vals();

      for (auto &s: syms) { sym_pool.put(s.second); }
    }
    
    bool mark_vals(optional<uint64_t> max_ns = {}) {
      Timer t;

      if (!unmarked_vals) {
        for (auto i(marked_vals.next); i != &marked_vals; i = i->next) {
          i->get().unmark();
        }
        
        unmarked_vals = move(marked_vals);
      }
      
      for (Env *e(env); e; e = e->prev) {
        if (max_ns && t.ns() >= *max_ns) { return false; }
        e->mark_items(*this);
      }
      
      for (Stack *s(stack); s; s = s->prev) {
        if (max_ns && t.ns() >= *max_ns) { return false; }
        s->mark_items(*this);
      }

      return true;
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
    const Sym *sym(const string &spec, Args &&...args) {
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
  T *PoolType<T>::get(Cx &cx, Args &&...args) {
    T *v(pool.get(forward<Args>(args)...));
    cx.marked_vals.push(*v);
    return v;
  }
}

#endif
