#ifndef FORTHY2_STACK_HPP
#define FORTHY2_STACK_HPP

#include <vector>

namespace forthy2 {
  using namespace std;
  
  struct Cx;
  struct Val;
  
  struct Stack {
    using Items = vector<Val *>;
    using Iter = Items::iterator;
    
    Stack *prev = nullptr;
    Items items;
    
    Stack() {}
    
    template <typename T>
    Stack(T beg, T end): items(beg, end) {}

    Iter begin() { return items.begin(); }

    Iter end() { return items.end(); }

    size_t len() { return items.size(); }

    void mark_items(Cx &cx);
    
    Val *&peek(size_t offs = 0) { return items[items.size() - offs -1]; }

    Val &pop() {
      Val *v(items.back());
      items.pop_back();
      return *v;
    }

    void push(Val &v) { items.push_back(&v); }
  };

  
}

#endif
