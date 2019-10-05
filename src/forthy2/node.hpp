#ifndef FORTHY2_NODE_HPP
#define FORTHY2_NODE_HPP

namespace forthy2 {  
  template <typename T, typename TagT = T>
  struct Node {
    Node<T, TagT> *prev, *next;

    Node(): prev(this), next(this) {}

    void append(Node<T, TagT> &node) {
      node.prev = this;
      node.next = next;
      next->prev = &node;
      next = &node;
    }

    void del() {
      prev->next = next;
      next->prev = prev;
    }

    void push(Node<T, TagT> &node) { prev->append(node); }
    T &get() { return static_cast<T &>(*this); }
  };
}

#endif
