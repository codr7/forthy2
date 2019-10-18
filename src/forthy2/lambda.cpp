#include <cassert>

#include "forthy2/cx.hpp"
#include "forthy2/lambda.hpp"

namespace forthy2 {
  Lambda::Lambda(Node<Op> &beg_pc, Node<Op> &end_pc): Fn(beg_pc, end_pc) {}

  void Lambda::dump(ostream &out) { out << "Lambda@" << this; }

  void Lambda::sweep(Cx &cx) { assert(false); }

  Type &Lambda::type(Cx &cx) { return cx.lambda_type; }
}
