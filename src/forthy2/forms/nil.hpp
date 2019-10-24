#ifndef FORTHY2_FORM_NIL_HPP
#define FORTHY2_FORM_NIL_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct NilForm: Form {
    NilForm();
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out, int quote) override;
    void dealloc(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
