#include "forthy2/types/pair.hpp"

namespace forthy2 {
  PairType pair_type("Pair");

  Type &PairVal::type() { return pair_type; }
}
