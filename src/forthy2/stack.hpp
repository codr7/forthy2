#ifndef FORTHY2_STACK_HPP
#define FORTHY2_STACK_HPP

#include <vector>

#include "forthy2/val.hpp"

namespace forthy2 {
  using namespace std;
  
  struct Cx;
  
  struct Stack: Val {
    using Items = vector<Val *>;
    using Iter = Items::iterator;
    
    Stack *prev = nullptr;
    Items items;

    Stack() {}
    Stack(const Stack &in): items(in.items) { }

    template <typename T>
    Stack(T beg, T end): items(beg, end) {}

    operator bool() override { return !items.empty(); }

    Iter beg() { return items.begin(); }
    Iter end() { return items.end(); }

    void clear() { items.clear(); }
    
    Val &clone(Cx &cx) override;
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    void dump_items(ostream &out);

    bool empty() { return items.empty(); }

    bool eq(Val &other) override;

    size_t len() { return items.size(); }

    bool mark(Cx &cx) override;
    void mark_items(Cx &cx);

    Val &peek(size_t offs) { return *items[items.size() - offs -1]; }

    Val &pop() {
      Val *v(items.back());
      items.pop_back();
      return *v;
    }

    void push(Val &v) { items.push_back(&v); }

    void swap() {
      size_t ss(items.size());
      std::swap(items[ss-1], items[ss-2]);
    }
    
    void sweep(Cx &cx) override;

    Val *try_pop(Cx &cx) { return items.empty() ? nullptr : &pop(); }

    Type &type(Cx &cx) override;
  };  
}

#endif
