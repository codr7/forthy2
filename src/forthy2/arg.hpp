#ifndef FORTHY2_ARG_HPP
#define FORTHY2_ARG_HPP

#include <iostream>
#include <vector>

namespace forthy2 {
  using namespace std;

  struct Cx;
  struct Sym;
  struct Type;
  struct Val;
  
  struct Arg {
    Type *type = nullptr;
    Val *val = nullptr;

    Arg(Type &type): type(&type) {}
    Arg(Val *val): val(val) {}
  };

  struct Args {
    static Sym &get_id(Cx &cx, Sym &root, const vector<Arg> &args);
    static uint64_t get_weight(Cx &cx, const vector<Arg> &args);

    vector<Arg> items;
    
    Args(const vector<Arg> &items);
    bool applicable(Cx &cx);
    void dump(ostream &out);
    unsigned int len();
    void mark_items(Cx &cx);
  };
}

#endif
