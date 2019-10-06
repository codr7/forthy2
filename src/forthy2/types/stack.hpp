#ifndef FORTHY2_TYPE_STACK_HPP
#define FORTHY2_TYPE_STACK_HPP

#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct StackVal: TVal<Stack> {
    StackVal() {}

    template <typename T>
    StackVal(T beg, T end): TVal<Stack>(beg, end) {}

    void dump(ostream &out) override {
      out << '(';
      bool first(true);
      
      for (Val *v: v.items) {
        if (first) {
          first = false;
        } else {
          out << ' ';
        }
            
        v->dump(out);
      }

      out << ')';
    }

    Cmp cmp(Val &other) override {
      Stack &other_v(dynamic_cast<StackVal &>(other).v);
        
      for (auto i(v.begin()), j(other_v.begin());
           i != v.end() && j != other_v.end();
           i++, j++) {
        Cmp res((*i)->cmp(**j));
        if (res != Cmp::Eq) { return res; }
      }

      return forthy2::cmp(v.len(), other_v.len());
    }

    Type &get_type(Cx &cx) override;

    bool is(Val &other) override {
      Stack &other_v(dynamic_cast<StackVal &>(other).v);
      if (v.len() != other_v.len()) { return false; }

      for (auto i(v.begin()), j(other_v.begin());
           i != v.end() && j != other_v.end();
           i++, j++) {
        if (!(*i)->is(**j)) { return false; }
      }

      return true;
    }

    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
