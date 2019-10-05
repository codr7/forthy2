#include "forthy2/types/stack.hpp"

namespace forthy2 {
  StackType stack_type("Stack");

  Type &StackVal::type() { return stack_type; }
}
