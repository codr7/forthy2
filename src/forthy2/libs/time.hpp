#ifndef FORTHY2_LIB_TIME_HPP
#define FORTHY2_LIB_TIME_HPP

#include "forthy2/cx.hpp"

namespace forthy2 {
  void init_time(Cx &cx, Pos pos, Scope &scope);

  namespace time {
    inline Node<Op> &int_hours_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::hours(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &int_mins_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::mins(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &int_secs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::secs(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &int_msecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::msecs(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &int_usecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::usecs(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &int_nsecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.time_type.get(cx, Time::nsecs(dynamic_cast<Int &>(cx.pop()).imp)));
      return *return_pc.next;
    }

    inline Node<Op> &hours_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).hours()));
      return *return_pc.next;
    }

    inline Node<Op> &mins_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).mins()));
      return *return_pc.next;
    }

    inline Node<Op> &secs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).secs()));
      return *return_pc.next;
    }

    inline Node<Op> &msecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).msecs()));
      return *return_pc.next;
    }

    inline Node<Op> &usecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).usecs()));
      return *return_pc.next;
    }

    inline Node<Op> &nsecs_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      cx.push(cx.int_type.get(cx, dynamic_cast<Time &>(cx.pop()).nsecs()));
      return *return_pc.next;
    }

    inline Node<Op> &add_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      Time::Imp &y(dynamic_cast<Time &>(cx.pop()).imp);
      cx.push(cx.time_type.get(cx, dynamic_cast<Time &>(cx.pop()).imp + y));
      return *return_pc.next;
    }

    inline Node<Op> &sub_imp(Cx &cx, Pos pos, Node<Op> &return_pc) {
      Time::Imp &y(dynamic_cast<Time &>(cx.pop()).imp);
      cx.push(cx.time_type.get(cx, dynamic_cast<Time &>(cx.pop()).imp - y));
      return *return_pc.next;
    }
  }
}

#endif
