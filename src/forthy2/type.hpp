#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

#include <string>

#include "forthy2/types/meta.hpp"

namespace forthy2 {
  using namespace std;

  struct Type {
    string id;
    MetaVal val;
    
    Type(const string &id): id(id), val(*this) {}
  };
}

#endif
