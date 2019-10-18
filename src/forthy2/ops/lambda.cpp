#include "forthy2/cx.hpp"
#include "forthy2/ops/lambda.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  LambdaOp::LambdaOp(Form &form, Node<Op> &prev): Op(form, prev), end_pc(nullptr) {}
  
  void LambdaOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.lambda_op.put(*this);
  }

  void LambdaOp::dump(ostream &out) {
    out << "lambda " << form;
  }

  Node<Op> &LambdaOp::eval(Cx &cx) {
    cx.push(val ? *val : val.emplace(*this, *end_pc));
    return *end_pc->next;
  }
}
