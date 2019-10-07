#ifndef FORTHY2_TYPE_STACK_HPP
#define FORTHY2_TYPE_STACK_HPP

#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct StackVal: TVal<Stack> {
    StackVal() {}

    StackVal(const Stack &src): TVal<Stack>(src) {}

    template <typename T>
    StackVal(T beg, T end): TVal<Stack>(beg, end) {}

    Val &clone(Cx &cx) override;

    void dump(ostream &out) override {
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

    Cmp cmp(Val &other) override {
      Stack &other_val(dynamic_cast<StackVal &>(other).val);
        
      for (auto i(val.begin()), j(other_val.begin());
           i != val.end() && j != other_val.end();
           i++, j++) {
        Cmp res((*i)->cmp(**j));
        if (res != Cmp::Eq) { return res; }
      }

      return forthy2::cmp(val.len(), other_val.len());
    }

    Type &get_type(Cx &cx) override;

    bool is(Val &other) override {
      Stack &other_val(dynamic_cast<StackVal &>(other).val);
      if (val.len() != other_val.len()) { return false; }

      for (auto i(val.begin()), j(other_val.begin());
           i != val.end() && j != other_val.end();
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
