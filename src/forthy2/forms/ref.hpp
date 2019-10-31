#ifndef FORTHY2_FORM_REF_HPP
#define FORTHY2_FORM_REF_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct RefForm: Form {
    Form *val;
    
    RefForm(const Pos &pos, Form &val);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    bool splice(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
