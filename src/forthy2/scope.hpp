#ifndef FORTHY2_SCOPE_HPP
#define FORTHY2_SCOPE_HPP

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
  
  struct Scope {
    struct Item {
      Scope *home;
      Sym *id;
      Val *val;
      
      Item(Scope *home, Sym &id, Val &val);
    };
      
    using Items = vector<Item>;
    using Iter = Items::iterator;
    
    Scope *prev = nullptr;
    Items items;

    Scope();
    Scope(Cx &cx, Scope &in);
    
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
