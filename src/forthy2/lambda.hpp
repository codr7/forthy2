#ifndef FORTHY2_LAMBDA_HPP
#define FORTHY2_LAMBDA_HPP

#include "forthy2/fn.hpp"

namespace forthy2 {
  struct Lambda: Fn {
    Lambda(Node<Op> &beg_pc, Node<Op> &end_pc);
    void dump(ostream &out) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  using LambdaType = ValType<Lambda>;
}

#endif
