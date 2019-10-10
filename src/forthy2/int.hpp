#ifndef FORTHY2_INT_HPP
#define FORTHY2_INT_HPP

#include <cstdint>
#include <iostream>

#include "forthy2/val.hpp"

namespace forthy2 {
  struct Cx;
  
  struct Int: Val {
    using Imp = int64_t;
    Imp imp;

    Int(Imp imp);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
