#ifndef FORTHY2_UTIL_HPP
#define FORTHY2_UTIL_HPP

#include <string>
#include <sstream>

namespace forthy2 {
  using namespace std;
  
  inline void append(ostream &s) {}

  template <typename A0, typename...Args>
  void append(ostream &s, const A0 &a0, const Args &...args) {
    s << a0;
    append(s, args...);
  }

  template <typename...Args>
  string str(const Args &...args) {
    stringstream out;
    append(out, args...);
    return out.str();
  }

  constexpr int64_t pow(int64_t b, uint64_t e) {
    int64_t r(1);

    for (;;) {
      if (e & 1) { r *= b; }
      e >>= 1;
      if (!e) { break; }
      b *= b;
    }

    return r;
  }

  constexpr uint64_t sqrt(uint64_t n) {
    uint64_t s(2), ns(n >> s);
    
    while (ns && ns != n) {
      s += 2;
      ns = n >> s;
    }
    
    s -= 2;
    uint64_t r(0);
    
    for (;;) {
      r <<= 1;
      uint64_t cr(r + 1);
      if (cr * cr <= n >> s) { r = cr; }
      if (!s) { break; }
      s -= 2;
    }
    
    return r;
  }
}

#endif
