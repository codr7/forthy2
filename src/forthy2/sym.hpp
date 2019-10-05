#ifndef FORTHY2_SYM_HPP
#define FORTHY2_SYM_HPP

#include <string>

namespace forthy2 {
  using namespace std;
  
  struct Sym {
    string name;
    Sym(const string &name): name(name) {}
  };

  inline ostream &operator <<(ostream &out, const Sym *sym) {
    out << sym->name;
    return out;
  }
}

#endif
