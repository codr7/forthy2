#include "forthy2/libs/iter.hpp"

namespace forthy2 {
  void init_iter(Cx &cx, Pos pos, Scope &scope) {
    scope.bind_type(cx, pos, cx.filter_type);
    scope.bind_type(cx, pos, cx.map_type);
    scope.bind_type(cx, pos, cx.zip_type);

    scope.add_method(cx, pos, cx.sym("filter"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = filter_imp;

    scope.add_method(cx, pos, cx.sym("iter"), {{cx.a_type.or_()}}).imp = iter_imp;

    scope.add_method(cx, pos, cx.sym("map"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = map_imp;

    scope.add_method(cx, pos, cx.sym("zip"),
                     {{cx.a_type.or_()}, {cx.a_type.or_()}}).imp = zip_imp;

    scope.add_method(cx, pos, cx.sym("unzip"), {{cx.a_type.or_()}}).imp = unzip_imp;
  }
}
