#ifndef FORTHY2_OP_HPP
#define FORTHY2_OP_HPP

#include <iostream>

#include "forthy2/form.hpp"
#include "forthy2/node.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  
  struct Op: Node<Op> {
    Form &form;
    
    Op(Form &form, Node<Op> &prev);
    virtual ~Op();
    virtual void dealloc(Cx &cx);
    virtual void dump(ostream &out) = 0;
    virtual Node<Op> &eval(Cx &cx);
    virtual void mark_vals(Cx &cx);
  };

  ostream &operator <<(ostream &out, const Op &op);
}

#endif
