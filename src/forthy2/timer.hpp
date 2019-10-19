#ifndef FORTHY2_TIMER_HPP
#define FORTHY2_TIMER_HPP

#include <cstdint>

#include "forthy2/time.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Timer {
    using Clock = chrono::steady_clock;
    Clock::time_point start = Clock::now();
    Time::Imp get() { return Clock::now() - start; }
  };
}

#endif
