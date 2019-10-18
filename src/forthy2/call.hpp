#ifndef FORTHY2_CALL_HPP
#define FORTHY2_CALL_HPP

#include "forthy2/node.hpp"
#include "forthy2/pos.hpp"

namespace forthy2 {
  struct Fn;
  
  struct Call {
    Call *prev;
    Op &pc;
    Fn &fn;
    Node<Op> &return_pc;
    
    Call(Call *prev, Op &pc, Fn &fn, Node<Op> &return_pc):
      prev(prev), pc(pc), fn(fn), return_pc(return_pc) {}
  };
}

#endif
