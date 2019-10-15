#include "forthy2/cx.hpp"
#include "forthy2/ops/clock.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  ClockOp::ClockOp(Form &form, Node<Op> &prev, Form &body):
    Op(form, prev), body(body), end_pc(nullptr) {}
  
  void ClockOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    body.deref(cx);
    cx.clock_op.put(*this);
  }

  void ClockOp::dump(ostream &out) { out << "clock " << body; }

  Node<Op> &ClockOp::eval(Cx &cx) {
    Int &reps(cx.pop(form.pos, cx.int_type));
    Timer t;

    for (Int::Imp i(0); i < reps.imp; i++) {
      cx.eval(*this, *end_pc->next);
    }
    
    cx.push(cx.int_type.get(cx, t.ns()));
    return *end_pc->next;
  }

  void ClockOp::mark_vals(Cx &cx) {
    Op::mark_vals(cx);
    body.mark_vals(cx);
  }
}
