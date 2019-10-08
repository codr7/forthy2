#include "forthy2/form.hpp"

namespace forthy2 {
  Form::Form(const Pos &pos): pos(pos), cte(false), nrefs(1) { }

  Form::~Form() {}
    
  void Form::deref(Cx &cx) {
    if (!--nrefs) { dealloc(cx); }
  }
    
  void Form::mark_vals(Cx &cx) {}

  Form &Form::ref() {
    nrefs++;
    return *this;
  }
}
