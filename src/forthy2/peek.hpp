#ifndef FORTHY2_PEEK_HPP
#define FORTHY2_PEEK_HPP

#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  struct Peek: Val {
    bool alt_src;
    Int::Imp offs;
    
    Peek(bool alt_src, Int::Imp offs = 0): alt_src(alt_src), offs(offs) {}
    
    void dump(ostream &out) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  using PeekType = ValType<Peek>;
}

#endif
