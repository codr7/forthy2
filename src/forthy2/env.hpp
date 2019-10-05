#ifndef FORTHY2_ENV_HPP
#define FORTHY2_ENV_HPP

#include <algorithm>
#include <vector>

#include "forthy2/e.hpp"

namespace forthy2 {
  using namespace std;

  struct Pos;
  struct Sym;
  struct Val;
  
  struct Env {
    struct Item {
      Env *home;
      const Sym *id;
      Val *val;
      
      Item(Env *home, const Sym *id, Val *val = nullptr): home(home), val(val) {}
    };
      
    using Items = vector<Item>;
    using Iter = Items::iterator;
    
    Env *prev = nullptr;
    Items items;
    
    void bind(const Pos &pos, const Sym *id, Val *val) {
      Iter i(find(id));

      if (i == items.end() || i->id != id) {
        insert(i, id, val);
      } else {
        if (i->home == this) { throw ESys(pos, "Dup binding: ", id); }
        i->val = val;
      }      
    }

    Iter find(const Sym *id) {
      return lower_bound(items.begin(), items.end(), id,
                         [&](auto &x, auto &y) { return x.id < y; });
    }
    
    Val &get(const Pos &pos, const Sym *id) {
      auto i(find(id));
      if (i == items.end() || i->id != id) { throw ESys(pos, "Unknown id: ", id); }
      return *i->val;
    }
    
    Iter insert(Iter i, const Sym *id, Val *val) {
      return items.emplace(i, this, id, val);
    }
  };
}

#endif
