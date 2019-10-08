#include "forthy2/cx.hpp"
#include "forthy2/type.hpp"

namespace forthy2 {
  Type::Type(Cx &cx, const Sym *id, vector<Type *> parents):
    id(id), weight(cx.type_weight++), val(*cx.type_pool.get(*this)) {
    cx.marked_vals.push(val);
    for (Type *p: parents) { derive(*p, *p); }
  }

  Type::~Type() {}

  void Type::derive(Type &parent) { derive(parent, parent); }

  void Type::derive(Type &parent, Type &root) {
    auto found(parents.find(&parent));

    if (found == parents.end()) {
      weight += parent.weight;
      parents[&parent] = &root;
      for(auto &pp: parent.parents) { derive(*pp.first, root); }
    }
  }

  Type *Type::is_a(Type &parent) {
    auto found(parents.find(&parent));
    if (found == parents.end()) { return nullptr; }
    return found->second;
  }
}
