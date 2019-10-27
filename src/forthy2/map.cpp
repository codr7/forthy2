#include "forthy2/cx.hpp"
#include "forthy2/map.hpp"

namespace forthy2 {
  Map::Map(Val &in, Val &fn): in(in), fn(fn) {}

  void Map::dump(ostream &out) { out << "Map@" << this; }

  void Map::iter(Cx &cx, Pos pos, IterBody body) {
    in.iter(cx, pos, [&](Val &in_val) {
        cx.push(in_val);
        fn.call(cx, pos, cx.ops, true, true);
        body(cx.pop(pos));
        return true;
      });
  }

  bool Map::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    in.mark(cx);
    fn.mark(cx);
    return true;
  }

  void Map::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.map_type.pool.put(*this);
  }

  Type &Map::type(Cx &cx) { return cx.map_type; }
}
