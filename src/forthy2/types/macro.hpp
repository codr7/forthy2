#ifndef FORTHY2_TYPE_MACRO_HPP
#define FORTHY2_TYPE_MACRO_HPP

#include "forthy2/arg.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/ret.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct MacroVal: TVal<Macro> {
    MacroVal(const Sym *id, const Args &args, const Rets &rets);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    void sweep(Cx &cx) override;
  };
}

#endif
