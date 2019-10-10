#ifndef FORTHY2_FIX_HPP
#define FORTHY2_FIX_HPP

#include <array>
#include <cassert>
#include <iomanip>

#include "forthy2/util.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  struct Fix: Val {
    using Imp = uint64_t;

    static const uint8_t SCALE_BITS = 3;
    static const uint8_t SCALE_MAX = 1 << SCALE_BITS;
    
    static constexpr array<int64_t, SCALE_MAX> POW = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

    static Imp make(int64_t rep, uint8_t scale) {
      const bool negative(rep < 0);
      const uint64_t r(negative ? -rep : rep);
      return negative + (scale << 1) + (r << (SCALE_BITS + 1));
    }

    static int64_t pow(uint8_t scale) {    
      assert(scale < SCALE_MAX);
      return POW[scale];
    }

    Imp imp;
    
    Fix(int64_t rep, uint8_t scale): imp(make(rep, scale)) {}

    Cmp cmp(Val &other) override {
      auto &y(dynamic_cast<Fix &>(other));
      const int64_t xv(get()), yv(y.get());
      const uint8_t xs(scale()), ys(y.scale());
      return forthy2::cmp(xv, (xs == ys) ? yv : yv / pow(ys) * pow(xs));
    }

    void dump(ostream &out) override;

    int64_t frac() { return get() - trunc(); }

    int64_t get() {
      const uint64_t r(imp >> (SCALE_BITS + 1));
      return negative() ? -r : r;
    }

    bool is(Val &other) override { return dynamic_cast<Fix &>(other).imp == imp; }

    bool negative() { return imp << 63; }
  
    uint8_t scale() { return (imp >> 1) & ((1 << SCALE_BITS) - 1); }
  
    int64_t trunc(uint8_t to_s = 0) {
      const uint8_t from_s(scale());
      const uint8_t s((from_s == to_s) ? from_s : from_s - to_s);
      const int64_t m(pow(s)), v(get() / m);
      return v * m;
    }

    Type &type(Cx &cx) override;

    void sweep(Cx &cx) override;
  };  
}

#endif
