#ifndef FORTHY2_CALL_HPP
#define FORTHY2_CALL_HPP

#include "forthy2/node.hpp"
#include "forthy2/pos.hpp"

namespace forthy2 {
  struct Fn;
  
  struct Call {
    Call *prev;
    Pos pos;
    Fn &fn;
    Node<Op> &return_pc;
    
    Call(Call *prev, Pos pos, Fn &fn, Node<Op> &return_pc):
      prev(prev), pos(pos), fn(fn), return_pc(return_pc) {}
  };
}

#endif
