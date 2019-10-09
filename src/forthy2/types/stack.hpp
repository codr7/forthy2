#ifndef FORTHY2_TYPE_STACK_HPP
#define FORTHY2_TYPE_STACK_HPP

#include "forthy2/stack.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct StackVal: TVal<Stack> {
    StackVal();
    StackVal(const Stack &src);

    template <typename T>
    StackVal(T beg, T end): TVal<Stack>(beg, end) {}

    Val &clone(Cx &cx) override;
    void dump(ostream &out) override;
    Cmp cmp(Val &other) override;
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
