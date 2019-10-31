#ifndef FORTHY2_FORM_SPLICE_HPP
#define FORTHY2_FORM_SPLICE_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct SpliceForm: Form {
    SpliceForm(const Pos &pos);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    Form &quote(Cx &cx, Pos pos) override;
    void write(ostream &out) override;
  };
}

#endif
