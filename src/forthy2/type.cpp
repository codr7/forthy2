#include "forthy2/cx.hpp"
#include "forthy2/type.hpp"

namespace forthy2 {
  Type::Type(Cx &cx, const Sym *id): id(id), val(*cx.type_pool.get(*this)) {
    cx.marked_vals.push(val);
  }
}
