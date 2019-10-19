#include "forthy2/cx.hpp"
#include "forthy2/libs/time.hpp"

namespace forthy2 {
  static Node<Op> &int_hours_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::hours(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &int_mins_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::mins(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &int_secs_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::secs(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &int_msecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::msecs(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &int_usecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::usecs(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &int_nsecs_imp(Cx &cx, Op &pc) {
    cx.push(cx.time_type.get(cx, Time::nsecs(dynamic_cast<Int &>(cx.pop()).imp)));
    return *pc.next;
  }

  static Node<Op> &hours_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).hours()));
    return *pc.next;
  }

  static Node<Op> &mins_imp(Cx &cx, Op &pc) {
    cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).mins()));
    return *pc.next;
  }

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
    Time::Imp &y(dynamic_cast<Time &>(cx.pop()).imp);
    cx.push(cx.time_type.get(cx, dynamic_cast<Time &>(cx.pop()).imp + y));
    return *pc.next;
  }

  static Node<Op> &sub_imp(Cx &cx, Op &pc) {
    Time::Imp &y(dynamic_cast<Time &>(cx.pop()).imp);
    cx.push(cx.time_type.get(cx, dynamic_cast<Time &>(cx.pop()).imp - y));
    return *pc.next;
  }

  void init_time(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.time_type);

    scope.add_method(cx, pos, cx.sym("hours"), {{cx.int_type}}).imp = int_hours_imp;
    scope.add_method(cx, pos, cx.sym("mins"), {{cx.int_type}}).imp = int_mins_imp;
    scope.add_method(cx, pos, cx.sym("secs"), {{cx.int_type}}).imp = int_secs_imp;
    scope.add_method(cx, pos, cx.sym("msecs"), {{cx.int_type}}).imp = int_msecs_imp;
    scope.add_method(cx, pos, cx.sym("usecs"), {{cx.int_type}}).imp = int_usecs_imp;
    scope.add_method(cx, pos, cx.sym("nsecs"), {{cx.int_type}}).imp = int_nsecs_imp;

    scope.add_method(cx, pos, cx.sym("hours"), {{cx.time_type}}).imp = hours_imp;
    scope.add_method(cx, pos, cx.sym("mins"), {{cx.time_type}}).imp = mins_imp;
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
