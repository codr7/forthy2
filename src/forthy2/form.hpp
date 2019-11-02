#ifndef FORTHY2_FORM_HPP
#define FORTHY2_FORM_HPP

#include <iostream>
#include <vector>

#include "forthy2/pos.hpp"
#include "forthy2/val.hpp"
#include "forthy2/val_type.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Form;
  struct Op;
  struct Stack;
  
  using Forms = vector<Form *>;
  using FormIter = Forms::iterator;

  struct Form: Val {
    static bool splice_arg(Cx &cx, Pos pos, Form *&f);

    Pos pos;
    int nrefs;
    
    Form(Pos pos);
    virtual ~Form();
    virtual Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out) = 0;
    virtual Node<Op> &compile_ref(Cx &cx, Forms &in, Node<Op> &out);
    virtual void dealloc(Cx &cx) = 0;
    void deref(Cx &cx);
    void dump(ostream &out) override;
    void eval(Cx &cx);

    bool mark(Cx &cx) override {
      if (!Val::mark(cx)) { return false; }
      mark_vals(cx);
      return true;
    }
    
    virtual void mark_vals(Cx &cx);

    void print(Cx &cx, Pos pos, ostream &out) override { write(out); }
    
    virtual Form &quote(Cx &cx, Pos pos);    
    Form &ref();
    
    virtual bool splice(Cx &cx) { return false; }

    void sweep(Cx &cx) override { deref(cx); }

    virtual Type &type(Cx &cx) override;
    virtual Val &unquote(Cx &cx);
    virtual void write(ostream &out) = 0;
  };

  using FormType = ValType<Form>;

  ostream &operator <<(ostream &out, const Form &form);
  ostream &operator <<(ostream &out, const Forms &forms);
}

#endif
