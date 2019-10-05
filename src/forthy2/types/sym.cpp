#include "forthy2/types/sym.hpp"

namespace forthy2 {
  SymType sym_type("Sym");

  Type &SymVal::type() { return sym_type; }
}
