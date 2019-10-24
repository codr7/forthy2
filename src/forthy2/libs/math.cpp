#include "forthy2/cx.hpp"
#include "forthy2/libs/math.hpp"

namespace forthy2 {
  static Node<Op> &int_add_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp +
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  static Node<Op> &int_div_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp /
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  static Node<Op> &int_mul_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp *
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }

  static Node<Op> &int_sub_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    Val &y(cx.pop()), &x(cx.pop());
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp -
                            dynamic_cast<Int &>(y).imp));

    return *return_pc.next;
  }
  
  static Node<Op> &fix_add_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale()), ys(y.scale());
    const int64_t yv(y.get());
      
    cx.push(cx.fix_type.get(cx,
                            x.get() +
                            ((xs == ys) ? yv : yv * Fix::pow(xs) / Fix::pow(ys)),
                            xs));

    return *return_pc.next;
  }

  static Node<Op> &fix_div_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale());
    
    cx.push(cx.fix_type.get(cx, 
                            x.get() * Fix::pow(xs) / 
                            (y.get() * Fix::pow(xs) / Fix::pow(y.scale())), 
                            x.scale()));

    return *return_pc.next;
  }

  static Node<Op> &fix_mul_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale());

    cx.push(cx.fix_type.get(cx, 
                            x.get() * y.get() / Fix::pow(y.scale()),
                            xs));

    return *return_pc.next;
  }

  static Node<Op> &fix_sub_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
    auto &y(dynamic_cast<Fix &>(cx.pop())), &x(dynamic_cast<Fix &>(cx.pop()));
    const uint8_t xs(x.scale()), ys(y.scale());
    const int64_t yv(y.get());

    cx.push(cx.fix_type.get(cx, 
                            x.get() -
                            ((xs == ys) ? yv : yv * Fix::pow(xs) / Fix::pow(ys)), 
                            xs));

    return *return_pc.next;
  }

  void init_math(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.fix_type);

    scope.add_method(cx, pos, cx.sym("+"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_add_imp;

    scope.add_method(cx, pos, cx.sym("/"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_div_imp;

    scope.add_method(cx, pos, cx.sym("*"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_mul_imp;

    scope.add_method(cx, pos, cx.sym("-"),
                     {{cx.int_type}, {cx.int_type}}).imp = int_sub_imp;

    scope.add_method(cx, pos, cx.sym("+"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_add_imp;

    scope.add_method(cx, pos, cx.sym("/"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_div_imp;

    scope.add_method(cx, pos, cx.sym("*"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_mul_imp;

    scope.add_method(cx, pos, cx.sym("-"),
                     {{cx.fix_type}, {cx.fix_type}}).imp = fix_sub_imp;
  }
}
