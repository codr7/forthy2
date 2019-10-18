#include "forthy2/cx.hpp"
#include "forthy2/forms/id.hpp"

namespace forthy2 {
  IdForm::IdForm(Pos pos, Sym &val): Form(pos), val(val) {}

  Node<Op> &IdForm::compile(Cx &cx, Forms &in, Node<Op> &out) {
    Val &v(cx.scope->get(pos, val));
    Type *vt(&v.type(cx));

    if (vt == &cx.macro_type) {
      if (!cte) { throw ESys(pos, "Runtime macro dispatch: ", val); }
      return dynamic_cast<Macro &>(v).expand(cx, *this, in, out);
    }
    
    Node<Op> *op(&out);

    if (vt == &cx.method_type || vt == &cx.method_set_type) {
      op = &cx.push_op.get(*this, *op, v);
      return cx.call_op.get(*this, *op, false);
    }

    return cx.push_op.get(*this, *op, v);
  }

  Node<Op> &IdForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Val &v(cx.scope->get(pos, val));
    return cx.push_op.get(*this, out, v);
  }

  void IdForm::dealloc(Cx &cx) { cx.id_form.put(*this); }

  void IdForm::dump(ostream &out) { out << val; }
}
