#ifndef FORTHY2_FIX_HPP
#define FORTHY2_FIX_HPP

#include <cassert>
#include <iomanip>

#include "forthy2/cmp.hpp"
#include "forthy2/math.hpp"

namespace forthy2::fix {
  const uint8_t SCALE_BITS(3);
  const uint8_t SCALE_MAX((1 << SCALE_BITS));

  using T = uint64_t;
    
  constexpr T make(int64_t rep, uint8_t scale) {
    const bool is_neg(rep < 0);
    const uint64_t r(is_neg ? -rep : rep);
    return is_neg + (scale << 1) + (r << (SCALE_BITS + 1));
  }
  
  constexpr bool is_neg(T f) { return f << 63; }
  
  constexpr uint8_t scale(T f) { return (f >> 1) & ((1 << SCALE_BITS) - 1); }
  
  constexpr int64_t get(T f) {
    const uint64_t r(f >> (SCALE_BITS + 1));
    return is_neg(f) ? -r : r;
  }

  static const array<int64_t, SCALE_MAX> POW({
      1, 10, 100, 1000, 10000, 100000, 1000000, 10000000});

  constexpr int64_t pow(uint8_t scale) {    
    assert(scale < SCALE_MAX);
    return POW[scale];
  }

  constexpr int64_t trunc(T f, uint8_t ts = 0) {
    const uint8_t fs(scale(f));
    const uint8_t s((fs == ts) ? fs : fs - ts);
    const int64_t m(pow(s)), v(get(f) / m);
    return v * m;
  }
  
  constexpr int64_t frac(T f) { return get(f) - trunc(f); }
  
  inline int cmp(const Pos &pos, T x, T y) {
    const int64_t xv(get(x)), yv(get(y));
    const uint8_t xs(scale(x)), ys(scale(y));
    return forthy2::cmp(pos, xv, (xs == ys) ? yv : yv / pow(ys) * pow(xs));
  }

  constexpr void dump(T f, ostream &out) {
    const uint8_t s(scale(f));
    const int64_t v(trunc(f) / pow(s));
    const bool neg(is_neg(f));
    if (neg && !v) { out << '-'; }
    const int64_t ff(frac(f));
    out << v << '.' << setw(s) << setfill('0') << (neg ? -ff : ff);
  }
  
  constexpr T add(T x, T y) {
    const uint8_t xs(scale(x)), ys(scale(y));
    const int64_t yv(get(y));
    return make(get(x) + ((xs == ys) ? yv : yv * pow(xs) / pow(ys)), xs);
  }
  
  constexpr T sub(T x, T y) {
    const uint8_t xs(scale(x)), ys(scale(y));
    const int64_t yv(get(y));
    return make(get(x) - ((xs == ys) ? yv : yv * pow(xs) / pow(ys)), xs);
  }

  constexpr T mul(T x, T y) {
    const uint8_t xs(scale(x));
    return make(get(x) * get(y) / pow(scale(y)), xs);
  }

  constexpr T div(T x, T y) {
    const uint8_t xs(scale(x));
    return make(get(x) * pow(xs) / (get(y) * pow(xs) / pow(scale(y))), scale(x));
  }
}

namespace forthy2 { using Fix = fix::T; }

#endif
