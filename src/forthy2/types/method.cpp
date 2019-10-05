#include "forthy2/types/method.hpp"

namespace forthy2 {
  MethodType method_type("Method");

  Type &MethodVal::type() { return method_type; }
}
