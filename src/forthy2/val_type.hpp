#ifndef FORTHY2_VAL_TYPE_HPP
#define FORTHY2_VAL_TYPE_HPP

#include "forthy2/type.hpp"

namespace forthy2 {
  template <typename T>
  struct ValType: Type {
    ValType(Cx &cx, Sym &id, vector<Type *> parents = {}): Type(cx, id, parents) {}
  };
}

#endif
