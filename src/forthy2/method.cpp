#include "forthy2/cx.hpp"
#include "forthy2/method.hpp"

namespace forthy2 {
  Method::Method(MethodSet &set, Sym &id, const vector<Arg> &args, uint64_t weight):
    set(set), id(id), args(args), weight(weight) { }

  bool Method::applicable(Cx &cx) {
    Stack::Items &s(cx.stack->items);
    auto ss(s.size());
    if (ss < args.len()) { return false; }
    Val **sv = &s[ss-args.len()];

    for (Arg &a: args.items) {
      if (a.val) {
        if (!a.val->eq(**sv)) { return false; }
      } else if (!(*sv)->type(cx).isa(*a.type)) {
        return false;
      }
    }

    return true;
  }
  
  void Method::call(Cx &cx, Pos pos) {
    if (imp) {
      imp(cx, pos);
    } else {
    }
  }

  void Method::dump(ostream &out) { out << "Method@" << this; }

  bool Method::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    set.mark(cx);
    args.mark_items(cx);
    return true;
  }

  void Method::sweep(Cx &cx) {
    Val::sweep(cx);
    Node<Method>::unlink();
    set.len--;
    cx.method_type.pool.put(*this);
  } 

  Type &Method::type(Cx &cx) { return cx.method_type; }
}
