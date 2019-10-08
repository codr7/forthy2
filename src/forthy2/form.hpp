#ifndef FORTHY2_FORM_HPP
#define FORTHY2_FORM_HPP

#include <iostream>
#include <vector>

#include "forthy2/pos.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  
  struct Form {
    Pos pos;
    int nrefs;
    
    Form(const Pos &pos);
    virtual ~Form();
    virtual void dealloc(Cx &cx) = 0;
    void deref(Cx &cx);
    virtual void dump(ostream &out) = 0;
    virtual void mark_vals(Cx &cx);
    Form &ref();
  };

  using Forms = vector<Form *>;
  using FormIter = Forms::iterator;
}

#endif
