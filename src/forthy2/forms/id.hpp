#ifndef FORTHY2_FORM_ID_HPP
#define FORTHY2_FORM_ID_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct IdForm: Form {
    Sym &val;
    
    IdForm(Pos pos, Sym &val);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) override;
    Node<Op> &compile_ref(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    Form &quote(Cx &cx, Pos pos) override;
    Val &unquote(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
