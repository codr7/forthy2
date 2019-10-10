#ifndef FORTHY2_FORM_DOT_HPP
#define FORTHY2_FORM_DOT_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct DotForm: Form {
    Form &y, &z;
    
    DotForm(Pos pos, Form &y, Form &z);
    Node<Op> &compile(Cx &cx, FormIter &in, FormIter end, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    void mark_vals(Cx &cx) override;
  };
}

#endif
