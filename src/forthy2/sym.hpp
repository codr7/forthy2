#ifndef FORTHY2_SYM_HPP
#define FORTHY2_SYM_HPP

#include <string>

#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Sym: Val {
    string name;

    bool operator ==(const Sym &) = delete;
    bool operator !=(const Sym &) = delete;
    
    Sym(string_view name);
    void print(Cx &cx, Pos pos, ostream &out) override;
    void dump(ostream &out) override;
    void sweep(Cx &cx) override;
    Form &to_form(Cx &cx, Pos pos) override;
    Type &type(Cx &cx) override;
  };
}

#endif
