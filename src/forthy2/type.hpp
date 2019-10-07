#ifndef FORTHY2_TYPE_HPP
#define FORTHY2_TYPE_HPP

namespace forthy2 {
  struct Cx;
  struct MetaVal;
  struct Sym;
  
  struct Type {
    const Sym *id;
    MetaVal &val;
    
    Type(Cx &cx, const Sym *id);
    virtual ~Type() {}
  };
}

#endif
