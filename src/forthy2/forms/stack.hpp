#ifndef FORTHY2_FORM_STACK_HPP
#define FORTHY2_FORM_STACK_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct StackForm: Form {
    Forms body;
    
    StackForm(Pos pos);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    void mark_vals(Cx &cx) override;
  };
}

#endif
