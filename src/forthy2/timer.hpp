#ifndef FORTHY2_TIMER_HPP
#define FORTHY2_TIMER_HPP

#include <chrono>
#include <cstdint>

namespace forthy2 {
  using namespace std;
  
  struct Timer {
    using Clock = chrono::steady_clock;
    Clock::time_point start = Clock::now();

    uint64_t ms() {
      return chrono::duration<double, milli>(Clock::now() - start).count();
    }

    uint64_t ns() {
      return chrono::duration<double, nano>(Clock::now() - start).count();
    }
  };
}

#endif
