#include "forthy2/cx.hpp"
#include "forthy2/lambda.hpp"

namespace forthy2 {
  void Lambda::dump(ostream &out) { out << "Lambda@" << this; }

  void Lambda::sweep(Cx &cx) {
    Fn::sweep(cx);
    cx.lambda_type.pool.put(*this);
  }

  Type &Lambda::type(Cx &cx) { return cx.lambda_type; }
}
