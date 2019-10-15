#ifndef FORTHY2_OP_CLOCK_HPP
#define FORTHY2_OP_CLOCK_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct Val;
  
  struct ClockOp: Op {
    Form &body;
    Node<Op> *end_pc;

    ClockOp(Form &form, Node<Op> &prev, Form &body);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
    void mark_vals(Cx &cx) override; 
  };
}

#endif
