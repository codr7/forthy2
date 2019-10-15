#include "forthy2/cx.hpp"
#include "forthy2/ops/stack.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  StackOp::StackOp(Form &form, Node<Op> &prev): Op(form, prev), end_pc(nullptr) {}
  
  void StackOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.stack_op.put(*this);
  }

  void StackOp::dump(ostream &out) {
    out << "stack " << dynamic_cast<StackForm &>(form).body;
  }

  Node<Op> &StackOp::eval(Cx &cx) {
    Stack &s(cx.stack_type.get(cx));
    cx.with_stack<void>(s, [&]() { cx.eval(*this, *end_pc->next); });
    cx.push(s);
    return *end_pc->next;
  }
}
