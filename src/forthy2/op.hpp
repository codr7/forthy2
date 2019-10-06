#ifndef FORTHY2_OP_HPP
#define FORTHY2_OP_HPP

#include <iostream>

#include "forthy2/node.hpp"
#include "forthy2/pos.hpp"

namespace forthy2 {
  using namespace std;

  struct Cx;
  
  struct Op: Node<Op> {
    Pos pos;
    
    Op(const Pos &pos): pos(pos) {}

    virtual void dump(ostream &out) = 0;
    virtual Node<Op> *eval(Cx &cx) { return Node<Op>::next; }
  };
}

#endif
