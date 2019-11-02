#include "forthy2/cx.hpp"
#include "forthy2/scope.hpp"
#include "forthy2/method_set.hpp"

namespace forthy2 {
  bool MethodSet::Order::operator() (Method *x, Method *y) const {
    return x->weight >= y->weight;
  }

  MethodSet &MethodSet::get(Cx &cx, Pos pos, Scope &scope, Sym &id, int nargs) {
    auto i(scope.find(id));
    
    if (i != scope.items.end() && i->id == &id) {
      auto &ms(*dynamic_cast<MethodSet *>(i->val));

      if (nargs != ms.nargs) {
        ESys(pos, "Argument count mismatch (", nargs, "): ", id);
      }
      
      return ms;
    }
    
    MethodSet &s(cx.method_set_type.get(cx, id, nargs));
    scope.insert(i, id, s);
    return s;
  }

  MethodSet::MethodSet(Sym &id, int nargs): id(id), nargs(nargs) {}
  
  Val &MethodSet::clone(Cx &cx) {
    auto &out(cx.method_set_type.get(cx, id, nargs));
    copy(items.begin(), items.end(), inserter(out.items, out.items.end()));
    return out;
  }

  void MethodSet::dump(ostream &out) { out << "MethodSet@" << this; }

  Val::Len MethodSet::len() { return items.size(); }

  bool MethodSet::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (Method *m: items) { m->mark(cx); }
    return true;
  }

  MethodSet::Iter MethodSet::push(Method &m) { return items.insert(&m).first; }

  void MethodSet::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.method_set_type.pool.put(*this);
  }

  Type &MethodSet::type(Cx &cx) { return cx.method_set_type; }
}
