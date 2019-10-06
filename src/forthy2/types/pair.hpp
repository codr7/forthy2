#ifndef FORTHY2_TYPE_PAIR_HPP
#define FORTHY2_TYPE_PAIR_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  struct PairVal: TVal<pair<Val *, Val *>> {
    using V = pair<Val *, Val *>;

    PairVal(const V &v): TVal<V>(v) {}
    PairVal(Val *first, Val *second): TVal<V>(first, second) {}

    void dump(ostream &out) override {
      v.first->dump(out);
      out << ',';
      v.second->dump(out);
    }

    Cmp cmp(Val &other) override {
      V &other_v(dynamic_cast<PairVal &>(other).v);
      Cmp first(v.first->cmp(*other_v.first));
      return (first == Cmp::Eq) ? v.second->cmp(*other_v.second) : first;
    }

    Type &get_type(Cx &cx) override;

    bool is(Val &other) override {
      V &other_v(dynamic_cast<PairVal &>(other).v);
      return other_v.first->is(*v.first) && other_v.second->is(*v.second);
    }

    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
