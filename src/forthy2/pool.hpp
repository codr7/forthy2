#ifndef FORTHY2_POOL_HPP
#define FORTHY2_POOL_HPP

#include <vector>

namespace forthy2 {  
  using namespace std;
  
  template <typename T>
  struct Pool {
    static const size_t MIN_SLOTS = 30;

    using Slot = typename aligned_storage<sizeof(T), alignof(T)>::type;

    size_t slab_size, slab_offs;
    vector<Slot *> slabs;
    vector<T *> free;
    
    Pool(): slab_size(MIN_SLOTS), slab_offs(0) {
      slabs.emplace_back(new Slot[slab_size]);
    }

    ~Pool() {
      for (Slot *i: slabs) { delete[] i; }        
    }
    
    template <typename...Args>
    T *get(Args &&...args) {
      return new (alloc()) T(forward<Args>(args)...);
    }

    T *alloc() {
      T *p(nullptr);
      
      if (free.empty()) {
        Slot *s(nullptr);
        
        if (slab_offs < slab_size) {
          s = slabs.back();
        } else {
          slab_size *= 2;
          s = new Slot[slab_size];
          slabs.push_back(s);
          slab_offs = 0;
        }
      
        p = reinterpret_cast<T *>(&s[slab_offs++]);
      } else {
        p = free.back();
        free.pop_back();
      }
      
      return p;
    }

    void put(T *item) {
      item->~T();
      free.push_back(item);
    }
  };
}

#endif
