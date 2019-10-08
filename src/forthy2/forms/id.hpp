#ifndef FORTHY2_FORM_ID_HPP
#define FORTHY2_FORM_ID_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct IdForm: Form {
    const Sym *val;
    
    IdForm(const Pos &pos, const Sym *val);
    Node<Op> &compile(Cx &cx, FormIter &in, FormIter end, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void dump(ostream &out) override;
  };
}

#endif
