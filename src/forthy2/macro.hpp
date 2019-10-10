#ifndef FORTHY2_MACRO_HPP
#define FORTHY2_MACRO_HPP

#include <functional>
#include <string>

#include "forthy2/arg.hpp"
#include "forthy2/form.hpp"
#include "forthy2/ret.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;

  struct Macro: Val {
    using Imp = function<Node<Op> &(Cx &cx,
                                    Form &form,
                                    FormIter &in,
                                    FormIter end,
                                    Node<Op> &out)>;

    Sym &id;
    Args args;
    Rets rets;
    Imp imp;

    Macro(Sym &id, const vector<Arg> &args, const vector<Ret> &rets);
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Node<Op> &expand(Cx &cx, Form &form, FormIter &in, FormIter end, Node<Op> &out);
    Type &get_type(Cx &cx) override;
    bool is(Val &other) override;
    bool mark(Cx &cx) override;
    void sweep(Cx &cx) override;
  };
}

#endif
