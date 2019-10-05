#ifndef FORTHY2_CMP_HPP
#define FORTHY2_CMP_HPP

namespace forthy2 {
  enum struct Cmp {Lt = -1, Eq = 0, Gt = 1};

  template <typename T>
  Cmp cmp(T x, T y) {
    if (x < y) { return Cmp::Lt; }
    return (x == y) ? Cmp::Eq : Cmp::Gt;
  }
}

#endif
