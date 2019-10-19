#ifndef FORTHY2_TIME_HPP
#define FORTHY2_TIME_HPP

#include <chrono>

#include "forthy2/val.hpp"
#include "forthy2/pool_type.hpp"

namespace forthy2 {
  struct Cx;
  
  struct Time: Val {
    using Imp = chrono::steady_clock::duration;
    using Rep = typename Imp::rep;
    using Period = typename Imp::period;
    
    Imp imp;

    Time(Imp imp): imp(imp) {}

    operator bool() override { return imp.count(); }

    Cmp cmp(Val &other) override {
      return forthy2::cmp<Imp>(imp, dynamic_cast<Time &>(other).imp);
    }

    void dump(ostream &out) override;

    bool eq(Val &other) override { return dynamic_cast<Time &>(other).imp == imp; }

    Rep secs() { return chrono::duration_cast<chrono::seconds>(imp).count(); }
    Rep msecs() { return chrono::duration_cast<chrono::milliseconds>(imp).count(); }
    Rep usecs() { return chrono::duration_cast<chrono::microseconds>(imp).count(); }
    Rep nsecs() { return chrono::duration_cast<chrono::nanoseconds>(imp).count(); }
    
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };

  using TimeType = PoolType<Time>;
}

#endif
