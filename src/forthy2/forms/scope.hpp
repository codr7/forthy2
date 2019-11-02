#ifndef FORTHY2_FORM_SCOPE_HPP
#define FORTHY2_FORM_SCOPE_HPP

#include "forthy2/form.hpp"
#include "forthy2/stack.hpp"

namespace forthy2 {
  struct ScopeForm: Form {
    Stack body;
    
    ScopeForm(Pos pos);
    Forms body_forms();
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    Node<Op> &compile_ref(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    bool splice(Cx &cx) override;
    Type &type(Cx &cx) override;
    void write(ostream &out) override;
  };

  using ScopeType = ValType<ScopeForm>;
}

#endif
