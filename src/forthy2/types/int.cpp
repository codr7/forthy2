#include "forthy2/types/int.hpp"

namespace forthy2 {
  IntType int_type("Int");

  Type &IntVal::type() { return int_type; }
}
