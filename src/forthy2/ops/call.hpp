#ifndef FORTHY2_OP_CALL_HPP
#define FORTHY2_OP_CALL_HPP

#include "forthy2/op.hpp"

namespace forthy2 {
  struct CallOp: Op {
    Val *val;
    bool safe;
    
    CallOp(Form &form, Node<Op> &prev, Val *val, bool safe);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    Node<Op> &eval(Cx &cx) override;
    void mark_vals(Cx &cx) override;
  };
}

#endif
