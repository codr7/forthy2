#include "forthy2/cx.hpp"
#include "forthy2/ops/check.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  CheckOp::CheckOp(Form &form, Node<Op> &prev, Node<Op> &body_pc):
    Op(form, prev), body_pc(body_pc) {}
  
  void CheckOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.check_op.put(*this);
  }

  void CheckOp::dump(ostream &out) { out << "check " << body_pc.next->get().form; }

  Node<Op> &CheckOp::eval(Cx &cx) {
    Val &v(cx.pop(form.pos));
      
    if (!v) {
      Forms fs;
      
      for (Node<Op> *op(body_pc.next); op != this; op = op->next) {
        Form &f(op->get().form);
        if (fs.empty() || &f != fs.back()) { fs.push_back(&f); }
      }

      throw ESys(form.pos, "Test failed: ", fs);
    }
    
    return *Node<Op>::next;
  }
}
