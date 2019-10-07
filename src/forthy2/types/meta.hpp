#ifndef FORTHY2_TYPE_META_HPP
#define FORTHY2_TYPE_META_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Type;
  
  struct MetaVal: TVal<Type &> {
    MetaVal(Type &v);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    bool is(Val &other) override;
    Type &get_type(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
