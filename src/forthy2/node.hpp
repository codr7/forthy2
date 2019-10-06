#ifndef FORTHY2_NODE_HPP
#define FORTHY2_NODE_HPP

namespace forthy2 {  
  template <typename T, typename TagT = T>
  struct Node {
    Node<T, TagT> *prev, *next;

    Node(): prev(this), next(this) {}

    operator bool() { return next != this; }
    
    void extend(Node<T, TagT> &src) {
      if (src.next != &src) {
        prev->next = src.next;
        src.next->prev = prev;
        prev = src.prev;
        src.prev->next = this;
        src.prev = src.next = &src;
      }
    }

    void append(Node<T, TagT> &node) {
      node.prev = this;
      node.next = next;
      next->prev = &node;
      next = &node;
    }

    T &get() { return static_cast<T &>(*this); }

    void push(Node<T, TagT> &node) { prev->append(node); }
    
    void unlink() {
      prev->next = next;
      next->prev = prev;
    }
  };
}

#endif
