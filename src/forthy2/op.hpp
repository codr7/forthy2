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
    
    Op(Node<Op> &prev, const Pos &pos): pos(pos) { prev.append(*this); }
    virtual ~Op() {}
    
    virtual void dealloc(Cx &cx) = 0;
    virtual void dump(ostream &out) = 0;
    virtual Node<Op> *eval(Cx &cx) { return Node<Op>::next; }
    virtual void mark_vals(Cx &cx) {} 
  };
}

#endif
