#include "forthy2/cx.hpp"
#include "forthy2/type.hpp"

namespace forthy2 {
  Type::Type(Cx &cx, Sym &id, vector<Type *> parents):
    id(id), weight(cx.type_weight++) {
    cx.marked.push(*this);
    for (Type *p: parents) { derive(*p, *p); }

    if (id.name == "Nil" || id.name.back() == '?') {
      nil_type = this;
    } else {
      nil_type = new NilType(cx, cx.sym(id, '?'));
      cx.nil_type.derive(*nil_type);
      derive(*nil_type);
    }
  }

  Type::~Type() {}

  Cmp Type::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

  void Type::derive(Type &parent) { derive(parent, parent); }

  void Type::derive(Type &parent, Type &root) {
    auto found(parents.find(&parent));

    if (found == parents.end()) {
      weight += parent.weight;
      parents[&parent] = &root;
      for (auto &pp: parent.parents) { derive(*pp.first, root); }
    }
  }

  void Type::dump(ostream &out) { out << id; }

  bool Type::is(Val &other) { return this == &other; }

  Type *Type::isa(Type &parent) {
    if (this == &parent) { return this; }
    
    if (auto found(parents.find(&parent)); found != parents.end()) {
      return found->second;
    }
    
    return nullptr;
  }

  bool Type::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (auto &p: parents) { p.first->mark(cx); }
    return true;
  }

  NilType &Type::or_nil() { return *dynamic_cast<NilType *>(nil_type); }

  void Type::sweep(Cx &cx) {
    Val::sweep(cx);
    delete this;
  }

  Type &Type::type(Cx &cx) { return cx.meta_type; }
}
