#ifndef FORTHY2_RET_HPP
#define FORTHY2_RET_HPP

#include <vector>

namespace forthy2 {
  using namespace std;

  struct Type;
  
  struct Ret {
    Type *type = nullptr;
    Ret(Type &type): type(&type) {}
  };
  
  using Rets = vector<Ret>;
}

#endif
