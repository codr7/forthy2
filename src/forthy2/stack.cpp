#include "forthy2/cx.hpp"
#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Stack::Stack() {}

  Stack::Stack(const Stack &in): items(in.items) { }

  Stack::Iter Stack::beg() { return items.begin(); }

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

  bool Stack::empty() { return items.empty(); }
  
  Stack::Iter Stack::end() { return items.end(); }

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

  size_t Stack::len() { return items.size(); }

  bool Stack::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    mark_items(cx);
    return true;
  }

  void Stack::mark_items(Cx &cx) {
    for (Val *v: items) { v->mark(cx); }
  }

  Val &Stack::peek(size_t offs) { return *items[items.size() - offs -1]; }

  Val &Stack::pop() {
    Val *v(items.back());
    items.pop_back();
    return *v;
  }

  void Stack::push(Val &v) { items.push_back(&v); }

  void Stack::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.stack_type.pool.put(*this);
  }

  Val &Stack::try_pop(Cx &cx) {
    if (items.empty()) { return cx._; }
    return pop();
  }

  Type &Stack::type(Cx &cx) { return cx.stack_type; }
}
