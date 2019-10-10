#ifndef FORTHY2_SYM_HPP
#define FORTHY2_SYM_HPP

#include <string>

#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Sym: Val {
    string name;
    
    Sym(const string &name);
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    void sweep(Cx &cx) override;
  };

  ostream &operator <<(ostream &out, const Sym &sym);

  inline bool operator !=(const Sym &x, const Sym &y) {
    return &x != &y;
  }

  inline bool operator <(const Sym &x, const Sym &y) {
    return &x < &y;
  }
}

#endif
