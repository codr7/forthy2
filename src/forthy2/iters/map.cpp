#include "forthy2/cx.hpp"
#include "forthy2/iters/map.hpp"

namespace forthy2 {
  Map::Map(Iter &in, Val &fn): in(in), fn(fn) {}

  void Map::dump(ostream &out) { out << "Map@" << this; }

  bool Map::mark(Cx &cx) {
    if (!Val::mark(cx)) { return false; }
    in.mark(cx);
    fn.mark(cx);
    return true;
  }

  Val *Map::get_next(Cx &cx, Pos pos) {
    Val *in_val(in.get_next(cx, pos));
    if (!in_val) { return nullptr; }
    cx.push(*in_val);
    fn.call(cx, pos, cx.ops, true, true);
    return &cx.pop(pos);
  }

  void Map::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.map_type.pool.put(*this);
  }

  Type &Map::type(Cx &cx) { return cx.map_type; }
}
