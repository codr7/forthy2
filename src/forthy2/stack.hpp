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

    Stack();
    Stack(const Stack &in);

    template <typename T>
    Stack(T beg, T end): items(beg, end) {}

    operator bool() override { return !items.empty(); }

    Iter beg();

    void clear() { items.clear(); }
    
    Val &clone(Cx &cx) override;
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    void dump_items(ostream &out);
    bool empty();
    Iter end();
    bool eq(Val &other) override;
    size_t len();
    bool mark(Cx &cx) override;
    void mark_items(Cx &cx);
    Val &peek(size_t offs = 0);
    Val &pop();
    void push(Val &v);

    void swap() {
      size_t ss(items.size());
      std::swap(items[ss-1], items[ss-2]);
    }
    
    void sweep(Cx &cx) override;
    Val &try_pop(Cx &cx);
    Type &type(Cx &cx) override;
  };  
}

#endif
