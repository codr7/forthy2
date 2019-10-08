#include "forthy2/macro.hpp"

namespace forthy2 {
  Macro::Macro(const Sym *id, const Args &args, const Rets &rets):
    id(id), args(args), rets(rets) {}
}
