#include "forthy2/cx.hpp"
#include "forthy2/scope.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Scope::Scope() {}
  
  Scope::Scope(Cx &cx, Scope &in) {
    transform(in.items.begin(),
              in.items.end(),
              back_inserter(items), [&](auto &i) {
                return Item(i.home, *i.id, i.val->clone(cx));
              });
  }
  
  Macro &Scope::add_macro(Cx &cx, Pos pos, Sym &id, const vector<Arg> &args) {
    Macro &m(cx.macro_type.get(cx, id, args));
    bind(pos, id, m);
    return m;
  }

  Method &Scope::add_method(Cx &cx, Pos pos, Sym &id, const vector<Arg> &args) {
    MethodSet &s(MethodSet::get(cx, pos, *this, id, args.size()));

    Method &m(cx.method_type.get(cx,
                                 s,
                                 Args::get_id(cx, id, args),
                                 args,
                                 Args::get_weight(cx, args)));
    
    bind(pos, m.id, m);
    s.push(m);
    return m;
  }

  void Scope::bind(Pos pos, Sym &id, Val &val) {
    Iter i(find(id));
    
    if (i == items.end() || i->id != &id) {
      insert(i, id, val);
    } else {
      if (i->home == this) { throw ESys(pos, "Dup item: ", id); }
      i->val = &val;
    }      
  }

  void Scope::bind_type(Cx &cx, Pos pos, Type &type) {
    bind(pos, type.id, type);
    if (type.nil_type != &type) { bind_type(cx, pos, type.or_()); }
  }

  Scope::Iter Scope::find(Sym &id) {
    return lower_bound(items.begin(), items.end(), &id,
                       [&](auto &x, auto &y) { return x.id < y; });
  }
    
  Val &Scope::get(Pos pos, Sym &id) {
    auto i(find(id));
    if (i == items.end() || i->id != &id) { throw ESys(pos, "Unknown id: ", id); }
    return *i->val;
  }
    
  Scope::Iter Scope::insert(Iter i, Sym &id, Val &val) {
    return items.emplace(i, this, id, val);
  }
  
  void Scope::mark_items(Cx &cx) {
    for (Item i: items) { i.val->mark(cx); }
  }

  Scope::Item::Item(Scope *home, Sym &id, Val &val):
    home(home), id(&id), val(&val) {}
}
