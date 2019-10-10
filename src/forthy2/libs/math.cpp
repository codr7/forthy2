#include "forthy2/cx.hpp"
#include "forthy2/libs/math.hpp"

namespace forthy2 {
  static void int_add_imp(Cx &cx, Pos pos) {
    Val &y(cx.pop(pos)), &x(cx.pop(pos));
    
    cx.push(cx.int_type.get(cx,
                            dynamic_cast<Int &>(x).imp +
                            dynamic_cast<Int &>(y).imp));
  }

  static void fix_add_imp(Cx &cx, Pos pos) {
    auto
      &y(dynamic_cast<Fix &>(cx.pop(pos))),
      &x(dynamic_cast<Fix &>(cx.pop(pos)));
    
    const uint8_t xs(x.scale()), ys(y.scale());
    const int64_t yv(y.get());
      
    cx.push(cx.fix_type.get(cx,
                            x.get() +
                            ((xs == ys) ? yv : yv * Fix::pow(xs) / Fix::pow(ys)),
                            xs));
  }

  static void fix_div_imp(Cx &cx, Pos pos) {
    auto
      &y(dynamic_cast<Fix &>(cx.pop(pos))),
      &x(dynamic_cast<Fix &>(cx.pop(pos)));

    const uint8_t xs(x.scale());
    
    cx.push(cx.fix_type.get(cx, 
                            x.get() * Fix::pow(xs) / 
                            (y.get() * Fix::pow(xs) / Fix::pow(y.scale())), 
                            x.scale()));
  }

  static void fix_mul_imp(Cx &cx, Pos pos) {
    auto
      &y(dynamic_cast<Fix &>(cx.pop(pos))),
      &x(dynamic_cast<Fix &>(cx.pop(pos)));

    const uint8_t xs(x.scale());

    cx.push(cx.fix_type.get(cx, 
                            x.get() * y.get() / Fix::pow(y.scale()),
                            xs));
  }

  static void fix_sub_imp(Cx &cx, Pos pos) {
    auto
      &y(dynamic_cast<Fix &>(cx.pop(pos))),
      &x(dynamic_cast<Fix &>(cx.pop(pos)));
    
    const uint8_t xs(x.scale()), ys(y.scale());
    const int64_t yv(y.get());

    cx.push(cx.fix_type.get(cx, 
                            x.get() -
                            ((xs == ys) ? yv : yv * Fix::pow(xs) / Fix::pow(ys)), 
                            xs));
  }
  
  void init_math(Cx &cx, Pos pos, Env &env) {
    env.bind_type(cx, pos, cx.fix_type);

    env.add_method(cx, pos, cx.sym("+"),
                   {{cx.int_type}, {cx.int_type}},
                   {cx.int_type}).imp = int_add_imp;

    env.add_method(cx, pos, cx.sym("+"),
                   {{cx.fix_type}, {cx.fix_type}},
                   {cx.fix_type}).imp = fix_add_imp;

    env.add_method(cx, pos, cx.sym("/"),
                   {{cx.fix_type}, {cx.fix_type}},
                   {cx.fix_type}).imp = fix_div_imp;

    env.add_method(cx, pos, cx.sym("*"),
                   {{cx.fix_type}, {cx.fix_type}},
                   {cx.fix_type}).imp = fix_mul_imp;

    env.add_method(cx, pos, cx.sym("-"),
                   {{cx.fix_type}, {cx.fix_type}},
                   {cx.fix_type}).imp = fix_sub_imp;
  }
}
