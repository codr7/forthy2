#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

#include <string>

namespace forthy2 {
  using namespace std;

  struct Type {
    string id;    
    Type(const string &id): id(id) {}
  };
}

#endif
