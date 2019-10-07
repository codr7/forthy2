#ifndef FORTHY2_TYPE_FIX_HPP
#define FORTHY2_TYPE_FIX_HPP

#include "forthy2/fix.hpp"
#include "forthy2/prim_val.hpp"

namespace forthy2 {
  struct FixVal: PrimVal<Fix> {
    FixVal(Fix val);
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
