#include "forthy2/cx.hpp"
#include "forthy2/forms/id.hpp"

namespace forthy2 {
  IdForm::IdForm(Pos pos, Sym &val): Form(pos), val(val) {}

  Node<Op> &IdForm::compile(Cx &cx, FormIter &in, FormIter end, Node<Op> &out) {
    Val &v(cx.env->get(pos, val));
    Type *vt(&v.type(cx));

    if (vt == &cx.macro_type) {
      return dynamic_cast<Macro &>(v).expand(cx, *this, in, end, out);
    }
    
    Node<Op> *op(&out);

    if (vt == &cx.method_type || vt == &cx.method_set_type) {
      op = &cx.push_op.get(*this, *op, v);
      return cx.call_op.get(*this, *op);
    }

    return cx.push_op.get(*this, *op, v);
  }

  void IdForm::dealloc(Cx &cx) { cx.id_form.put(*this); }

  void IdForm::dump(ostream &out) { out << val; }
}
