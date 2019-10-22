#ifndef FORTHY2_FORM_DOT_HPP
#define FORTHY2_FORM_DOT_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct DotForm: Form {
    Form *x, *y, &z;
    
    DotForm(Pos pos, Form *x, Form *y, Form &z);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out, int quote) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
