#include "forthy2/cx.hpp"
#include "forthy2/types/stack.hpp"

namespace forthy2 {
  StackVal::StackVal() {}

  StackVal::StackVal(const Stack &src): TVal<Stack>(src) {}

  Val &StackVal::clone(Cx &cx) { return cx.stack_val.get(cx, val); }

  void StackVal::dump(ostream &out) {
    out << '(';
    bool first(true);
      
    for (Val *v: val.items) {
      if (first) {
        first = false;
      } else {
        out << ' ';
      }
            
      v->dump(out);
    }

    out << ')';
  }

  Cmp StackVal::cmp(Val &other) {
    Stack &other_val(dynamic_cast<StackVal &>(other).val);
        
    for (auto i(val.begin()), j(other_val.begin());
         i != val.end() && j != other_val.end();
         i++, j++) {
      Cmp res((*i)->cmp(**j));
      if (res != Cmp::Eq) { return res; }
    }

    return forthy2::cmp(val.len(), other_val.len());
  }

  Type &StackVal::get_type(Cx &cx) { return cx.stack_val; }

  bool StackVal::is(Val &other) {
    Stack &other_val(dynamic_cast<StackVal &>(other).val);
    if (val.len() != other_val.len()) { return false; }

    for (auto i(val.begin()), j(other_val.begin());
         i != val.end() && j != other_val.end();
         i++, j++) {
      if (!(*i)->is(**j)) { return false; }
    }

    return true;
  }

  bool StackVal::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    for (Val *v: val.items) { v->mark(cx); }
    return true;
  }

  void StackVal::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_val.pool.put(this);
  }
}
