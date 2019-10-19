#ifndef FORTHY2_MACRO_HPP
#define FORTHY2_MACRO_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/form.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;

  struct Macro: Val {
    using Imp = function<Node<Op> &(Cx &cx,
                                    Form &form,
                                    Forms &in,
                                    Node<Op> &out)>;

    Sym &id;
    Args args;
    Imp imp;

    Macro(Sym &id, const vector<Arg> &args);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Node<Op> &expand(Cx &cx, Form &form, Forms &in, Node<Op> &out);
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };
}

#endif
