#ifndef FORTHY2_FORM_STACK_HPP
#define FORTHY2_FORM_STACK_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct StackForm: Form {
    Forms body;
    
    StackForm(Pos pos, const Forms &body = {});
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    bool splice(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
