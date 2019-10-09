#include "forthy2/arg.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  void dump(Args &args, ostream &out) {
    out << '[';
    bool first(true);
      
    for (Arg &a: args) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }

      if (a.val) {
        a.val->dump(out);
      } else {
        out << a.type->id->name;
      }
    }

    out << ']';
  }
}
