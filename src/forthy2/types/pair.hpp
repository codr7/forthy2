#ifndef FORTHY2_TYPE_PAIR_HPP
#define FORTHY2_TYPE_PAIR_HPP

#include "forthy2/val.hpp"

namespace forthy2 {
  struct PairVal: TVal<pair<Val *, Val *>> {
    using P = pair<Val *, Val *>;

    PairVal(const P &v): TVal<P>(v) {}
    PairVal(Val &first, Val &second): TVal<P>(&first, &second) {}

    void dump(ostream &out) override {
      val.first->dump(out);
      out << ',';
      val.second->dump(out);
    }

    Cmp cmp(Val &other) override {
      P &other_val(dynamic_cast<PairVal &>(other).val);
      Cmp first(val.first->cmp(*other_val.first));
      return (first == Cmp::Eq) ? val.second->cmp(*other_val.second) : first;
    }

    Type &get_type(Cx &cx) override;

    bool is(Val &other) override {
      P &other_val(dynamic_cast<PairVal &>(other).val);
      return other_val.first->is(*val.first) && other_val.second->is(*val.second);
    }

    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
