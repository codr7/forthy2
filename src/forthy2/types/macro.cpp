#include "forthy2/cx.hpp"
#include "forthy2/types/macro.hpp"

namespace forthy2 {
  MacroVal::MacroVal(const Sym *id, const Args &args, const Rets &rets):
    TVal<Macro>(id, args, rets) {}

  Cmp MacroVal::cmp(Val &other) {
    return forthy2::cmp(&val, &dynamic_cast<MacroVal &>(other).val);
  }

  void MacroVal::dump(ostream &out) { out << "Macro@" << this; }

  Type &MacroVal::get_type(Cx &cx) { return cx.macro_val; }

  bool MacroVal::is(Val &other) {
    return &val == &dynamic_cast<MacroVal &>(other).val;
  }

  void MacroVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.macro_val.pool.put(this);
  }
}
