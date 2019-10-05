#ifndef FORTHY2_TYPE_STACK_HPP
#define FORTHY2_TYPE_STACK_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/prim_val.hpp"
#include "forthy2/stack.hpp"

namespace forthy2 {
  struct StackVal: TVal<Stack> {
    StackVal() {}

    template <typename T>
    StackVal(T beg, T end): TVal<Stack>(beg, end) {}

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

    Type &type() override;
  };

  struct StackType: PoolType<StackVal> {
    StackType(const string &id): PoolType(id) {}
  };

  extern StackType stack_type;
}

#endif
