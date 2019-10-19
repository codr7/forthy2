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

    static Imp hours(Int::Imp n) { return chrono::hours(n); }
    static Imp mins(Int::Imp n) { return chrono::minutes(n); }
    static Imp secs(Int::Imp n) { return chrono::seconds(n); }
    static Imp msecs(Int::Imp n) { return chrono::milliseconds(n); }
    static Imp usecs(Int::Imp n) { return chrono::microseconds(n); }
    static Imp nsecs(Int::Imp n) { return chrono::nanoseconds(n); }
    
    Imp imp;

    Time(Imp imp): imp(imp) {}

    operator bool() override { return imp.count(); }

    Cmp cmp(Val &other) override {
      return forthy2::cmp<Imp>(imp, dynamic_cast<Time &>(other).imp);
    }

    void dump(ostream &out) override;

    bool eq(Val &other) override { return dynamic_cast<Time &>(other).imp == imp; }

    Rep hours() { return chrono::duration_cast<chrono::hours>(imp).count(); }
    Rep mins() { return chrono::duration_cast<chrono::minutes>(imp).count(); }
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
