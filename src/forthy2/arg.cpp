#include <sstream>

#include "forthy2/cx.hpp"
#include "forthy2/arg.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  static void dump(const vector<Arg> &items, ostream &out) {
    out << '[';
    bool first(true);
      
    for (auto &a: items) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }

      if (a.val) {
        a.val->dump(out);
      } else {
        out << a.type->id;
      }
    }

    out << ']';
  }

  Sym &Args::get_id(Cx &cx, Sym &root, const vector<Arg> &items) {
    stringstream buf;
    buf << root;
    forthy2::dump(items, buf);
    return cx.sym(buf.str());
  }

  uint64_t Args::get_weight(Cx &cx, const vector<Arg> &items) {
    uint64_t weight(0);
    
    for (auto &a: items) {
      weight += a.val ? a.val->get_type(cx).weight + 1 : a.type->weight;
    }
    
    return weight;
  }

  Args::Args(const vector<Arg> &items): items(items) {}

  void Args::dump(ostream &out) { forthy2::dump(items, out); }

  int Args::len() { return items.size(); }

  void Args::mark_items(Cx &cx) {
    for (auto &a: items) {
      if (a.val) {
        a.val->mark(cx);
      } else {
        a.type->mark(cx);
      }
    }
  }
}
