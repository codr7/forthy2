#ifndef FORTHY2_LIB_MATH_HPP
#define FORTHY2_LIB_MATH_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_math(Cx &cx, Pos pos, Scope &scope);

  inline Node<Op> &int_add_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp +
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  inline Node<Op> &int_add_bang_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Int::Imp &y(cx.pop(cx.int_type).imp), &x(cx.peek(cx.int_type).imp), z(x+y);

    if (z < cx.ints.back()) {
      cx.poke(cx.int_type.get(cx, z));
    } else {
      x = z;
    }

    return *return_pc.next;
  }

  inline Node<Op> &int_div_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp /
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  inline Node<Op> &int_mul_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp *
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  inline Node<Op> &int_sub_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp -
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }
  
  inline Node<Op> &fix_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Int::Imp scale(cx.pop(cx.int_type).imp);
    cx.push(cx.fix_type.get(cx, cx.pop(cx.int_type).imp * Fix::pow(scale), scale));
    return *return_pc.next;
  }

  inline Node<Op> &fix_add_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Fix &y(cx.pop(cx.fix_type)), &x(cx.fix_type.get(cx, cx.pop(cx.fix_type)));
    x.add(y);
    cx.push(x);
    return *return_pc.next;
  }

  inline Node<Op> &fix_add_bang_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Fix &y(cx.pop(cx.fix_type)), &x(cx.peek(cx.fix_type));
    x.add(y);
    return *return_pc.next;
  }

  inline Node<Op> &fix_div_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale());
    
    cx.push(cx.fix_type.get(cx, 
                            x.get() * Fix::pow(xs) / 
                            (y.get() * Fix::pow(xs) / Fix::pow(y.scale())), 
                            x.scale()));

    return *return_pc.next;
  }

  inline Node<Op> &fix_mul_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale());

    cx.push(cx.fix_type.get(cx, 
                            x.get() * y.get() / Fix::pow(y.scale()),
                            xs));

    return *return_pc.next;
  }

  inline Node<Op> &fix_sub_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale()), ys(y.scale());
    const int64_t yv(y.get());

    cx.push(cx.fix_type.get(cx, 
                            x.get() -
                            ((xs == ys) ? yv : yv * Fix::pow(xs) / Fix::pow(ys)), 
                            xs));

    return *return_pc.next;
  } 
}

#endif
