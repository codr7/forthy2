#ifndef FORTHY2_FORM_LIT_HPP
#define FORTHY2_FORM_LIT_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct LitForm: Form {
    Val &val;
    
    LitForm(Pos pos, Val &val);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
