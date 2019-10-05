#ifndef FORTHY2_CX_HPP
#define FORTHY2_CX_HPP

#include <iostream>
#include <unordered_map>

#include "forthy2/defer.hpp"
#include "forthy2/env.hpp"
#include "forthy2/pool.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/sym.hpp"
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

    Node<Val> gc_vals;
    
    Env root_env, *env;
    Stack root_stack, *stack;

    Cx(): env(&root_env), stack(&root_stack) { }
    
    void deinit() {}

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
}

#endif
