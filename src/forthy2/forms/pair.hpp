#ifndef FORTHY2_FORM_PAIR_HPP
#define FORTHY2_FORM_PAIR_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct PairForm: Form {
    Form &left, &right;
    
    PairForm(const Pos &pos, Form &left, Form &right);
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
    void mark_vals(Cx &cx) override;
  };
}

#endif
