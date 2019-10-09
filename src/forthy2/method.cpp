#include "forthy2/method.hpp"

namespace forthy2 {
  Method::Method(const Sym *id,
                 uint64_t weight,
                 const Args &args,
                 const Rets &rets):
    id(id), weight(weight), args(args), rets(rets) { }
}
