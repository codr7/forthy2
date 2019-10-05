#ifndef FORTHY2_DEFER_HPP
#define FORTHY2_DEFER_HPP

namespace forthy2 {
  template <typename T>
  struct Defer {
    T body;
    Defer(T body) : body(body) {}
    ~Defer() { body(); }
  };

  template <typename T>
  Defer<T> defer(T body) { return Defer<T>(body); }
}

#endif
