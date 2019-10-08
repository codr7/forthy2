#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

#include <unordered_map>
#include <vector>

namespace forthy2 {
  struct Cx;
  struct MetaVal;
  struct Sym;
  
  struct Type {
    using Weight = uint64_t;
    
    const Sym *id;
    Weight weight;
    unordered_map<Type *, Type *> parents;
    MetaVal &val;
    
    Type(Cx &cx, const Sym *id, vector<Type *> parents = {});
    virtual ~Type();
    void derive(Type &parent);
    void derive(Type &parent, Type &root);
    Type *is_a(Type &parent);
  };
}

#endif
