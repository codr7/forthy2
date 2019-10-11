#ifndef FORTHY2_FORM_HPP
#define FORTHY2_FORM_HPP

#include <iostream>
#include <vector>

#include "forthy2/node.hpp"
#include "forthy2/pos.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Form;
  struct Op;

  using Forms = vector<Form *>;
  using FormIter = Forms::iterator;

  struct Form {
    Pos pos;
    bool cte;
    int nrefs;
    
    Form(Pos pos);
    virtual ~Form();
    virtual Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) = 0;
    virtual void dealloc(Cx &cx) = 0;
    void deref(Cx &cx);
    virtual void dump(ostream &out) = 0;
    void eval(Cx &cx, Forms &in);
    virtual void mark_vals(Cx &cx);
    Form &ref();
  };

  ostream &operator <<(ostream &out, const Form &form);
  ostream &operator <<(ostream &out, const Forms &forms);
}

#endif
