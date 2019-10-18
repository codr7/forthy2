#include "forthy2/cx.hpp"
#include "forthy2/method.hpp"

namespace forthy2 {
  Method::Method(MethodSet &set, Sym &id, const vector<Arg> &args, uint64_t weight):
    set(set), id(id), args(args), weight(weight) {}

  void Method::dump(ostream &out) { out << "Method@" << this; }

  bool Method::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    set.mark(cx);
    args.mark_items(cx);
    fn.mark(cx);
    return true;
  }

  void Method::sweep(Cx &cx) {
    Val::sweep(cx);
    Node<Method>::unlink();
    set.len--;
    fn.sweep(cx);
    cx.method_type.pool.put(*this);
  } 

  Type &Method::type(Cx &cx) { return cx.method_type; }
}
