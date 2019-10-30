#include "forthy2/cx.hpp"
#include "forthy2/libs/time.hpp"

namespace forthy2 {
  void init_time(Cx &cx, Pos pos, Scope &scope) {
    using namespace time;
    
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
