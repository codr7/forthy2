#include "forthy2/cx.hpp"
#include "forthy2/forms/nil.hpp"

namespace forthy2 {
  NilForm::NilForm(): Form(Pos::_) {}

  Node<Op> &NilForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    return cx.push_op.get(*this, out, cx._);
  }

  void NilForm::dealloc(Cx &cx) {}
  
  void NilForm::write(ostream &out) { out << '_'; }
}
