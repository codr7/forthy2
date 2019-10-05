#ifndef FORTHY2_POS_HPP
#define FORTHY2_POS_HPP

namespace forthy2 {
  struct Sym;
  
  struct Pos {
    static const Pos _;
    
    const Sym *file;
    int row, col;

    Pos(const Sym *file, int row, int col): file(file), row(row), col(col) {}
  };
}

#endif
