#ifndef FORTHY2_ENV_HPP
#define FORTHY2_ENV_HPP

#include <algorithm>
#include <vector>

#include "forthy2/arg.hpp"
#include "forthy2/e.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Macro;
  struct Method;
  struct Pos;
  struct Sym;
  struct Type;
  struct Val;
  
  struct Env {
    struct Item {
      Env *home;
      Sym *id;
      Val *val;
      
      Item(Env *home, Sym &id, Val &val);
    };
      
    using Items = vector<Item>;
    using Iter = Items::iterator;
    
    Env *prev = nullptr;
    Items items;

    Env();
    Env(Cx &cx, Env &in);
    
    Macro &add_macro(Cx &cx, Pos pos, Sym &id, const vector<Arg> &args = {});
    Method &add_method(Cx &cx, Pos pos, Sym &id, const vector<Arg> &args = {});
    void bind(Pos pos, Sym &id, Val &val);
    void bind_type(Cx &cx, Pos pos, Type &type);
    Iter find(Sym &id);
    Val &get(Pos pos, Sym &id);
    Iter insert(Iter i, Sym &id, Val &val);
    void mark_items(Cx &cx);
  };
}

#endif
