#include "forthy2/cx.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {

  Val &Stack::clone(Cx &cx) { return cx.stack_type.get(cx, *this); }

  Cmp Stack::cmp(Val &other) {
    Items &other_items(dynamic_cast<Stack &>(other).items);
        
    for (auto i(items.begin()), j(other_items.begin());
         i != items.end() && j != other_items.end();
         i++, j++) {
      Cmp res((*i)->cmp(**j));
      if (res != Cmp::Eq) { return res; }
    }

    return forthy2::cmp(items.size(), other_items.size());
  }

  void Stack::dump(ostream &out) {
    out << '(';
    dump_items(out);
    out << ')';
  }

  void Stack::dump_items(ostream &out) {
    bool first(true);
      
    for (Val *v: items) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }
            
      v->dump(out);
    }
  }

  bool Stack::eq(Val &other) {
    Items &other_items(dynamic_cast<Stack &>(other).items);
    if (items.size() != other_items.size()) { return false; }

    for (auto i(items.begin()), j(other_items.begin());
         i != items.end() && j != other_items.end();
         i++, j++) {
      if (!(*i)->eq(**j)) { return false; }
    }

    return true;
  }

  Iter &Stack::iter(Cx &cx, Pos pos) { return cx.stack_iter_type.get(cx, *this); }

  bool Stack::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    mark_items(cx);
    return true;
  }

  void Stack::mark_items(Cx &cx) {
    for (Val *v: items) { v->mark(cx); }
  }


  void Stack::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_type.pool.put(*this);
  }

  Type &Stack::type(Cx &cx) { return cx.stack_type; }
}
