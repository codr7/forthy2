#include "forthy2/cx.hpp"
#include "forthy2/forms/id.hpp"

namespace forthy2 {
  IdForm::IdForm(Pos pos, Sym &val): Form(pos), val(val) {}

  Node<Op> &IdForm::compile(Cx &cx, Forms &in, Node<Op> &out, int quote) {
    bool stash(val.name.front() == '$');
    Sym &id(stash ? cx.sym(val.name.substr(1)) : val);
    if (quote > 0) { return cx.push_op.get(*this, out, id); }
    Val *v(&cx.scope->get(pos, id));
    Type *vt(&v->type(cx));
    Node<Op> *pc(&out);
        
    if (vt == &cx.macro_type) {
      return dynamic_cast<Macro *>(v)->expand(cx, *this, in, *pc, stash);
    }

    if (stash) { throw ESys(pos, "Invalid stash: ", val.name); }

    if (vt == &cx.peek_type) {
      Peek &pv(*dynamic_cast<Peek *>(v));
      return cx.peek_op.get(*this, *pc, pv.alt_src, pv.offs);
    }
    
    bool safe(true);

    if (vt == &cx.method_type || vt == &cx.method_set_type) {
      if (vt == &cx.method_set_type) {
        auto &ms(*dynamic_cast<MethodSet *>(v));

        if (!ms.nargs) {
          v = &ms.root.prev->get();
          safe = false;
        } else if (ms._len == 1) {
          v = &ms.root.next->get();
        }
      }
      
      return cx.call_op.get(*this, *pc, v, safe);
    }

    return cx.push_op.get(*this, *pc, *v);
  }

  Node<Op> &IdForm::compile_ref(Cx &cx, Forms &in, Node<Op> &out) {
    Val &v(cx.scope->get(pos, val));
    return cx.push_op.get(*this, out, v);
  }

  void IdForm::dealloc(Cx &cx) { cx.id_form.put(*this); }

  void IdForm::write(ostream &out) { out << val.name; }
}
