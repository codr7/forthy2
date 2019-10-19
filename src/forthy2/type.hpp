#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

#include <vector>

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  struct Sym;
  
  struct Type: Val {
    using Parents = vector<pair<Type *, Type *>>;
    using ParentIter = typename Parents::iterator;

    Sym &id;
    uint64_t weight;
    Parents parents;
    Type *nil_type = nullptr;
    
    Type(Cx &cx, Sym &id, vector<Type *> parents = {});
    virtual ~Type();
    Cmp cmp(Val &other) override;
    void derive(Type &parent);
    void derive(Type &parent, Type &root);
    void dump(ostream &out) override;
    ParentIter find_parent(Type &parent);
    ParentIter insert_parent(ParentIter i, Type &parent, Type &root);
    Type *isa(Type &parent);
    bool mark(Cx &cx) override;
    Type &or_();
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  inline bool operator==(Type &x, Type &y) { return &x == &y; }
}

#endif
