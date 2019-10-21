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
      nil_type = new NilType(cx, cx.sym(id.name, '?'));
      cx.nil_type.derive(*nil_type);
      derive(*nil_type);
    }
  }

  Type::~Type() {}

  Cmp Type::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }

  void Type::derive(Type &parent) { derive(parent, parent); }

  void Type::derive(Type &parent, Type &root) {
    auto i(find_parent(parent));

    if (i == parents.end() || i->first != &parent) {
      weight += parent.weight;
      insert_parent(i, parent, root);
      for (auto &pp: parent.parents) { derive(*pp.first, root); }
    }
  }

  void Type::dump(ostream &out) { out << id.name; }

  Type::ParentIter Type::find_parent(Type &parent) {
    return lower_bound(parents.begin(), parents.end(), &parent,
                       [&](auto &x, auto &y) { return x.first < y; });
  }
  
  Type::ParentIter Type::insert_parent(ParentIter i, Type &parent, Type &root) {
    return parents.emplace(i, &parent, &root);
  }

  Type *Type::isa(Type &parent) {
    if (this == &parent) { return this; }
    
    if (auto i(find_parent(parent)); i != parents.end() && i->first == &parent) {
      return i->second;
    }
    
    return nullptr;
  }

  bool Type::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (auto &p: parents) { p.first->mark(cx); }
    return true;
  }

  Type &Type::or_() { return *nil_type; }

  void Type::sweep(Cx &cx) {
    Val::sweep(cx);
    delete this;
  }

  Type &Type::type(Cx &cx) { return cx.meta_type; }
}
