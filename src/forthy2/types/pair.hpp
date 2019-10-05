#ifndef FORTHY2_TYPE_PAIR_HPP
#define FORTHY2_TYPE_PAIR_HPP

#include "forthy2/pool_type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct PairVal: Val {
    using V = pair<Val *, Val *>;
    V v;

    PairVal(const V &v): v(v) {}
    PairVal(Val *first, Val *second): v(first, second) {}

    Cmp cmp(Val &other) override {
      V &other_v(dynamic_cast<PairVal &>(other).v);
      Cmp first(v.first->cmp(*other_v.first));
      return (first == Cmp::Eq) ? v.second->cmp(*other_v.second) : first;
    }

    bool is(Val &other) override {
      V &other_v(dynamic_cast<PairVal &>(other).v);
      return other_v.first->is(*v.first) && other_v.second->is(*v.second);
    }

    Type &type() override;
  };

  struct PairType: PoolType<PairVal> {
    PairType(const string &id): PoolType(id) {}
  };

  extern PairType pair_type;
}

#endif
