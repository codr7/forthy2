#include "forthy2/cx.hpp"
#include "forthy2/libs/time.hpp"

namespace forthy2 {
  static Node<Op> &secs_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).secs()));
    return *pc.next;
  }

  static Node<Op> &msecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).msecs()));
    return *pc.next;
  }

  static Node<Op> &usecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).usecs()));
    return *pc.next;
  }

  static Node<Op> &nsecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).nsecs()));
    return *pc.next;
  }

  static Node<Op> &add_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx,
                             dynamic_cast<Time &>(cx.pop()).imp +
                             dynamic_cast<Time &>(cx.pop()).imp));
    
    return *pc.next;
  }

  static Node<Op> &sub_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx,
                             dynamic_cast<Time &>(cx.pop()).imp -
                             dynamic_cast<Time &>(cx.pop()).imp));
    
    return *pc.next;
  }

  void init_time(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.time_type);

    scope.add_method(cx, pos, cx.sym("secs"), {{cx.time_type}}).imp = secs_imp;
    scope.add_method(cx, pos, cx.sym("msecs"), {{cx.time_type}}).imp = msecs_imp;
    scope.add_method(cx, pos, cx.sym("usecs"), {{cx.time_type}}).imp = usecs_imp;
    scope.add_method(cx, pos, cx.sym("nsecs"), {{cx.time_type}}).imp = nsecs_imp;

    scope.add_method(cx, pos, cx.sym("+"),
                     {{cx.time_type}, {cx.time_type}}).imp = add_imp;

    scope.add_method(cx, pos, cx.sym("-"),
                     {{cx.time_type}, {cx.time_type}}).imp = sub_imp;
  }
}
