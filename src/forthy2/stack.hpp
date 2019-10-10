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

    Iter begin();
    Val &clone(Cx &cx) override;
    Cmp cmp(Val &other) override;
    void dump(ostream &out) override;
    Iter end();
    bool is(Val &other) override;
    size_t len();
    bool mark(Cx &cx) override;
    void mark_items(Cx &cx);
    Val *&peek(size_t offs = 0);
    Val &pop();
    void push(Val &v);
    void sweep(Cx &cx) override;
    Type &type(Cx &cx) override;
  };  
}

#endif
