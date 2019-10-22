#include "forthy2/cx.hpp"
#include "forthy2/forms/id.hpp"

namespace forthy2 {
  IdForm::IdForm(Pos pos, Sym &val): Form(pos), val(val) {}

  Node<Op> &IdForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {
    if (quote > 0) { return cx.push_op.get(*this, out, val); }
    Val *v(&cx.scope->get(pos, val));
    Type *vt(&v->type(cx));

    if (vt == &cx.macro_type) {
      return dynamic_cast<Macro *>(v)->expand(cx, *this, in, out);
    }
    
    Node<Op> *op(&out);
    bool safe(true);

    if (vt == &cx.method_type || vt == &cx.method_set_type) {
      if (vt == &cx.method_set_type) {
        auto &ms(*dynamic_cast<MethodSet *>(v));

        if (!ms.nargs) {
          v = &ms.root.prev->get();
          safe = false;
        } else if (ms.len == 1) {
          v = &ms.root.next->get();
        }
      }
      
      return cx.call_op.get(*this, *op, v, safe);
    }

    return cx.push_op.get(*this, *op, *v);
  }

  Node<Op> &IdForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Val &v(cx.scope->get(pos, val));
    return cx.push_op.get(*this, out, v);
  }

  void IdForm::dealloc(Cx &cx) { cx.id_form.put(*this); }

  void IdForm::write(ostream &out) { out << val.name; }
}
