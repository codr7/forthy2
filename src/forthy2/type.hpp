#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

#include <unordered_map>
#include <vector>

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  struct Sym;
  
  struct Type: Val {
    Sym &id;
    uint64_t weight;
    unordered_map<Type *, Type *> parents;
    
    Type(Cx &cx, Sym &id, vector<Type *> parents = {});
    virtual ~Type();
    Cmp cmp(Val &other) override;
    void derive(Type &parent);
    void derive(Type &parent, Type &root);
    void dump(ostream &out) override;
    bool is(Val &other) override;
    Type *isa(Type &parent);
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
