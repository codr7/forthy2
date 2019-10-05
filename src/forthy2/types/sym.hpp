#ifndef FORTHY2_TYPE_SYM_HPP
#define FORTHY2_TYPE_SYM_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/prim_val.hpp"

namespace forthy2 {
  struct Sym;
  
  struct SymVal: PrimVal<const Sym *> {
    SymVal(const Sym *v): PrimVal<const Sym *>(v) {}
    Type &type() override;
  };

  struct SymType: PoolType<SymVal> {
    SymType(const string &id): PoolType(id) {}
  };

  extern SymType sym_type;
}

#endif
