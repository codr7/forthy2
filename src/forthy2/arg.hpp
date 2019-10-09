#ifndef FORTHY2_ARG_HPP
#define FORTHY2_ARG_HPP

#include <iostream>
#include <vector>

namespace forthy2 {
  using namespace std;

  struct Type;
  struct Val;
  
  struct Arg {
    Type *type = nullptr;
    Val *val = nullptr;

    Arg(Type &type): type(&type) {}
    Arg(Val *val): val(val) {}
  };
  
  using Args = vector<Arg>;

  void dump(Args &args, ostream &out);
  uint64_t get_weight(Args &args);
}

#endif
