#ifndef FORTHY2_ITER_HPP
#define FORTHY2_ITER_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Iter: Val {
    virtual void dump(ostream &out) override;
    virtual Iter &iter(Cx &cx, Pos pos) override;
    virtual Val *pop(Cx &cx, Pos pos) = 0;
    void print(Cx &cx, Pos pos, ostream &out) override;
    virtual void sweep(Cx &cx) override;
    virtual Type &type(Cx &cx) override;    
  };

  using IterType = ValType<Iter>;
}

#endif
