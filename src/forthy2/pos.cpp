#include "forthy2/pos.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  const Pos Pos::_(nullptr, -1, -1);

  ostream &operator <<(ostream &out, const Pos &p) {
    if (p.file) { out << *p.file << '@'; }
    out << p.row << ':' << p.col;
    return out;
  }
}
