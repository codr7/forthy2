#include "forthy2/cx.hpp"
#include "forthy2/e.hpp"
#include "forthy2/macro.hpp"
#include "forthy2/sym.hpp"

namespace forthy2 {
  Macro::Macro(Sym &id, const vector<Arg> &args): id(id), args(args) {}

  Cmp Macro::cmp(Val &other) { return forthy2::cmp<Val *>(this, &other); }
  
  void Macro::dump(ostream &out) { out << "Macro@" << this; }

  Node<Op> &Macro::expand(Cx &cx, Form &form, Forms &in, Node<Op> &out, bool stash) {
    auto nargs(args.len());
    
    if (in.size() < nargs) {
      throw ESys(form.pos, "Missing macro args: ", id.name);
    }
    
    if (imp) { return imp(cx, form, in, out, stash); }
    Node<Op> *pc(&out);
    Stack stack;

    cx.with_stack<void>(stack, [&]() {
        auto i(in.end());

        transform(i - nargs, i, back_inserter(stack.items), [&](Form *f) -> Val * {
            return &f->unquote(cx);
          });

        in.erase(i - nargs, i);

        if (!args.applicable(cx)) {
          throw ESys(form.pos, "Macro not applicable: ", id.name, '\n', stack);
        }
        
        cx.eval(ops, ops);
        Val &v(cx.pop(form.pos));
        Type *vt(&v.type(cx));
        
        if (vt == &cx.macro_type) {
          transform(stack.begin(), stack.end(), back_inserter(in), [&](Val *fv) {
              auto *f(dynamic_cast<Form *>(&v));
              if (!f) { f = &cx.lit_form.get(form.pos, *fv); }
              if (!f) { throw ESys(form.pos, "Expected Form: ", *fv); }
              return f;
            });
          
          pc = &dynamic_cast<Macro &>(v).expand(cx, form, in, out, stash);
        } else if (vt == &cx.scope_type) {
          pc = &cx.compile(dynamic_cast<Form &>(v), *pc);
        } else if (vt == &cx.stack_type) {
          auto &s(dynamic_cast<Stack &>(v));
          Forms fs;

          transform(s.begin(), s.end(), back_inserter(fs), [&](Val *v) {
              return dynamic_cast<Form *>(v);
            });

          pc = &cx.compile(fs, *pc);
        } else {
          pc = &cx.push_op.get(form, *pc, v);
        }
      });

    return *pc;
  }

  bool Macro::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    args.mark_items(cx);
    return true;
  }

  void Macro::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.macro_type.pool.put(*this);
  }

  Type &Macro::type(Cx &cx) { return cx.macro_type; }
}
