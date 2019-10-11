#ifndef FORTHY2_POS_HPP
#define FORTHY2_POS_HPP

#include <iostream>

namespace forthy2 {
  using namespace std;
  
  struct Sym;
  
  struct Pos {
    static const Pos _;
    
    Sym *file;
    int row, col;

    Pos(Sym *file = nullptr, int row = 1, int col = 0):
      file(file), row(row), col(col) {}
  };

  ostream &operator <<(ostream &out, const Pos &p);
}

#endif
